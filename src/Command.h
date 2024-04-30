#ifndef FT_COMMAND_H
#define FT_COMMAND_H

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
#include "utils.h"

// Create a Command interface
class Command
{
public:
    virtual void execute(int clientSocket, sockaddr_in address_client) = 0;
};

// Create a concrete command for handling client requests
class ClientRequestCommand : public Command
{
public:
    void execute(int clientSocket, sockaddr_in address_client) override 
    {
        std::string client_representation = "Client [" + std::to_string(clientSocket) + " | " + inet_ntoa(address_client.sin_addr) + "] ";
        std::cout << client_representation << "has connected to the server" << std::endl;
        while (true)
        {

            char buffer[DEFAULT_BUFLEN_IN] = {0};
            int bytesRead = read(clientSocket, buffer, DEFAULT_BUFLEN_IN);
            if (bytesRead <= 0)
            {
                std::cout << client_representation << "disconnected" << std::endl;
                break;
            }
            std::cout << client_representation << "message: " << buffer << std::endl;

            srv::TarotCardTeller cardTeller;
            std::string answer = cardTeller.tell_tarot(std::string(buffer));
            const char *message = answer.c_str();
            std::cout << client_representation << "received: " << message << std::endl;
            send(clientSocket, message, strlen(message), 0);
        }
        close(clientSocket);
    };
};


#endif // FT_COMMAND_H