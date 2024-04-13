#ifndef FT_SERVER_H
#define FT_SERVER_H

#include <iostream>
#include <thread>
#include <vector>
#include <winsock2.h>
#include <mutex>
#include <string>

#define DEFAULT_PORT 2026
#define DEFAULT_BUFLEN 512
#define MAX_CLIENTS 6

namespace server {

class Server {
public:
    Server(int port);
    ~Server();

    void start();
    void stop();

private:
    int port;
    bool running;
    std::vector<std::thread> threads;

    void handleClient(int clientSocket);
    void initializeWinsock();
    void cleanupWinsock();
};

}
#endif // FT_SERVER_H