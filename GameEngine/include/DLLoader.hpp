/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <dlfcn.h>
#include <iostream>
#include <memory>

template <typename T> class DLLoader {
  public:
    DLLoader(const std::string &path)
    {
        std::unique_ptr<T> (*factory)();

        m_lib = dlopen(path.c_str(), RTLD_LAZY);
        if (!m_lib) {
            std::cout << "dlopen: " << dlerror() << std::endl;
            exit(84);
        }
        *(void **) (&factory) = dlsym(m_lib, "factory");
        if (!factory) {
            std::cout << "dlsym: " << dlerror() << std::endl;
            exit(84);
        }
        this->m_instance = std::move(factory());
    };
    ~DLLoader()
    {
        dlclose(m_lib);
        m_lib = nullptr;
        m_instance.reset();
    };
    T *getInstance() const
    {
        if (!m_instance) {
            std::cout << "Failed to load instance from shared factory."
                      << std::endl;
            exit(84);
        }
        return m_instance.get();
    };

    void reload(const std::string &path)
    {
        std::unique_ptr<T> (*factory)();

        dlclose(m_lib);
        m_lib = nullptr;
        m_instance.reset();

        m_lib = dlopen(path.c_str(), RTLD_LAZY);
        if (!m_lib) {
            std::cout << "dlopen: " << dlerror() << std::endl;
            exit(84);
        }
        *(void **) (&factory) = dlsym(m_lib, "factory");
        if (!factory) {
            std::cout << "dlsym: " << dlerror() << std::endl;
            exit(84);
        }
        this->m_instance = std::move(factory());
    };

  private:
    void *m_lib;
    std::unique_ptr<T> m_instance;
};

#endif /* !DLLOADER_HPP_ */
