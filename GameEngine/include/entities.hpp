/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** entities
*/

#pragma once
#include "components.hpp"

#include <unordered_map>
#include <vector>

#include <cstdint>
#include <cassert>

using Entity             = std::uint32_t;
const Entity maxEntities = 1000;

class EntityManager
{
public:
    EntityManager();
    Entity createEntity();
    void   destroyEntity(Entity entity);

private:
    std::vector<Entity>                  m_availableEntities;
    std::unordered_map<Entity, Position> m_positions;
    std::unordered_map<Entity, Velocity> m_velocities;
};


/********-Player Entity-******/
class Player
{
public:
    Player()  = delete;
    ~Player() = default;

private:
    Position    m_position;
    HealthPoint m_life;
};

/********-Enemy Entity-******/
class Enemy
{
public:
    Enemy()  = delete;
    ~Enemy() = default;

private:
    Position    m_position;
    HealthPoint m_life;
};
