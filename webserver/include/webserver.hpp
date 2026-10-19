#pragma once
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <ctime>
#include <set>
#include <map>
#include <vector>
#include <cstring>
#include <stdbool.h>
#include <fcntl.h>
#include <stdexcept>
#include <new>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <utility>
#include <cctype>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

#define BUFFER_SIZE 4096
#define TIMEOUT_SEC 60
#define DEF_MAX_BODY_SIZE 1048576
#define MAX_HEADER_SIZE 8192