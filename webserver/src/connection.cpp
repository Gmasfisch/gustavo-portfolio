#include "../include/webserver.hpp"
#include "../include/connection.hpp"

static bool parseNum(const std::string& s, size_t& out);

Connection::Connection() : _fd(-1), _bytes_sent(0), _state(READING_HEADERS), _last_activity(time(NULL)), _config(NULL), _close_after_write(false), _cgi_pid(-1), _cgi_in_fd(-1), _cgi_out_fd(-1), _cgi_input_sent(0), _cgi_start(0), _chunk_scan(0)
{}

Connection::Connection(int fd, const ServerConfig* cfg) : _fd(fd), _bytes_sent(0), _state(READING_HEADERS), _last_activity(time(NULL)), _config(cfg), _close_after_write(false), _cgi_pid(-1), _cgi_in_fd(-1), _cgi_out_fd(-1), _cgi_input_sent(0), _cgi_start(0), _chunk_scan(0)
{}

Connection::Connection(const Connection& other) : _fd(other._fd), _read_buffer(other._read_buffer), _write_buffer(other._write_buffer),
	_bytes_sent(other._bytes_sent), _state(other._state), _last_activity(other._last_activity), _config(other._config), _close_after_write(other._close_after_write), _cgi_pid(other._cgi_pid), _cgi_in_fd(other._cgi_in_fd), _cgi_out_fd(other._cgi_out_fd), _cgi_input(other._cgi_input), _cgi_input_sent(other._cgi_input_sent), _cgi_output(other._cgi_output), _cgi_start(other._cgi_start), _chunk_scan(other._chunk_scan)
{}

void Connection::appendToRead(const char* data, size_t n)
{
	_read_buffer.append(data, n);
}

const std::string& Connection::getReadBuffer() const
{
	return _read_buffer;
}

static bool parseNum(const std::string& s, size_t& out)
{
    std::stringstream ss(s);
    ss >> out;
    return !ss.fail();
}

static bool parseHexNum(const std::string& s, size_t& out)
{
	std::stringstream ss(s);
	ss >> std::hex >> out;
	return !ss.fail();
}

static e_extract trimBody(const std::string& body, std::string& new_body, size_t &consumed)
{
	size_t init_pos = 0;
	while (true)
	{
		size_t size_end = body.find("\r\n", init_pos);
		if (size_end == std::string::npos)
			return EXTRACT_INCOMPLETE;
		size_t size = 0;
		if (!parseHexNum(body.substr(init_pos, size_end - init_pos), size))
			return EXTRACT_BAD_REQUEST;
		if (size == 0)
		{
			if (size_end + 4 > body.size())
				return EXTRACT_INCOMPLETE;
			consumed = size_end + 4;
			return EXTRACT_READY;
		}
		if (size_end + 2 + size + 2 > body.size())
			return EXTRACT_INCOMPLETE;
		new_body += body.substr(size_end + 2, size);
		init_pos = size + 2 + size_end + 2;
	}
	return EXTRACT_READY;
}

e_extract Connection::extractRequest(std::string& out)
{
	size_t pos = _read_buffer.find("\r\n\r\n");
	if (pos == std::string::npos)
		return EXTRACT_INCOMPLETE;
	size_t end = pos + 4;
	size_t req_end;

	std::string lower = _read_buffer.substr(0, end);
	for (size_t i = 0; i < lower.size(); i++)
		lower[i] = tolower(static_cast<unsigned char>(lower[i]));
	size_t te_pos = lower.find("transfer-encoding: chunked");
	size_t cl_pos = lower.find("content-length:");
	if (te_pos != std::string::npos && cl_pos != std::string::npos)
		return EXTRACT_BAD_REQUEST;
	size_t max_body = DEF_MAX_BODY_SIZE;
	if (_config != NULL)
		max_body = _config->client_max_body_size;
	if (te_pos != std::string::npos && te_pos < pos )
	{
		if (_read_buffer.size() - end > max_body *2 + 1024)
			return EXTRACT_TOO_LARGE;
		size_t from = end;
		if (_chunk_scan > from)
			from = _chunk_scan;
		size_t term = _read_buffer.find("0\r\n\r\n", from);
		if (term == std::string::npos)
		{
			if (_read_buffer.size() > 4)
				_chunk_scan = _read_buffer.size() - 4;
			return EXTRACT_INCOMPLETE;
		}
		std::string headers = _read_buffer.substr(0, end);
		std::string clean_body;
		size_t te = 0;
		e_extract r = trimBody(_read_buffer.substr(end), clean_body, te);
		if (clean_body.size() > max_body)
			return EXTRACT_TOO_LARGE;
		if (r != EXTRACT_READY)
		{
			if (r == EXTRACT_INCOMPLETE)
				_chunk_scan = term + 1;
			return r;
		}
		out = headers + clean_body;
		_read_buffer.erase(0, end + te);
		_chunk_scan = 0;
		return EXTRACT_READY;
	}
	else
	{
		size_t cl = 0;
		if (cl_pos != std::string::npos && cl_pos < pos)
		{
			size_t num_start = cl_pos + 15;
			size_t num_end = _read_buffer.find( "\r\n", num_start );
			if (num_end == std::string::npos)
				return EXTRACT_INCOMPLETE ;
			if (!parseNum(_read_buffer.substr(num_start, num_end - num_start), cl))
    	        return EXTRACT_BAD_REQUEST;
		}
		if (cl > max_body)
			return EXTRACT_TOO_LARGE;
		if (_read_buffer.size() < end + cl)
			return EXTRACT_INCOMPLETE;
		req_end = end + cl;
	}
	out = _read_buffer.substr(0, req_end);
	_read_buffer.erase(0, req_end);
	return EXTRACT_READY;
}

void Connection::queueWrite(const std::string& data)
{
	_write_buffer.append(data);
}

bool Connection::hasPendingWrite() const
{
	return _bytes_sent < _write_buffer.size();
}

const char* Connection::pendingData() const
{
	return _write_buffer.c_str() + _bytes_sent;
}

size_t Connection::pendingSize() const
{
	return _write_buffer.size() - _bytes_sent;
}

void Connection::advanceSent(size_t n) 
{
	_bytes_sent += n;
	if (_bytes_sent >= _write_buffer.size())
	{
		_write_buffer.clear();
		_bytes_sent = 0;
	}
}

const ServerConfig* Connection::getConfig() const
{
	return _config;
}

void Connection::touch()
{
	_last_activity = time(NULL);
}

time_t Connection::getLastActivity() const
{
	return _last_activity;
}

void Connection::markForClose()
{
	_close_after_write = true;
}

bool Connection::shouldCloseAfterWrite() const
{
	return _close_after_write;
}

Connection& Connection::operator=(const Connection& other)
{
	if (this != &other)
	{
		this->_fd = other._fd;
		this->_read_buffer = other._read_buffer;
		this->_write_buffer = other._write_buffer;
		this->_bytes_sent = other._bytes_sent;
		this->_state = other._state;
		this->_last_activity = other._last_activity;
		this->_config = other._config;
		this->_close_after_write = other._close_after_write;
		this->_cgi_pid = other._cgi_pid;
		this->_cgi_in_fd = other._cgi_in_fd;
		this->_cgi_out_fd = other._cgi_out_fd;
		this->_cgi_input = other._cgi_input;
		this->_cgi_input_sent = other._cgi_input_sent;
		this->_cgi_output = other._cgi_output;
		this->_cgi_start = other._cgi_start;
		this->_chunk_scan = other._chunk_scan;
	}
	return *this;
}

void Connection::beginCgi(pid_t pid, int in_fd, int out_fd, const std::string& body)
{
	_cgi_pid = pid;
	_cgi_in_fd = in_fd;
	_cgi_out_fd = out_fd;
	_cgi_input = body;
	_cgi_input_sent = 0;
	_cgi_output.clear();
	_cgi_start = time(NULL);
	_state = CGI_WRITING;
}

bool Connection::isCgiRunning() const
{
	return _state == CGI_WRITING || _state == CGI_READING;
}

pid_t Connection::cgiPid() const 
{ 
	return _cgi_pid;
}

int Connection::cgiInFd() const 
{ 
	return _cgi_in_fd; 
}

int Connection::cgiOutFd() const 
{ 
	return _cgi_out_fd; 
}

time_t Connection::cgiStart() const 
{ 
	return _cgi_start; 
}

const char* Connection::cgiInputPtr() const
{
	return _cgi_input.c_str() + _cgi_input_sent;
}

size_t Connection::cgiInputLeft() const
{
	return _cgi_input.size() - _cgi_input_sent;
}

void Connection::cgiInputAdvance(size_t n)
{
	_cgi_input_sent += n;
}

void Connection::cgiSwitchToReading()
{
	_cgi_in_fd = -1;
	_state = CGI_READING;
}

void Connection::cgiAppendOutput(const char* data, size_t n)
{
	_cgi_output.append(data, n);
}

const std::string& Connection::cgiOutput() const
{
	return _cgi_output;
}

void Connection::cgiReset()
{
	_cgi_pid = -1;
	_cgi_in_fd = -1;
	_cgi_out_fd = -1;
	_cgi_input.clear();
	_cgi_input_sent = 0;
	_cgi_output.clear();
	_cgi_start = 0;
	_state = READING_HEADERS;
}

Connection::~Connection()
{}