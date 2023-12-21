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

template<typename... Components>
EntityManager::EntityManager(Components&&... components) {
    addComponents(std::forward<Components>(components)...);
}

template<typename Component, typename... Rest>
void EntityManager::addComponents(Component&& component, Rest&&... rest) {
    addComponent(std::forward<Component>(component));
    addComponents(std::forward<Rest>(rest)...);
}

template<typename Component>
Component* EntityManager::getComponent() const {
    auto it = components.find(typeid(Component).hash_code());
    if (it != components.end()) {
        return dynamic_cast<Component*>(it->second.get());
    }
    return nullptr;
}

template<typename Component>
void EntityManager::addComponent(Component&& component) {
    components[typeid(Component).hash_code()] = std::make_unique<Component>(std::forward<Component>(component));
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
