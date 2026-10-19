#pragma once
#include "webserver.hpp"
#include "connection.hpp"
#include "config.hpp"
#include <csignal>

extern volatile std::sig_atomic_t g_stop;

class Server
{
    public:
        Server();
        bool setupSocket(const std::pair<std::string, int>& hostPort, const ServerConfig* cfg);
        void run();
        ~Server();
        
    private:
        Server& operator=(const Server&);
        Server(const Server&);
        std::string makeResponse(int code, const std::string& type, const std::string& body);
        std::string cgiResponse(const std::string& out);
        std::string handleRequest(const std::string& raw, Connection& conn, int client_fd);
        std::string makeError(int code);
        std::string serveError(const ServerConfig* cfg, int code);
		unsigned long changeIpToInt(const std::string& host);
        void processBuffer(int client_fd, Connection& conn);
        void closeClient(int fd);
        void setEvents(int fd, short events);
        void removePollFd(int fd);
        bool startCgi(int client_fd, Connection& conn, const std::string& interpreter,
                      const std::string& filepath, const std::vector<std::string>& env,
                      const std::string& body);
        void cgiWriteStep(int pipe_fd, Connection& conn, std::vector<int>& toRemove);
        void cgiReadStep(int pipe_fd, int client_fd, Connection& conn, std::vector<int>& toRemove);
        void finishCgi(int client_fd, Connection& conn, std::vector<int>& toRemove);
        void abortCgi(int client_fd, Connection& conn, int code, std::vector<int>& toRemove);
        std::map<int, const ServerConfig*> _listen_fds;
        std::map<int, Connection> _clients;
        std::vector<struct pollfd> _pollfds;
        std::map<int, int> _cgi_pipe_to_client;
};

