#pragma once
#include "webserver.hpp"
#include "config.hpp"

enum e_extract
{
    EXTRACT_INCOMPLETE,
    EXTRACT_READY,
    EXTRACT_TOO_LARGE,
    EXTRACT_BAD_REQUEST
};

class Connection
{
    public:
        Connection();
        Connection(int fd, const ServerConfig* cfg);
        Connection(const Connection&);
        Connection& operator=(const Connection&);
        const ServerConfig* getConfig() const;
        void appendToRead(const char* data, size_t n);
        const std::string& getReadBuffer() const;
        e_extract extractRequest(std::string& out);
        void queueWrite(const std::string& data);
        bool hasPendingWrite() const;
        const char* pendingData() const;
        size_t pendingSize() const;
        void advanceSent(size_t n);
        void touch();
        void markForClose();
        bool shouldCloseAfterWrite() const;
        time_t getLastActivity() const;
        void beginCgi(pid_t pid, int in_fd, int out_fd, const std::string& body);
        bool isCgiRunning() const;
        pid_t cgiPid() const;
        int cgiInFd() const;
        int cgiOutFd() const;
        time_t cgiStart() const;
        const char* cgiInputPtr() const;
        size_t cgiInputLeft() const;
        void cgiInputAdvance(size_t n);
        void cgiSwitchToReading();
        void cgiAppendOutput(const char* data, size_t n);
        const std::string& cgiOutput() const;
        void cgiReset();
        ~Connection();

    private:
        int _fd;
        std::string _read_buffer;
        std::string _write_buffer;
        size_t _bytes_sent;
        enum e_state
        {
            READING_HEADERS,
            READING_BODY,
            SENDING,
            CGI_WRITING,
            CGI_READING,
            DONE
        };
        e_state _state;
        time_t _last_activity;
        const ServerConfig* _config;
        bool _close_after_write;
        pid_t _cgi_pid;
        int _cgi_in_fd;
        int _cgi_out_fd;
        std::string _cgi_input;
        size_t _cgi_input_sent;
        std::string _cgi_output;
        time_t _cgi_start;
        size_t _chunk_scan;
};