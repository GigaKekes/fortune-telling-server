#ifndef FT_SERVER_H
#define FT_SERVER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

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
    int port_;
    bool running_;

    std::vector<std::thread> client_threads_;

    void handleClient(int clientSocket);

};

}
#endif // FT_SERVER_H