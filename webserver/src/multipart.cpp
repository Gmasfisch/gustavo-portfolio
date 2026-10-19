#include "../include/multipart.hpp"

std::string MultipartParser::extractBoundary(const std::string& contentType)
{
	size_t pos = contentType.find("boundary=");
	if (pos == std::string::npos)
		throw std::runtime_error("No boundary found in Content-Type");
	size_t start = pos + 9;
	return contentType.substr(start);
}

std::string MultipartParser::extractFileContent(const std::string& body, const std::string& boundary)
{
	std::string delimiter = "--" + boundary;
	size_t headerEnd = body.find("\r\n\r\n");
	if (headerEnd == std::string::npos)
		throw std::runtime_error("No header end found");
	size_t contentStart = headerEnd + 4;
	size_t nextDelim = body.find(delimiter, contentStart);
	if (nextDelim == std::string::npos)
		throw std::runtime_error("No new occurrence for delimiter");
	if (nextDelim < contentStart + 2)
		return (std::string());
	size_t contentEnd = nextDelim - 2;
	return (body.substr(contentStart, contentEnd - contentStart));
}

std::string MultipartParser::extractFilename(const std::string& body)
{
	size_t pos = body.find( "filename=\"" );
	if (pos == std::string::npos)
		throw std::runtime_error("No filename found");
	size_t start = pos + 10;
	size_t end = body.find( "\"", start );
	if (end == std::string::npos)
		throw std::runtime_error("Missing \" after filename in body");
	std::string name = body.substr(start, end - start);
	size_t slash = name.rfind('/');
	if (slash != std::string::npos)
		name = name.substr(slash + 1);
	return (name);
}
