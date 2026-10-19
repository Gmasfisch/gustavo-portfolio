#pragma once
#include <string>
#include <stdexcept>

class MultipartParser
{
	public:
		static std::string extractBoundary(const std::string& contentType);
		static std::string extractFileContent(const std::string& body, const std::string& boundary);
		static std::string extractFilename(const std::string& body);

	private:
		MultipartParser();
};