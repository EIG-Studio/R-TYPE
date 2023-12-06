/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** entities
*/

#include "entities.hpp"


EntityManager::EntityManager()
{
    for (Entity entity = 0; entity < maxEntities; ++entity)
    {
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

void EntityManager::destroyEntity(Entity entity)
{
    m_availableEntities.push_back(entity);
}
