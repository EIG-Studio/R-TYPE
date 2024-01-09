/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** entities
*/

#pragma once
#define getComponent(e, f) getComponentT( e, f, __FILE__, __func__, __LINE__ )

#include "components.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window.hpp>

#include <SFML/System.hpp>

#include <any>
#include <iostream>
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
    Entity createEntityWithID(int customID);
    void destroyEntity(Entity entity);
    Entity getEntity(size_t id);
    void setEntity(Entity& entityToCopy, int id);
    Entity getPlayer();
    Entity getFirstEnemy();
    bool hasEntity(size_t id);
    std::vector<Entity> getListEnemies();
    std::vector<Entity> getListPlayers();
    std::vector<Entity> getListEntities();
    std::vector<Entity> getListPlayersProjectile();
    std::vector<Entity> deletePlayersProjectile(int id);
    std::vector<Entity> deleteEnnemy(int id);
    void deleteById(int id);
    void destroyEnnemy(std::vector<Entity> ennemyList);
    template <typename T>
    Entity addComponent(Entity entity, T component);
    template <typename T>
    void removeComponent(Entity entity, T component);
    template <typename T>
    T& getComponentT(Entity& entity, T component, const char* file, const char* fn, int line);

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
Entity Registry::addComponent(Entity entity, T component)
{
    ID newID = any_cast<ID>(entity.mComponents[0]);
    size_t id = newID.getID();

    if (hasComponent(entity, component))
        return entity;

    entity.mComponents.push_back(component);

    for (size_t i = 0; i < m_entities.size(); i++) {
        newID = any_cast<ID>(m_entities[i].mComponents[0]);
        if (newID.getID() == id)
            m_entities[i] = entity;
    }
    return entity;
}

template <typename T>
void Registry::removeComponent(Entity entity, T component)
{
    ID newID = any_cast<ID>(entity.mComponents[0]);
    size_t id = newID.getID();
    int index = 0;

    if (!hasComponent(entity, component))
        return;

    for (size_t i = 0; i < entity.mComponents.size(); i++) {
        try {
            std::any_cast<T>(entity.mComponents[i]);
            index = i;
        } catch (const std::bad_any_cast&) {
            continue;
        }
    }

    entity.mComponents.erase(entity.mComponents.begin() + index);

    for (size_t i = 0; i < m_entities.size(); i++) {
        newID = any_cast<ID>(m_entities[i].mComponents[0]);
        if (newID.getID() == id)
            m_entities[i] = entity;
    }
}

#include <iostream>
template <typename T>
T& Registry::getComponentT(Entity& entity, T component, const char* file, const char* fn, int line)
{
    for (auto& mComponent : entity.mComponents) {
        try {
            std::any_cast<T>(mComponent);
            return std::any_cast<T&>(mComponent);
        } catch (const std::bad_any_cast&) {
            continue;
        }
    }
    throw std::runtime_error("Component not found function called at " + std::string(file) + " " + std::string(fn) + " " + std::to_string(line));
}

template <typename T>
bool Registry::hasComponent(Entity& entity, T component)
{
    for (const auto& otherComponent : entity.mComponents) {
        try {
            std::any_cast<T>(otherComponent);
            return true;
        } catch (const std::bad_any_cast&) {
            continue;
        }
    }
    return false;
}
