/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** entities
*/

#pragma once
#include "components.hpp"

#include <SFML/Window.hpp>

#include <SFML/System.hpp>

#include <any>
#include <memory>
#include <unordered_map>
#include <vector>

#include <cassert>
#include <cstdint>

class Entity
{
public:
    Entity() = default;
    ~Entity() = default;

    std::vector<std::any> mComponents;

private:
};

/********-Registry-******/
class Registry
{
public:
    Registry() = default;
    ~Registry() = default;
    Entity createEntity();
    void destroyEntity(Entity entity);
    template <typename T>
    void addComponent(Entity entity, T component);
    template <typename T>
    void removeComponent(Entity entity, T component);
    template <typename T>
    T& getComponent(Entity& entity, T component);

private:
    std::vector<Entity> m_entities;
    size_t m_id = 0;
};

template <typename T>
void Registry::addComponent(Entity entity, T component)
{
    entity.mComponents.push_back(component);
}

template <typename T>
void Registry::removeComponent(Entity entity, T component)
{
    int index = entity.mComponents[component].has_value();
    entity.mComponents.erase(entity.mComponents.begin() + index);
}

template <typename T>
T& Registry::getComponent(Entity& entity, T component)
{
    for (auto & mComponent : entity.mComponents) {
        if ((mComponent).type() == component.type())
            return std::any_cast<T&>(mComponent);
    }
    throw std::runtime_error("Component does not exist");
}

