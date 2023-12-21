/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "../../GameEngine/include/entities.hpp"
#include "server.hpp"

#include <dlfcn.h>
#include <thread>


int main()
{
    // void* libraryHandle = dlopen("GameEngine/libsamurai_ecs.so", RTLD_LAZY);
    //
    // if (!libraryHandle) {
    //     std::cerr << "Failed to load the shared library: " << dlerror() << std::endl;
    //     return 84;
    // }
    try {
        Server server;


        Registry registry = Registry();
        registry.createEntity();

        std::thread serverThread(&Server::startListening, &server);
        // std::thread serverThread2(&Server::startSending, &server);
        serverThread.join();
        // serverThread2.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // dlclose(libraryHandle);
    return 0;
}
