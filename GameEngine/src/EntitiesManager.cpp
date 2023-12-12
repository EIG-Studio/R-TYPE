/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** entities
*/

#include "entities.hpp"

#include <iostream>


EntityManager::EntityManager()
{
    for (Entity entity = 0; entity < maxEntities; ++entity) {
        m_availableEntities.push_back(entity);
    }
}

Entity EntityManager::createEntity()
{
    assert(!m_availableEntities.empty());

    Entity id = m_availableEntities.back();
    m_availableEntities.pop_back();
    return id;
}

extern "C"
{
    void moveUp()
    {
        std::cout << "UP" << std::endl;
    }
    void moveRight()
    {
        std::cout << "RIGHT" << std::endl;
    }
    void moveDown()
    {
        std::cout << "DOWN" << std::endl;
    }
    void moveLeft()
    {
        std::cout << "LEFT" << std::endl;
    }
}

void EntityManager::destroyEntity(Entity entity)
{
    m_availableEntities.push_back(entity);
}
