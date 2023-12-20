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

#include <unordered_map>
#include <vector>

#include <cassert>
#include <cstdint>

using Entity = std::uint32_t;
const Entity maxEntities = 1000;

extern "C"
{
    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();
}

class EntityManager
{
public:
    EntityManager();
    Entity createEntity();
    template <typename... Components>
    EntityManager(Components&&... components);

    template <typename Component>
    Component* getComponent() const;

    template <typename Component, typename... Rest>
    void addComponents(Component&& component, Rest&&... rest);
    void destroyEntity(Entity entity);

private:
    std::vector<Entity> m_availableEntities;
    std::unordered_map<Entity, Position> m_positions;
    std::unordered_map<Entity, Velocity> m_velocities;
    std::unordered_map<size_t, std::unique_ptr<void>> components;
    template <typename Component>
    void addComponent(Component&& component);
};

class registry
{
public:

private:
};

/********-Player Entity-******/
class Player
{
public:
    Player() = delete;
    ~Player() = default;

private:
    Position m_position;
    HealthPoint m_life;
};

/********-Enemy Entity-******/
class Enemy
{
public:
    Enemy() = delete;
    ~Enemy() = default;

private:
    Position m_position;
    HealthPoint m_life;
};

/********-Registry-******/
class Registry
{
public:
    Registry() = default;
    ~Registry() = default;

private:
    Entity createEntity();
    void destroyEntity(Entity entity);
    std::vector<Entity> m_availableEntities;
};
