#include "../include/config.hpp"

LocationConfig::LocationConfig()
	: autoindex(false), redirect_code(0), upload_enabled(false), client_max_body_size(0)
{
}

ServerConfig::ServerConfig()
	: client_max_body_size(1 * 1024 * 1024)
{
}

const LocationConfig* ServerConfig::matchLocation(const std::string& uri) const
{
	const LocationConfig* best = NULL;
	size_t bestLen = 0;

	for (size_t i = 0; i < locations.size(); i++)
	{
		const std::string& path = locations[i].path;
		if (uri.compare(0, path.size(), path) == 0 && path.size() > bestLen)
		{
			best = &locations[i];
			bestLen = path.size();
		}
	}
	return best;
}