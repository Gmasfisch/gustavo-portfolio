#pragma once
#include "webserver.hpp"
#include "config.hpp"

class ConfigParser
{
	public:
		static std::vector<std::string>	tokenize(const std::string& content);
		static const std::string&		next(const std::vector<std::string>& tokens, size_t& i);
		static const std::string&		expect(const std::vector<std::string>& tokens, size_t& i, const std::string& value);
		static void parseLocationDirective(const std::vector<std::string>& tokens, size_t& i, LocationConfig& loc);
		static LocationConfig parseLocationBlock(const std::vector<std::string>& tokens, size_t& i);
		static void parseServerDirective(const std::vector<std::string>& tokens, size_t& i, ServerConfig& srv);
		static ServerConfig parseServerBlock(const std::vector<std::string>& tokens, size_t& i);
		static Config parseFile(const std::string& path);
		static long stringToInt(const std::string& str);

	private:
		ConfigParser();
};