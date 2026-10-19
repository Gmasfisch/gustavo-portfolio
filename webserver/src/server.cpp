#include "../include/webserver.hpp"
#include "../include/server.hpp"
#include "../include/request.hpp"
#include "../include/multipart.hpp"
#include <csignal>

volatile std::sig_atomic_t g_stop = 0;

static const int CGI_TIMEOUT_SEC = 15;

static std::string statusText(int code);
static std::string contentType(const std::string& path);
static bool readFile(const std::string& path, std::string& out);
static bool writeFile(const std::string& path, const std::string& content);
static bool methodAllowed(const std::string& method, const std::vector<std::string>& allowed);static bool listDirectory(const std::string& dirpath, const std::string& urlpath, std::string& out);
static std::vector<std::string> buildEnv(const Request& req, const ServerConfig* cfg);
static std::string envToUpper(const std::string& s);

Server::Server()
{}

bool Server::setupSocket(const std::pair<std::string, int>& hostPort, const ServerConfig* cfg)
{
    int fd;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        std::cerr << "Error: Socket()" << std::endl;
        return false;
    }
    fcntl(fd, F_SETFL, O_NONBLOCK);
    int yes = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
    {
        std::cerr << "error: setsockopt" << std::endl;
        close(fd);
        return false;
    }
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(hostPort.second);
	unsigned long changedIp = changeIpToInt(hostPort.first);
	if (changedIp == INADDR_NONE)
		std::cerr << "inet addr failed to parse IP" << std::endl;
    addr.sin_addr.s_addr = changedIp;
    if (bind(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
    {
        std::cerr << "Error: Bind()" << std::endl;
        close(fd);
        return false;
    }
    if (listen(fd, SOMAXCONN) < 0)
    {
        std::cerr << "Error: Listen()" << std::endl;
        close(fd);
        return false;
    }
    _listen_fds[fd] = cfg;
    return true;
}

unsigned long Server::changeIpToInt(const std::string& host)
{
	std::string ipString = host;
	if (ipString == "0.0.0.0" || ipString.empty())
		return 0;
	std::stringstream ss(ipString);
	unsigned int part1, part2, part3, part4;
	char dot1, dot2, dot3;

	ss >> part1 >> dot1 >> part2 >> dot2 >> part3 >> dot3 >> part4;
	if (ss.fail() || !ss.eof() || dot1 != '.' || dot2 != '.' || dot3 != '.' || part1 > 255 || part2 > 255 || part3 > 255 || part4 > 255)
		throw std::runtime_error("Error: Invalid IP format" + ipString); 
	unsigned long ipAsNumber = (part1 << 24) | (part2 << 16) | (part3 << 8) | part4;
	return htonl(ipAsNumber);
}

void Server::processBuffer(int client_fd, Connection& conn)
{
    if (conn.isCgiRunning())
        return;
    e_extract r;
    std::string raw;
    while ((r = conn.extractRequest(raw)) == EXTRACT_READY)
    {
        std::string resp = handleRequest(raw, conn, client_fd);
        if (conn.isCgiRunning())
            return;
        conn.queueWrite(resp);
    }
    if (r == EXTRACT_TOO_LARGE || r == EXTRACT_BAD_REQUEST)
    {
        conn.queueWrite(serveError(conn.getConfig(), r == EXTRACT_TOO_LARGE ? 413 : 400));
        conn.markForClose();
    }
    if (conn.hasPendingWrite())
        setEvents(client_fd, POLLIN | POLLOUT);
}

void Server::run()
{
    std::map<int, const ServerConfig*>::iterator it;
    for (it = _listen_fds.begin(); it != _listen_fds.end(); it++)
    {
        struct pollfd pfd;
        pfd.fd = it->first;
        pfd.events = POLLIN;
        pfd.revents = 0;
        _pollfds.push_back(pfd);
    }
    while (!g_stop)
    {
        std::vector<std::pair<int, const ServerConfig*> > newVec;
        std::vector<int> toClose;
        std::vector<int> pipesToRemove;
        if (poll(&_pollfds[0], _pollfds.size(), 1000) < 0)
            continue;
        for (size_t i = 0; i < _pollfds.size(); i++)
        {
            short re = _pollfds[i].revents;
            if (re == 0)
                continue;
            int fd = _pollfds[i].fd;
            if (_cgi_pipe_to_client.count(fd)) 
            {
                std::map<int, Connection>::iterator oc = _clients.find(_cgi_pipe_to_client[fd]);
                try
                {
                    if (oc == _clients.end())
                    {
                        close(fd);
                        _cgi_pipe_to_client.erase(fd);
                        pipesToRemove.push_back(fd);
                    }
                    else if (fd == oc->second.cgiInFd() && (re & (POLLOUT | POLLERR)))
                        cgiWriteStep(fd, oc->second, pipesToRemove);
                    else if (fd == oc->second.cgiOutFd() && (re & (POLLIN | POLLHUP)))
                        cgiReadStep(fd, oc->first, oc->second, pipesToRemove);
                    else if (re & (POLLERR | POLLNVAL))
                        abortCgi(oc->first, oc->second, 502, pipesToRemove);
                }
                catch (const std::bad_alloc&) 
                {
                    if (oc != _clients.end())
                        toClose.push_back(oc->first);
                }
                continue;
            }
            if (re & (POLLHUP | POLLERR | POLLNVAL))
            {
                if (!_listen_fds.count(fd))
                    toClose.push_back(fd);
                continue;
            }
            if (re & POLLIN)
            {
                if (_listen_fds.count(fd))
                {
                    int client_fd = accept(fd, NULL, NULL);
                    if (client_fd >= 0)
                    {
                        fcntl(client_fd, F_SETFL, O_NONBLOCK);
                        newVec.push_back(std::make_pair(client_fd, _listen_fds[fd]));
                    }
                }
                else 
                {
                    char buf[BUFFER_SIZE];
                    ssize_t n = recv(fd, buf, sizeof(buf), 0);
                    if (n > 0) 
                    {
                        std::map<int, Connection>::iterator cit = _clients.find(fd);
                        if (cit == _clients.end())
                            continue;
                        try
                        {
                            cit->second.appendToRead(buf, n);
                            cit->second.touch();
                            processBuffer(fd, cit->second);
                        }
                        catch (const std::bad_alloc&)
                        {
                            toClose.push_back(fd);
                        }
                    }
                    else 
                    {
                        std::cout << "Client disconnected" << std::endl;
                        toClose.push_back(fd);
                    }
                }
            }
            if (re & POLLOUT)
            {
                std::map<int, Connection>::iterator cit = _clients.find(fd);
                if (cit == _clients.end())
                    continue;
                ssize_t n = send(fd, cit->second.pendingData(), cit->second.pendingSize(), 0);
                if (n > 0)
                    cit->second.advanceSent(n);
                else
                    toClose.push_back(fd);
                if (!cit->second.hasPendingWrite())
                {
                    if(cit->second.shouldCloseAfterWrite())
                        toClose.push_back(fd);
                    else
                        setEvents(fd, POLLIN);
                }
            }
        }
        for (size_t j = 0; j < newVec.size(); j++)
        {
            _clients.insert(std::make_pair(newVec[j].first, Connection(newVec[j].first, newVec[j].second)));
            struct pollfd pfd;
            pfd.fd = newVec[j].first;
            pfd.events = POLLIN;
            pfd.revents = 0;
            _pollfds.push_back(pfd);
        }
        time_t now = time(NULL);
        std::map<int, Connection>::iterator cit;
        for (cit = _clients.begin(); cit != _clients.end(); ++cit)
        {
            if (cit->second.isCgiRunning() && now - cit->second.cgiStart() > CGI_TIMEOUT_SEC)
            {
                std::cout << "CGI timed out" << std::endl;
                abortCgi(cit->first, cit->second, 504, pipesToRemove);
            }
            else if (now - cit->second.getLastActivity() > TIMEOUT_SEC)
            {
                std::cout << "Client timed out" << std::endl;
                toClose.push_back(cit->first);
            }
        }
        for (size_t p = 0; p < pipesToRemove.size(); p++)
            removePollFd(pipesToRemove[p]);
        for (size_t k = 0; k < toClose.size(); k++)
            closeClient(toClose[k]);
    }
    std::vector<int> remaining;
    for (std::map<int, Connection>::iterator cit = _clients.begin(); cit != _clients.end(); ++cit)
        remaining.push_back(cit->first);
    for (size_t k = 0; k < remaining.size(); k++)
        closeClient(remaining[k]);
}

std::string Server::cgiResponse(const std::string& out)
{
    size_t pos = out.find("\r\n\r\n");
    size_t sep_len = 4;
    std::string headers;
    std::string body;
    if (pos == std::string::npos)
    {
        pos = out.find("\n\n");
        sep_len = 2;
    }
    if (pos == std::string::npos)
        body = out;
    else 
    {
        headers = out.substr(0, pos);
        body = out.substr(pos + sep_len);
    }
    std::ostringstream oss;
	std::string statusLine = "200 OK";
	size_t statusPos = headers.find("Status: ");
	if (statusPos != std::string::npos && (statusPos == 0 || headers[statusPos - 1] == '\n'))
	{
		size_t lineEnd = headers.find('\n', statusPos);
		std::string rawStatus;
		if (lineEnd == std::string::npos)
		    rawStatus = headers.substr(statusPos + 8);
		else
		    rawStatus = headers.substr(statusPos + 8, lineEnd - (statusPos + 8));

		if (!rawStatus.empty() && rawStatus[rawStatus.size() - 1] == '\r')
		    rawStatus.erase(rawStatus.size() - 1);
		statusLine = rawStatus;
		size_t eraseEnd;
		if (lineEnd == std::string::npos)
		    eraseEnd = headers.size();
		else
		    eraseEnd = lineEnd + 1;
		headers.erase(statusPos, eraseEnd - statusPos);
	}
	oss << "HTTP/1.1 " << statusLine << "\r\n";
    if (!headers.empty())
        oss << headers << "\r\n";
    oss << "Content-Length: " << body.size() << "\r\n";
    oss << "\r\n";
    oss << body;
    return oss.str();
}

std::string Server::handleRequest(const std::string& raw, Connection& conn, int client_fd)
{
    const ServerConfig* cfg = conn.getConfig();
    Request req;
    if (!req.parseReq(raw))
        return serveError(cfg, 400);
    if (req.getVersion().compare(0, 5, "HTTP/") != 0)
        return serveError(cfg, 400);
    if (req.getVersion() != "HTTP/1.1" && req.getVersion() != "HTTP/1.0")
        return serveError(cfg, 505);

    std::string full_path = req.getPath();
    std::string pure_path = full_path;
    std::string query_string = "";
    size_t qmark = full_path.find('?');
    if (qmark != std::string::npos)
    {
        pure_path = full_path.substr(0, qmark);
        query_string = full_path.substr(qmark + 1);
    }

    if (pure_path.find("..") != std::string::npos)
        return serveError(cfg, 403);

    const LocationConfig* loc = cfg->matchLocation(pure_path);
	
    if (!loc)
		return serveError(cfg, 404);

    if (!methodAllowed(req.getMethod(), loc->methods)) {
        return serveError(cfg, 405);
	}
	
	if (loc->client_max_body_size > 0 && req.getBody().size() > (size_t)loc->client_max_body_size)
		return serveError(cfg, 413);

    if (loc->redirect_code != 0)
    {
        std::ostringstream oss;
        oss << "HTTP/1.1 " << loc->redirect_code << " " << statusText(loc->redirect_code) << "\r\n"
            << "Location: " << loc->redirect_target << "\r\n"
            << "Content-Length: 0\r\n"
            << "\r\n";
        return oss.str();
    }
	
    std::string subpath = pure_path;
	if (loc->path != "/" && subpath.find(loc->path) == 0)
	    subpath = subpath.substr(loc->path.length());

	if (subpath.empty() || subpath[0] != '/')
	    subpath = "/" + subpath;

	std::string filepath = loc->root + subpath;

    struct stat st;
    bool exists = (stat(filepath.c_str(), &st) == 0);
    bool isdir = (exists && S_ISDIR(st.st_mode));
    size_t dot = filepath.rfind('.');
    if (dot != std::string::npos)
    {
        std::string ext = filepath.substr(dot);
        std::map<std::string, std::string>::const_iterator it = loc->cgi_extensions.find(ext);
        if (it != loc->cgi_extensions.end() && (req.getMethod() == "GET" || req.getMethod() == "POST"))
        {
            if (!exists && req.getMethod() == "GET")
                return serveError(cfg, 404);
            std::vector<std::string> env = buildEnv(req, cfg);
            if (!startCgi(client_fd, conn, it->second, filepath, env, req.getBody()))
                return serveError(cfg, 500);
            return std::string();
        }
    }
    
    if (req.getMethod() == "GET")
    {
        if (isdir)
        {
            if (filepath[filepath.size() - 1] != '/')
                filepath += '/';
            
            std::string indexpath = filepath + loc->index;
            bool has_index = (!loc->index.empty() && stat(indexpath.c_str(), &st) == 0);
			if (!req.getPath().empty() && req.getPath()[req.getPath().size() - 1] != '/')
			{
				if (!has_index && !loc->autoindex)
                	return serveError(cfg, 404);
			}

            if (has_index)
                filepath = indexpath;
            else if (loc->autoindex)
            {
                std::string body;
                if (!listDirectory(filepath, pure_path, body))
                    return serveError(cfg, 403);
                return makeResponse(200, "text/html", body);
            }
            else
			{
				if (!exists)
					return serveError(cfg, 404);
				else
					return serveError(cfg, 403);
			}
        }
        if (!exists)
            return serveError(cfg, 404);

        std::string resp_body;
        if (!readFile(filepath, resp_body))
            return serveError(cfg, 404);
        return makeResponse(200, contentType(filepath), resp_body);
    }
    else if (req.getMethod() == "POST")
    {
        std::map<std::string, std::string>::const_iterator it = req.getHeaders().find("content-type");
        if (it != req.getHeaders().end() && it->second.find("multipart/form-data") != std::string::npos)
        {
            if (!loc->upload_enabled || loc->upload_dir.empty())
                return serveError(cfg, 403);
            try
            {
                std::string boundary = MultipartParser::extractBoundary(it->second);
                std::string filename = MultipartParser::extractFilename(req.getBody());
                if (filename.empty() || filename == "." || filename == "..")
                    return serveError(cfg, 400);
                std::string content = MultipartParser::extractFileContent(req.getBody(), boundary);
                filepath = loc->upload_dir + "/" + filename;
                if (!writeFile(filepath, content))
                    return serveError(cfg, 500);
                return makeResponse(201, "text/plain", "Created\n");
            }
            catch(const std::exception& e)
            {
                return serveError(cfg, 400);
            }
        }
        if (!loc->upload_enabled)
            return makeResponse(200, "text/plain", "OK\n");
        if (!writeFile(filepath, req.getBody()))
            return serveError(cfg, 500);
        return makeResponse(201, "text/plain", "Created\n");
    }
    else if (req.getMethod() == "DELETE")
    {
        if (!exists)
            return serveError(cfg, 404);
        if (isdir)
            return serveError(cfg, 403);
        if (std::remove(filepath.c_str()) != 0)
            return serveError(cfg, 404);
        return makeResponse(204, "text/plain", "");
    }
    return serveError(cfg, 405);
}

bool Server::startCgi(int client_fd, Connection& conn, const std::string& interpreter,
                      const std::string& filepath, const std::vector<std::string>& env,
                      const std::string& body)
{
    std::vector<char *> envptrs;
    for (size_t i = 0; i < env.size(); i++)
        envptrs.push_back(const_cast<char*>(env[i].c_str()));
    envptrs.push_back(NULL);

    int outfd[2];
    int infd[2];
    if (pipe(outfd) < 0)
        return false;
    if (pipe(infd) < 0)
    {
        close(outfd[0]);
        close(outfd[1]);
        return false;
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        close(outfd[0]);
        close(outfd[1]);
        close(infd[0]);
        close(infd[1]);
        return false;
    }
    if (pid == 0)
    {
        for (size_t i = 0; i < _pollfds.size(); i++)
            close(_pollfds[i].fd);
        close(outfd[0]);
        close(infd[1]);
        size_t file_pos = filepath.rfind("/");
        std::string file = filepath.substr(file_pos + 1);
        std::string dir = filepath.substr(0, file_pos);
        if (chdir(dir.c_str()) != 0)
            exit(1);
        char *argv[3];
        argv[0] = const_cast<char*>(interpreter.c_str());
        argv[1] = const_cast<char*>(file.c_str());
        argv[2] = NULL;
        dup2(outfd[1], STDOUT_FILENO);
        dup2(infd[0], STDIN_FILENO);
        close(outfd[1]);
        close(infd[0]);
        execve(interpreter.c_str(), argv, &envptrs[0]);
		std::cerr << "EXECVE FALLO: " << strerror(errno) << " path: " << interpreter << std::endl;
        exit(1);
    }
    close(outfd[1]);
    close(infd[0]);
    fcntl(infd[1], F_SETFL, O_NONBLOCK);
    fcntl(outfd[0], F_SETFL, O_NONBLOCK);
    conn.beginCgi(pid, infd[1], outfd[0], body);
    _cgi_pipe_to_client[infd[1]] = client_fd;
    _cgi_pipe_to_client[outfd[0]] = client_fd;

    struct pollfd pout;
    pout.fd = outfd[0];
    pout.events = POLLIN;
    pout.revents = 0;
    _pollfds.push_back(pout);
    struct pollfd pin;
    pin.fd = infd[1];
    pin.events = POLLOUT;
    pin.revents = 0;
    _pollfds.push_back(pin);
    return true;
}

void Server::cgiWriteStep(int pipe_fd, Connection& conn, std::vector<int>& toRemove)
{
    ssize_t n = write(pipe_fd, conn.cgiInputPtr(), conn.cgiInputLeft());
    if (n > 0)
        conn.cgiInputAdvance(n);
    if (n < 0 || conn.cgiInputLeft() == 0)
    {
        close(pipe_fd);
        _cgi_pipe_to_client.erase(pipe_fd);
        toRemove.push_back(pipe_fd);
        conn.cgiSwitchToReading();
    }
}

void Server::cgiReadStep(int pipe_fd, int client_fd, Connection& conn, std::vector<int>& toRemove)
{
    char buf[BUFFER_SIZE];
    ssize_t n = read(pipe_fd, buf, sizeof(buf));
    if (n > 0)
    {
        conn.cgiAppendOutput(buf, n);
        return;
    }
    close(pipe_fd);
    _cgi_pipe_to_client.erase(pipe_fd);
    toRemove.push_back(pipe_fd);
    finishCgi(client_fd, conn, toRemove);
}

void Server::finishCgi(int client_fd, Connection& conn, std::vector<int>& toRemove)
{
    if (conn.cgiInFd() >= 0)
    {
        close(conn.cgiInFd());
        _cgi_pipe_to_client.erase(conn.cgiInFd());
        toRemove.push_back(conn.cgiInFd());
    }
    bool ok = false;
    if (conn.cgiPid() > 0)
    {
        int status;
        pid_t r = waitpid(conn.cgiPid(), &status, WNOHANG);
        if (r == 0)
        {
            kill(conn.cgiPid(), SIGKILL);
            waitpid(conn.cgiPid(), NULL, 0);
            ok = true;
        }
        else if (r > 0 && WIFEXITED(status) && WEXITSTATUS(status) == 0)
            ok = true;
    }
    if (ok)
    {
        std::string response = cgiResponse(conn.cgiOutput());
        conn.cgiReset();
        conn.queueWrite(response);
        processBuffer(client_fd, conn);
    }
    else
    {
        const ServerConfig* cfg = conn.getConfig();
        conn.cgiReset();
        conn.queueWrite(serveError(cfg, 502));
        conn.markForClose();
    }
    setEvents(client_fd, POLLIN | POLLOUT);
}

void Server::abortCgi(int client_fd, Connection& conn, int code, std::vector<int>& toRemove)
{
    if (conn.cgiPid() > 0)
    {
        kill(conn.cgiPid(), SIGKILL);
        waitpid(conn.cgiPid(), NULL, 0);
    }
    if (conn.cgiInFd() >= 0)
    {
        close(conn.cgiInFd());
        _cgi_pipe_to_client.erase(conn.cgiInFd());
        toRemove.push_back(conn.cgiInFd());
    }
    if (conn.cgiOutFd() >= 0)
    {
        close(conn.cgiOutFd());
        _cgi_pipe_to_client.erase(conn.cgiOutFd());
        toRemove.push_back(conn.cgiOutFd());
    }
    const ServerConfig* cfg = conn.getConfig();
    conn.cgiReset();
    conn.queueWrite(serveError(cfg, code));
    conn.markForClose();
    setEvents(client_fd, POLLIN | POLLOUT);
}

void Server::removePollFd(int fd)
{
    for (size_t i = 0; i < _pollfds.size(); i++)
    {
        if (_pollfds[i].fd == fd)
        {
            _pollfds.erase(_pollfds.begin() + i);
            break;
        }
    }
}

void Server::closeClient(int fd)
{
    std::map<int, Connection>::iterator it = _clients.find(fd);
    if (it == _clients.end())
        return;
    if (it->second.cgiPid() > 0)
    {
        kill(it->second.cgiPid(), SIGKILL);
        waitpid(it->second.cgiPid(), NULL, 0);
    }
    if (it->second.cgiInFd() >= 0)
    {
        close(it->second.cgiInFd());
        _cgi_pipe_to_client.erase(it->second.cgiInFd());
        removePollFd(it->second.cgiInFd());
    }
    if (it->second.cgiOutFd() >= 0)
    {
        close(it->second.cgiOutFd());
        _cgi_pipe_to_client.erase(it->second.cgiOutFd());
        removePollFd(it->second.cgiOutFd());
    }
    close(fd);
    _clients.erase(fd);
    removePollFd(fd);
}

void Server::setEvents(int fd, short events)
{
    for (size_t i = 0; i < _pollfds.size(); i++)
    {
        if (_pollfds[i].fd == fd)
        {
            _pollfds[i].events = events;
            break;
        }
    }
}

static std::string statusText(int code)
{
    switch (code)
    {
        case 200: return "OK";
        case 201: return "Created";
        case 204: return "No Content";
        case 301: return "Moved Permanently";
        case 302: return "Found"; 
        case 400: return "Bad Request";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 413: return "Payload Too Large";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 502: return "Bad Gateway";
        case 504: return "Gateway Timeout";
        case 505: return "HTTP Version Not Supported";
        default: return "Unknown";
    }
}

std::string Server::makeResponse(int code, const std::string& type, const std::string& body)
{
    std::ostringstream oss;
    oss << "HTTP/1.1 " << code << " " << statusText(code) << "\r\n"
        << "Content-Type: " << type << "\r\n"
        << "Content-Length: " << body.size() << "\r\n"
        << "\r\n"
        << body;
    return oss.str();
}

std::string Server::makeError(int code)
{
    std::ostringstream body;
    body << "<html><body><h1>" << code << " " << statusText(code) << "</h1></body></html>";
    return makeResponse(code, "text/html", body.str());
}

std::string Server::serveError(const ServerConfig* cfg, int code)
{
    std::map<int, std::string>::const_iterator it = cfg->error_pages.find(code);
    if (it == cfg->error_pages.end())
        return makeError(code);
    std::string out;
    if (!readFile(it->second, out))
        return makeError(code);
    return makeResponse(code, contentType(it->second), out);
}

static std::string contentType(const std::string& path)
{
    size_t dot = path.rfind('.');
    if (dot == std::string::npos)
        return "application/octet-stream";

    std::string ext = path.substr(dot);

    if (ext == ".html" || ext == ".htm") 
        return "text/html";
    if (ext == ".css")                   
        return "text/css";
    if (ext == ".js")                    
        return "application/javascript";
    if (ext == ".json")                  
        return "application/json";
    if (ext == ".png")                   
        return "image/png";
    if (ext == ".jpg" || ext == ".jpeg") 
        return "image/jpeg";
    if (ext == ".gif")                   
        return "image/gif";
    if (ext == ".svg")                   
        return "image/svg+xml";
    if (ext == ".ico")                   
        return "image/x-icon";
    if (ext == ".txt")                   
        return "text/plain";
    if (ext == ".pdf")
        return "application/pdf";

    return "application/octet-stream";
}

static bool readFile(const std::string& path, std::string& out)
{
    std::ifstream file(path.c_str(), std::ios::binary);
    if (!file.is_open())
        return false;
    std::stringstream buffer;
    buffer << file.rdbuf();
    out = buffer.str();
    return true;
}

static bool writeFile(const std::string& path, const std::string& content)
{
    std::ofstream outfile;
    outfile.open(path.c_str(), std::ios::binary);
    if (!outfile.is_open())
        return false;
    outfile << content;
    return true;
}

static bool methodAllowed(const std::string& method, const std::vector<std::string>& allowed)
{
    if (allowed.empty())
        return true;
    for (size_t i = 0; i < allowed.size(); i++)
        if (allowed[i] == method)
            return true;
    return false;
}

static bool listDirectory(const std::string& dirpath, const std::string& urlpath, std::string& out)
{
    DIR* dir = opendir(dirpath.c_str());
    if (dir == NULL)
        return false;
    std::string base = urlpath;
    if (base.empty() || base[base.size() - 1] != '/')
        base += '/';
    std::ostringstream oss;
    oss << "<html><body><h1>Index of " << base << "</h1><ul>";

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL)
    {
        std::string name = entry->d_name;
        if (name == "." || name == "..")
            continue;
        oss << "<li><a href=\"" << base << name << "\">" << name << "</a></li>";
    }
    oss << "</ul></body></html>";
    closedir(dir);
    out = oss.str();
    return true;
}

static std::vector<std::string> buildEnv(const Request& req, const ServerConfig* cfg)
{
    std::vector<std::string> env;

    env.push_back("REQUEST_METHOD=" + req.getMethod());
    env.push_back("PATH_INFO=" + req.getPath());
    env.push_back("PATH_TRANSLATED=" + req.getPath());
    env.push_back("QUERY_STRING=" + req.getQuery());
    env.push_back("SERVER_PROTOCOL=" + req.getVersion());
    env.push_back("SERVER_NAME=" + cfg->server_name);
    env.push_back("GATEWAY_INTERFACE=CGI/1.1");
    env.push_back("REDIRECT_STATUS=200");

    std::ostringstream oss;
    oss << "CONTENT_LENGTH=" << req.getBody().size();
    env.push_back(oss.str());

    std::string contentType = req.getHeader("content-type");
    if (!contentType.empty())
        env.push_back("CONTENT_TYPE=" + contentType);

    std::map<std::string, std::string>::const_iterator it;
    for (it = req.getHeaders().begin(); it != req.getHeaders().end(); it++)
    {

        if (it->first == "content-type" || it->first == "content-length")
            continue;
        env.push_back("HTTP_" + envToUpper(it->first) + "=" + it->second);
    }
    return env;
}

static std::string envToUpper(const std::string& s)
{
    std::string str = s;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '-')
            str[i] = '_';
        else
            str[i] = toupper(str[i]);
    }
    return str;
}

Server::~Server()
{
    for (size_t i = 0; i < _pollfds.size(); i++)
        close(_pollfds[i].fd);
}