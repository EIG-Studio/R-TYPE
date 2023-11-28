/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** server
*/

#pragma once

/*
** EPITECH PROJECT, 2023
** B-YEP-400-BDX-4-1-zappy-johanna.bureau
** File description:
** client
*/


#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define READ_BUFFER_SIZE 1024

#include <iostream>
#include <string>
#include <vector>

namespace ServerRtype {
    struct player_t {
        int socketId;
        std::string ip;
        int port;
        int id;
    };

    class Server {
        public:
            Server(std::string ip, int port);
            ~Server() = default;
            void send(std::string message);
            std::string receive();
            void connectPlayer(std::string ip, int port);

        private:
            std::vector<player_t> player;
            std::vector<std::string> messageQueue;
            std::string ip;
            int port;
            int socketId;
    };
}
