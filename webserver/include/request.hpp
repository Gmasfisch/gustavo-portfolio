#pragma once
#include "webserver.hpp"

class Request
{
    public:
        Request();
        Request(const Request&);
        Request& operator=(const Request&);
        bool parseReq(const std::string&);
        const std::string& getMethod() const;
        const std::string& getPath() const;
        const std::string& getVersion() const;
        const std::string& getBody() const;
        const std::string& getQuery() const;
        const std::string getHeader(const std::string& name) const;
        const std::map<std::string, std::string>& getHeaders() const;
        ~Request();
    
    private:
        std::string _method;
        std::string _path;
        std::string _version;
        std::string _body;
        std::string _query;
        bool parseHeaders(const std::string& req, size_t pos);
        std::map<std::string, std::string> _headers;
};