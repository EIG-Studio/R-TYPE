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
    ECS(const char* libraryPath)
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

    void callMyFunction()
    {
        typedef void (*MyFunctionType)();
        auto myFunction = (MyFunctionType)dlsym(m_libraryHandle, "myFunction");

        if (!myFunction) {
            std::cerr << "Failed to find the symbol myFunction: " << dlerror() << std::endl;
        }

        myFunction();
    }

private:
    void* m_libraryHandle;
};
;
