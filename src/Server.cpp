#include "Server.h"

namespace srv
{

    Server::Server()
    {
        // Constructor implementation
        running_ = false;

        if ((server_fd_ = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
        int opt = 1;
        if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(DEFAULT_PORT);

        if (bind(server_fd_, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd_, MAX_CLIENTS) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
    }

    Server::~Server()
    {
       stop();
    }

    void Server::start()
    {
        struct sockaddr_in address_client;
        int addrlen_client = sizeof(address_client);
        int client_socket;
        
        while (true)
        {

            if ((client_socket = accept(server_fd_, (struct sockaddr *)&address_client, (socklen_t *)&addrlen_client)) < 0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            std::thread t(&Server::handleClient, this, client_socket, address_client);
            
            std::lock_guard<std::mutex> lock(thread_mtx_);
            client_threads_.push_back(std::move(t));
        }
    }

    void Server::stop()
    {
        for (auto &t : client_threads_)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
        close(server_fd_);
    }

    void Server::handleClient(int clientSocket, sockaddr_in address_client)
    {
        Command *command = new ClientRequestCommand();
        command->execute(clientSocket, address_client);
        delete command;
    }

} // namespace server