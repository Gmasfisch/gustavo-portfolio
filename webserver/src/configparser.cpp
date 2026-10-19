#include "../include/configparser.hpp"

std::vector<std::string> ConfigParser::tokenize(const std::string& content)
{
	std::vector<std::string>	tokens;
	size_t						i = 0;
	size_t						start;
	char						c;

	while (i < content.size())
	{
		c = content[i];
		if (c == '#')
		{
			while (content[i] && content[i] != '\n')
				i++;
			continue ;
		}
		if (std::isspace(static_cast<unsigned char>(c)))
		{
			i++;
			continue ;
		}
		if (c == '{' || c == '}' || c == ';')
		{
			tokens.push_back(std::string(1, c));
			i++;
			continue;
		}
		else
		{
			start = i;
			c = content[i];
			while (c && !(std::isspace(c) || c == '{' || c == '}' || c == ';'))
			{
				i++;
				c = content[i];
			}
			tokens.push_back(content.substr(start, i - start));
		}
	}
	return tokens;
}

const std::string& ConfigParser::next(const std::vector<std::string>& tokens, size_t& i)
{
	if (i >= tokens.size())
		throw std::runtime_error("Error: File finished before expected");
	size_t j = i;
	i++;
	return (tokens[j]);
}

const std::string& ConfigParser::expect(const std::vector<std::string>& tokens, size_t& i, const std::string& value)
{
	const std::string &current_token = next(tokens, i);
	if (current_token != value)
		throw std::runtime_error("Error: expected " + value + ", got " + current_token);
	return (current_token);
}

void ConfigParser::parseLocationDirective(const std::vector<std::string>& tokens, size_t& i, LocationConfig& loc)
{
	std::string directive = ConfigParser::next(tokens, i);

	if (directive == "root")
		loc.root = ConfigParser::next(tokens, i);
	else if (directive == "index")
		loc.index = ConfigParser::next(tokens, i);
	else if (directive == "autoindex")
		loc.autoindex = (ConfigParser::next(tokens, i) == "on");
	else if (directive == "upload_enabled")
		loc.upload_enabled = (ConfigParser::next(tokens, i) == "on");
	else if (directive == "upload_dir")
		loc.upload_dir = ConfigParser::next(tokens, i);
	else if (directive == "methods")
	{
		std::string method;
		while (i < tokens.size() && tokens[i] != ";")
		{
			method = ConfigParser::next(tokens, i);
			loc.methods.push_back(std::string(method));
		}
	}
	else if (directive == "redirect")
	{
		const std::string code_str = ConfigParser::next(tokens, i);
		loc.redirect_code = stringToInt(code_str);
		loc.redirect_target = ConfigParser::next(tokens, i);
	}
	else if (directive == "cgi_ext")
	{
		std::string ext = ConfigParser::next(tokens, i);
		std::string interpreter = ConfigParser::next(tokens, i);
		loc.cgi_extensions[ext] = interpreter;
	}
	else if (directive == "client_max_body_size")
    {
        std::string max = ConfigParser::next(tokens, i);
        loc.client_max_body_size = stringToInt(max);
    }
	else
		throw std::runtime_error("Unknown directive: " + directive);
	ConfigParser::expect(tokens, i, ";");
}

LocationConfig ConfigParser::parseLocationBlock(const std::vector<std::string>& tokens, size_t& i)
{
	LocationConfig loc;

	ConfigParser::expect(tokens, i, "{");
	while (i < tokens.size() && tokens[i] != "}")
		ConfigParser::parseLocationDirective(tokens, i, loc);
	ConfigParser::expect(tokens, i, "}");
	return loc;
}

void ConfigParser::parseServerDirective(const std::vector<std::string>& tokens, size_t& i, ServerConfig& srv)
{
	std::string directive = ConfigParser::next(tokens, i);

	if (directive == "listen")
	{
		std::string listen_str = ConfigParser::next(tokens, i);
		std::string local_host = "0.0.0.0";
		int local_port = 8080;
		if (i < tokens.size() && tokens[i] == ":")
		{
			local_host = listen_str;
			ConfigParser::next(tokens, i);
			std::string port_str = ConfigParser::next(tokens, i);
			local_port = stringToInt(port_str);
		}
		else
		{
			size_t colon = listen_str.find(':');
			if (colon != std::string::npos)
			{
				local_host = listen_str.substr(0, colon);
				std::string tmp = listen_str.substr(colon + 1);
				local_port = stringToInt(tmp);
			}
			else
			{
				if (listen_str.find('.') != std::string::npos)
					local_host = listen_str;
				else
					local_port = stringToInt(listen_str);
			}
		}
		if (local_port < 1 || local_port > 65535)
			throw std::runtime_error("Error: Invalid Port" + listen_str);
		if (local_host == "localhost")
			local_host = "127.0.0.1";
		srv.listens.push_back(std::make_pair(local_host, local_port));
	}
	else if (directive == "host" || directive == "host:")
	{
		std::string target_host = ConfigParser::next(tokens, i);
		if (srv.listens.empty())
			srv.listens.push_back(std::make_pair(target_host, 8080));
		else
			srv.listens.back().first = target_host;
	}
	else if (directive == "port" || directive == "port:")
	{
		int target_port = stringToInt(ConfigParser::next(tokens, i));
		if (target_port < 1 || target_port > 65535)
			throw std::runtime_error("Error: Invalid port Value");
		if (srv.listens.empty())
			srv.listens.push_back(std::make_pair("0.0.0.0", target_port));
		else
			srv.listens.back().second = target_port;
	}
	else if (directive == "server_name")
		srv.server_name = ConfigParser::next(tokens, i);
	else if (directive == "error_page")
	{
		std::string err_code = ConfigParser::next(tokens, i);
		std::string str = ConfigParser::next(tokens, i);
		srv.error_pages[stringToInt(err_code)] = str;
	}
	else if (directive == "client_max_body_size")
	{
		std::string max = ConfigParser::next(tokens, i);
		srv.client_max_body_size = stringToInt(max);
	}
	else
		throw std::runtime_error("Unknown directive: " + directive);
	ConfigParser::expect(tokens, i, ";");
}

ServerConfig ConfigParser::parseServerBlock(const std::vector<std::string>& tokens, size_t& i)
{
	ServerConfig srv;

	ConfigParser::expect(tokens, i, "{");
	while (i < tokens.size() && tokens[i] != "}")
	{
		if (tokens[i] == "location")
		{
			ConfigParser::next(tokens, i);
			std::string path = ConfigParser::next(tokens, i);
			LocationConfig loc = ConfigParser::parseLocationBlock(tokens, i);
			loc.path = path;
			srv.locations.push_back(loc);
		}
		else
			parseServerDirective(tokens, i, srv);
	}
	ConfigParser::expect(tokens, i, "}");
	if (srv.listens.empty())
		srv.listens.push_back(std::make_pair("0.0.0.0", 8080));
	for (size_t k = 0; k < srv.locations.size(); ++k)
    {
        if (srv.locations[k].client_max_body_size == 0)
            srv.locations[k].client_max_body_size = srv.client_max_body_size;
    }
	return srv;
}

Config ConfigParser::parseFile(const std::string& path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw std::runtime_error("Invalid path: " + path);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::vector<std::string> tokens = ConfigParser::tokenize(buffer.str());
	Config config;
	size_t  i = 0;
	while (i < tokens.size())
	{
		ConfigParser::expect(tokens, i, "server");
		config.push_back(parseServerBlock(tokens, i));
	}
	if (config.empty())
		throw std::runtime_error("No server block in file");
	return config;
}

long ConfigParser::stringToInt(const std::string& str)
{
	std::stringstream ss(str);
	long value;
	ss >> value;
	if (ss.fail() || !ss.eof())
		throw std::runtime_error("invalid number: " + str);
	if (value < 0)
		throw std::runtime_error("negative number not allowed: " + str);
	return value;
}
