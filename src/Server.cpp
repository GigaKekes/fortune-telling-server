#include "Server.h"

namespace server{

Server::Server(int port)
{
    // Constructor implementation
    this->port = port;
    this->running = false;
    initializeWinsock();
}

Server::~Server()
{
    // Destructor implementation
    cleanupWinsock();
}

void Server::start()
{
    // Method implementation for starting the server
    running = true;
    std::cout << "Server started on port " << port << std::endl;
    while (running)
    {
        // Accept incoming connections
        // Create a new thread to handle the client
    }
}

void Server::stop()
{
    // Method implementation for stopping the server
    running = false;
    std::cout << "Server stopped" << std::endl;
    return;
}

void Server::handleClient(int clientSocket)
{
}

void Server::initializeWinsock()
{
    
}

void Server::cleanupWinsock()
{

}

} // namespace server