/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "components.hpp"
#include "entities.hpp"
#include "server.hpp"

#include <dlfcn.h>
#include <thread>


int main()
{
    try {
        Server server;


        Registry registry = Registry();
        Entity entity;
        entity = registry.createEntity();
        // Position position = Position(std::make_pair(0, 0));
        // registry.addComponent(entity, position);
        // registry.addComponent(entity, Shooter(true));
        // registry.addComponent(entity, HitBox(std::make_pair(0, 0), std::make_pair(0, 0)));

        registry.systemsManager();

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
