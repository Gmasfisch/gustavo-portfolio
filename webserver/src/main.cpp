#include "webserver.hpp"
#include "connection.hpp"
#include "server.hpp"
#include "configparser.hpp"
#include <csignal>


static void handleStop(int)
{
    g_stop = 1;
}

int main(int argc, char **argv)
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, handleStop);
    signal(SIGTERM, handleStop);
    if (argc != 2)
    {
        std::cerr << "Usage: ./webserv <config file>" << std::endl;
        return (1);
    }
    try
    {
        Config config = ConfigParser::parseFile(argv[1]);
        Server server;
        for (size_t i = 0; i < config.size(); i++)
            for (size_t j = 0; j < config[i].listens.size(); j++)
                if (!server.setupSocket(config[i].listens[j], &config[i]))
                {
                    std::ostringstream msg;
                    msg << " cannot listen on host:port " << config[i].listens[j].first << ":" << config[i].listens[j].second;
                    throw std::runtime_error(msg.str());
                }
        std::cout << "waiting..." << std::endl;
        server.run();
    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...) 
    { 
        std::cerr << "unknown error" << std::endl; 
        return 1;
     }
    return (0);
}