/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ECS
*/

#pragma once

#include <dlfcn.h>
#include <iostream>

class ECS
{
public:
    ECS() = default;

    void setPath(const char* libraryPath)
    {
        m_libraryHandle = dlopen(libraryPath, RTLD_LAZY);

        if (!m_libraryHandle) {
            std::cerr << "Failed to load the shared library: " << dlerror() << std::endl;
        }
    }

    ~ECS()
    {
        if (m_libraryHandle) {
            dlclose(m_libraryHandle);
        }
    }

    void callMoveUp()
    {
        typedef void (*MyFunctionType)();
        auto moveUp = (MyFunctionType)dlsym(m_libraryHandle, "moveUp");

        if (!moveUp) {
            std::cerr << "Failed to find the symbol myFunction: " << dlerror() << std::endl;
        }

        moveUp();
    }

    void callMoveRight()
    {
        typedef void (*MyFunctionType)();
        auto moveRight = (MyFunctionType)dlsym(m_libraryHandle, "moveRight");

        if (!moveRight) {
            std::cerr << "Failed to find the symbol myFunction: " << dlerror() << std::endl;
        }

        moveRight();
    }

    void callMoveDown()
    {
        typedef void (*MyFunctionType)();
        auto moveDown = (MyFunctionType)dlsym(m_libraryHandle, "moveDown");

        if (!moveDown) {
            std::cerr << "Failed to find the symbol myFunction: " << dlerror() << std::endl;
        }

        moveDown();
    }

    void callMoveLeft()
    {
        typedef void (*MyFunctionType)();
        auto moveLeft = (MyFunctionType)dlsym(m_libraryHandle, "moveLeft");

        if (!moveLeft) {
            std::cerr << "Failed to find the symbol myFunction: " << dlerror() << std::endl;
        }

        moveLeft();
    }

private:
    void* m_libraryHandle{};
};
;
