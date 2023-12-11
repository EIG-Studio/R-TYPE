/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ECS
*/

#include <dlfcn.h>
#pragma once

class ECS {
    public:
        ECS() = default;
        ~ECS() = default;

        void* libraryHandle = dlopen("GameEngine/libEntitiesManager.so", RTLD_LAZY);
        using MyFunctionType = void (*)();
        auto myFunction = (MyFunctionType)dlsym(libraryHandle, "myFunction");

    protected:
    private:
};
