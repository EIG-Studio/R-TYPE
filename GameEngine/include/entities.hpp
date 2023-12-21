/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** entities
*/

#pragma once
#include "components.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

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
    std::string systemsManager(sf::RenderWindow& window);

    template <typename T>
    bool hasComponent(Entity& entity, T component);

    // void setWindow(sf::RenderWindow window)
    // {
    //     m_window = std::move(window);
    // }

private:
    std::vector<Entity> m_entities;
    sf::RenderWindow m_window;
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

#include <iostream>
template <typename T>
T& Registry::getComponent(Entity& entity, T component)
{
    for (auto& mComponent : entity.mComponents) {
        try {
            std::any_cast<T>(component);
            return std::any_cast<T&>(mComponent);
        } catch (const std::bad_any_cast&) {
            continue;
        }
    }
    throw std::runtime_error("Component not found");
}

template <typename T>
bool Registry::hasComponent(Entity& entity, T component)
{
    for (const auto& otherComponent : entity.mComponents) {
        try {
            std::any_cast<T>(component);
            return true;
        } catch (const std::bad_any_cast&) {
            continue;
        }
    }
    return false;
}
