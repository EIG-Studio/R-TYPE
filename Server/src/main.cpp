/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "server.hpp"
#include <dlfcn.h>

// int main()
// {
    
//     try {
//         Server server;
//         server.startListening();
//     } catch (std::exception& e) {
//         std::cerr << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }

int main()
{
    void* libraryHandle = dlopen("GameEngine/build/samurai_ecs.so", RTLD_LAZY);
    if (!libraryHandle) {
        std::cerr << "Failed to load the shared library: " << dlerror() << std::endl;
        return 1;
    }

    // Use the loaded library
    // ...

    // Unload the shared library
    dlclose(libraryHandle);

    return 0;
}
