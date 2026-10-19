*This project has been created as part of the 42 curriculum by mlemoula, gfischba.*

# webserv
C++98 HTTP server listening for TCP connections, reading HTTP requests, and sending back responses.
Non-blocking and driven by a single poll(), it features Nginx-like configuration, supports GET/POST/DELETE methods, static files, file uploads, CGI, custom error pages, and multiple listening ports.

## Description
webserv is a lightweight HTTP/1.1 server written from scratch in C++98. Its goal is to
understand the internals of HTTP and non-blocking network programming.

The whole server runs in a **single event loop built on one `poll()`** call: every socket
(listening and client) and every CGI pipe is non-blocking, and no read or write is ever
performed without `poll()` first reporting the file descriptor ready. This lets one process
serve many clients simultaneously without ever blocking.

The server is configured through an Nginx-inspired configuration file: multiple virtual
servers, listening ports, body-size limits, custom error pages, and per-route rules
(allowed methods, redirects, roots, directory listing, uploads, CGI).

## Features
- **Configuration file** (Nginx-inspired): multiple `server` blocks, several `listen`
  ports, `server_name`, `error_page`, `client_max_body_size`.
- **Per-route (`location`) rules**: accepted `methods`, `redirect`, `root`, default
  `index`, `autoindex` (directory listing), `upload_enabled` / `upload_dir`,
  `cgi_ext` (CGI by file extension). Route matching uses the longest matching prefix.
- **Methods**: `GET`, `POST`, `DELETE`.
- **Static files** with automatic `Content-Type` from the extension.
- **Directory listing** when `autoindex` is on.
- **File upload** via `multipart/form-data`, with path-traversal protection
  (only the file basename is kept).
- **CGI**, executed **without blocking the event loop**: each CGI runs in a forked
  process whose pipes are non-blocking and driven by the same single `poll()`; slow or
  runaway scripts are killed by a CGI timeout.
- **Custom error pages** (with built-in defaults when none are configured).
- **Multiple servers / ports** in a single configuration.
- **Robustness**: client and CGI timeouts, graceful client disconnection handling, and
  no crash on malformed input.

## Instructions
### Build
```
make            # builds ./webserv
make clean      # remove object files
make fclean     # remove object files and the binary
make re         # fclean + build
```
Compiled with `c++ -Wall -Wextra -Werror -std=c++98`.

### Run
```
./webserv <configuration file>
```
A configuration file is **required** (exactly one argument). Example:
```
./webserv config/default.conf
```
The sample configuration listens on ports 8080, 8081 and 9090.

### Test
With a browser (`http://localhost:8080/`) or from the command line:
```
# static file
curl http://localhost:8080/

# directory listing (autoindex)
curl http://localhost:8080/images/

# file upload (multipart/form-data)
curl -F "file=@index.html" http://localhost:8080/uploads/

# delete an uploaded file
curl -X DELETE http://localhost:8080/uploads/index.html

# CGI (GET and POST)
curl http://localhost:8080/cgi-bin/hora.sh
curl -X POST --data "hello" http://localhost:8080/cgi-bin/eco.sh
```
`telnet` and `nc` can be used to craft raw requests and check behaviour against NGINX.

## Configuration
A `server` block describes one virtual server; nested `location` blocks describe
per-route rules. Example (annotated):
```
server {
    listen 8080;                              # one or more listening ports
    listen 8081;
    server_name localhost;
    client_max_body_size 1048576;             # max request body in bytes

    error_page 404 ./www/errors/404.html;     # custom error pages
    error_page 500 ./www/errors/500.html;

    location / {
        root ./www;                           # files served from ./www
        index index.html;                     # default file for a directory
        methods GET;                          # allowed methods on this route
        autoindex off;                        # directory listing
    }

    location /uploads {
        root ./www/uploads;
        methods GET POST DELETE;
        upload_enabled on;                    # allow client uploads
        upload_dir ./www/uploads;             # where uploaded files are stored
        autoindex on;
    }

    location /old {
        redirect 301 /index.html;             # HTTP redirection
    }

    location /cgi-bin {
        root ./www/cgi-bin;
        methods GET POST;
        cgi_ext .sh /bin/bash;                # run *.sh files through /bin/bash
    }
}
```

## Resources
### References
- RFC 1945 — HTTP/1.0
- RFC 7230 / 7231 — HTTP/1.1 (message syntax, semantics)
- RFC 3875 — The Common Gateway Interface (CGI/1.1)
- RFC 2046 — MIME (multipart bodies, used for uploads)
- Beej's Guide to Network Programming (sockets)
- NGINX documentation (`server` / `location` blocks, used as a behaviour reference)
- `man` pages: `poll`, `socket`, `bind`, `listen`, `accept`, `fcntl`, `fork`,
  `execve`, `dup2`, `waitpid`

### Use of AI
AI (Claude + Gemini) was used as a **pair-programming tutor**. Concretely it was used to:
- explain the underlying notions (HTTP message framing and CRLF, `multipart/form-data`,
  the CGI model, non-blocking I/O with a single `poll()`);
- review our code and catch bugs (e.g. `size_t` underflow, copy-constructor pitfalls,
  functions outside the allowed list such as `atoi`);
- write throwaway unit tests to validate individual components;
- assist the design and implementation of the non-blocking CGI event loop.
