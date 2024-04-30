#ifndef FT_SERVER_H
#define FT_SERVER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "TarrotCardTeller.h"
#include "ThreadPool.h"
#include "utils.h"

namespace srv {

class Server {
private:
    bool running_;

    std::vector<std::thread> client_threads_; // Guarded by thread_mtx_
    std::mutex thread_mtx_;

    ThreadPool pool;
    std::mutex thread_pool;

    int server_fd_;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

public:
    Server();
    ~Server();

    void start();
    void stop();
private:
    void handleClient(int clientSocket, sockaddr_in address_client);
};

}
#endif // FT_SERVER_H