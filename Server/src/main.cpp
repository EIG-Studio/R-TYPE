/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "components.hpp"
#include "entities.hpp"
#include "server.hpp"

// #include <dlfcn.h>
#include <thread>


int main()
{
    try {
        Server server;


        Registry registry = Registry();
        Entity entity;
        entity = registry.createEntity();
        registry.addComponent(entity, Position({0, 0}));
        registry.addComponent(entity, Velocity());
        registry.addComponent(entity, Speed(1));
        registry.addComponent(entity, HealthPoint(100));
        registry.addComponent(entity, Damage(10));
        registry.addComponent(entity, Shooter());
        registry.addComponent(entity, Type(std::any_cast<EntityType>(Player)));

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
