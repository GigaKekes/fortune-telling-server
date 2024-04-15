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

#include "TarrotCardTeller.h"

#define DEFAULT_PORT 2026
#define DEFAULT_BUFLEN 1024
#define MAX_CLIENTS 6

namespace srv {

class Server {
private:
    bool running_;

    std::vector<std::thread> client_threads_; // Guarded by thread_mtx_
    std::mutex thread_mtx_;

    int server_fd_;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

public:
    Server();
    ~Server();

    void start();
    void stop();
private:
    void handleClient(int clientSocket);
};

}
#endif // FT_SERVER_H