#include "../include/request.hpp"

Request::Request()
{}

Request::Request(const Request& other)
{
    this->_method = other._method;
    this->_path = other._path;
    this->_version = other._version;
    this->_headers = other._headers;
    this->_query = other._query;
    this->_body = other._body;
}

Request& Request::operator=(const Request& other)
{
    if (this != &other)
    {
        this->_method = other._method;
        this->_path = other._path;
        this->_version = other._version;
        this->_headers = other._headers;
        this->_query = other._query;
        this->_body = other._body;
    }
    return *this;
}

bool Request::parseReq(const std::string& req)
{
    size_t line_end = req.find("\r\n");
    if (line_end == std::string::npos)
        return false;
    size_t pos1 = req.find(' ');
    if (pos1 == std::string::npos || pos1 > line_end)
        return false;
    _method = req.substr(0, pos1);
	size_t path_start = pos1;
	while (path_start < line_end && req[path_start] == ' ')
		path_start++;
    size_t pos2 = req.find(' ', pos1 + 1);
    if (pos2 == std::string::npos || pos2 > line_end)
        return false;
    _path = req.substr(pos1 + 1, pos2 - pos1 - 1);
	std::string decoded_path = "";
	for (size_t idx = 0; idx < _path.length(); ++idx)
	{
		if (idx + 2 < _path.length() && _path[idx] == '%' && _path[idx+1] == '2' && _path[idx+2] == '0')
		{
			decoded_path += ' ';
			idx += 2;
		}
		else
		{
			decoded_path += _path[idx];
		}
	}
	_path = decoded_path;
    size_t queryPos = _path.find('?');
    if (queryPos != std::string::npos)
    {
        _query = _path.substr(queryPos + 1);
        _path = _path.substr(0, queryPos);
    }
	size_t ver_start = pos2;
	while (ver_start < line_end && req[ver_start] == ' ')
		ver_start++;
    _version = req.substr(pos2 + 1, line_end - pos2 - 1);
	while (!_version.empty() && (_version[_version.size() - 1] == ' ' || _version[_version.size() - 1] == '\t'))
		_version.erase(_version.size() - 1);
    if (_method.empty() || _path.empty() || _version.empty())
        return false;
    if (!parseHeaders(req, line_end + 2))
        return false;
    size_t pos_body = req.find("\r\n\r\n");
    if (pos_body != std::string::npos)
        _body = req.substr(pos_body + 4);
    return true;
}

bool Request::parseHeaders(const std::string& req, size_t pos)
{
    while (pos < req.size())
    {
        size_t line_end = req.find("\r\n", pos);
        if (line_end == std::string::npos)
            return false;
        if (line_end == pos)
            return true;
        size_t colon_pos = req.find(':', pos);
        if (colon_pos == std::string::npos || colon_pos > line_end)
            return false;
        size_t spaces = colon_pos + 1;
        while (spaces < line_end && (req[spaces] == ' ' || req[spaces] == '\t'))
            spaces++;
        std::string name = req.substr(pos, colon_pos - pos);
        for (size_t i = 0; i < name.size(); i++)
            name[i] = std::tolower(name[i]);
        std::string value = req.substr(spaces, line_end - spaces);
		while (!value.empty() && (value[value.size() - 1] == ' ' || value[value.size() - 1] == '\t'))
			value.erase(value.size() - 1);
        _headers[name] = value;
        pos = line_end + 2;
    }
    return false;
}

const std::string Request::getHeader(const std::string& name) const
{
    std::map<std::string, std::string>::const_iterator it = _headers.find(name);
    if (it == _headers.end())
        return "";
    return it->second;
}

const std::string& Request::getMethod() const
{
    return _method;
}

const std::string& Request::getPath() const
{
    return _path;
}

const std::string& Request::getVersion() const
{
    return _version;
}

const std::string& Request::getBody() const
{
    return _body;
}

const std::string& Request::getQuery() const
{
    return _query;
}

const std::map<std::string, std::string>& Request::getHeaders() const
{
    return _headers;
}

Request::~Request()
{}