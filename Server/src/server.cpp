/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** server
*/

#include "server.hpp"

ServerRtype::Server::Server(std::string ip, int port)
{
    this->ip = ip;
    this->port = port;
    this->socketId = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketId == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        exit(84);
    }
    // this->serverAddress.sin_family = AF_INET;
    // this->serverAddress.sin_port = htons(port);
    // if (inet_pton(AF_INET, "127.0.0.1", &this->serverAddress.sin_addr) <= 0) {
    //     std::cerr << "Failed to set server address." << std::endl;
    //     exit(84);
    // }
}

void ServerRtype::Server::connectPlayer(std::string ip, int port)
{
    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int clientSocketId = accept(this->socketId, (struct sockaddr *)&clientAddress, &clientAddressSize);

    if (clientSocketId < 0) {
        std::cerr << "Failed to accept client." << std::endl;
        exit(84);
    }
    this->player.push_back({clientSocketId, ip, port});
}

void ServerRtype::Server::send(std::string message)
{
    for (auto &player : this->player) {
        if (write(player.socketId, message.c_str(), message.length()) < 0) {
            std::cerr << "Failed to send message." << std::endl;
            exit(84);
        }
    }
}

// std::string ServerRtype::Server::receive()
// {
//     char buffer[READ_BUFFER_SIZE + 1] = {0};
//     std::string message;
//     ssize_t size = read(this->socketId, buffer, READ_BUFFER_SIZE);

//     buffer[size] = '\0';
//     message = buffer;
//     if (size < 0) {
//         std::cerr << "Failed to receive message." << std::endl;
//         exit(84);
//     } else if (size == READ_BUFFER_SIZE) {
//         while (size == READ_BUFFER_SIZE) {
//             size = read(this->socketId, buffer, READ_BUFFER_SIZE);
//             buffer[size] = '\0';
//             message += buffer;
//         }
//     }
//     return message;
// }
