/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "SFML/Graphics/Sprite.hpp"
#include "components.hpp"
#include "entities.hpp"
#include "server.hpp"

#include <thread>

int main()
{
    try {
        Server server;
        std::thread serverThread(&Server::startListening, &server);
        std::thread serverThread2(&Server::startSending, &server);

        serverThread.join();
        serverThread2.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
