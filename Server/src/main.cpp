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
    void* libraryHandle = dlopen("GameEngine/libsamurai_ecs.so", RTLD_LAZY);

    if (!libraryHandle) {
        std::cerr << "Failed to load the shared library: " << dlerror() << std::endl;
        return 84;
    }
    try {
        Server server;

        typedef Registry* (*MyFunctionType)();
        auto factory = (MyFunctionType)dlsym(libraryHandle, "factory");

        if (!factory) {
            std::cerr << "Failed to find the symbol myFunction: " << dlerror() << std::endl;
        }

        // factory();


        std::thread serverThread(&Server::startListening, &server);
        serverThread.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;

    dlclose(libraryHandle);
    return 0;
}
