#include "Server.h"

namespace srv
{
    Server::Server()
    {
        Logger logger("server.log");
        
        // Constructor implementation
        running_ = false;

        if ((server_fd_ = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            logger.log("socket failed");
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
        int opt = 1;
        if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            logger.log("setsockopt failed");
            perror("setsockopt failed");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(DEFAULT_PORT);

        if (bind(server_fd_, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            logger.log("bind failed");
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd_, MAX_CLIENTS_IN_QUEUE) < 0)
        {
            logger.log("listening failed");
            perror("listening failed");
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
        std::string client_representation = "Client [" + std::to_string(clientSocket) + " | " + inet_ntoa(address_client.sin_addr) + "] ";

        {
            std::lock_guard<std::mutex> lock(logger_mtx_);
            logger.log(client_representation + "connected");
        }

        while (true)
        {
            char buffer[DEFAULT_BUFLEN_IN] = {0};
            int bytesRead = read(clientSocket, buffer, DEFAULT_BUFLEN_IN);
            if (bytesRead <= 0)
            {
                std::lock_guard<std::mutex> lock(logger_mtx_);
                logger.log(client_representation + "disconnected");
                break;
            }
            else
            {
                std::lock_guard<std::mutex> lock(logger_mtx_);
                logger.log(client_representation + "Sent: " + std::string(buffer));
            }

            auto future = pool.enqueue([buffer]
                                       {
                srv::TarotCardTeller cardTeller;
                std::string answer = cardTeller.tell_tarot(std::string(buffer));
                return answer; });

            std::string message = future.get();
            {
                std::lock_guard<std::mutex> lock(logger_mtx_);
                logger.log(client_representation + "Received: " + message);
            }
            send(clientSocket, message.c_str(), strlen(message.c_str()), 0);
        }
        close(clientSocket);
    }

} // namespace server