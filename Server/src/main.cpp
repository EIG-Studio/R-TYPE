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

#include <iostream>
#include <thread>

int main()
{
    try {
        Server server;
        Registry registry;

        std::thread serverThread(&Server::startListening, &server, std::ref(registry));
        std::thread serverThread2(&Server::startSending, &server);
        std::thread serverThread3(&Server::gameLoop, &server, std::ref(registry));
        std::thread serverThread4(&Server::playerLoop, &server, std::ref(registry));

        serverThread.join();
        serverThread2.join();
        serverThread3.join();
        serverThread4.join();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
