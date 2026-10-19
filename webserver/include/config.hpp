#pragma once

#include "webserver.hpp"

struct	LocationConfig
{
	std::string	path;
	std::vector<std::string> methods;
	std::string root;
	std::string index;
	bool autoindex;
	int redirect_code;
	std::string redirect_target;
	bool upload_enabled;
	std::string upload_dir;
	std::map<std::string,std::string> cgi_extensions;
	size_t client_max_body_size;
	LocationConfig();
};

struct	ServerConfig
{
	std::vector<std::pair<std::string, int> > listens;
	std::string server_name;
	std::map<int, std::string> error_pages;
	size_t client_max_body_size;
	std::vector<LocationConfig> locations;
	ServerConfig();
	const LocationConfig* matchLocation(const std::string& uri) const;
};

typedef std::vector<ServerConfig> Config;