/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** systems
*/

#pragma once

#include "entities.hpp"

#include <array>

void shootingSystem(Entity entity, Registry& registry);
std::string deathSystem(Entity entity, Registry& registry);
std::string damagedSystem(Entity entity, Entity otherEntity, Registry& registry);
std::string movementSystem(Entity entity, Registry& registry);
std::string collisionSystem(Entity entity, std::vector<Entity> entities, Registry& registry);
void iaSystem(Entity entity, Registry& registry);
void renderSystem(Entity entity, Registry& registry, sf::RenderWindow& window);

enum COMMAND
{
    NEW,
    LOGIN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NEW_PLAYER,
    NEW_ENEMY,
    NEW_BOSS,
    DELETE_ENTITY,
    GET_POWER_UP,
    PLAYER_PROJECTILE,
    PLAY_BOOM_ENEMIES,
    REFRESH,
    NEW_POS,
    NEW_HEALTH,
    UPDATE,
    SHOOT,
    POWER_UP,
    BLUE_PROJECILE,
    BLUE_PROJECILE_ENABLED,
    DAMAGE_TO_PLAYER,
    UNKNOWN,
    EMPTY,
    ALIVE,
    NEW_HUD,
    SCORE,
    LEVEL,
    ARROW_PLAYER,
    LOGIN_OK,
    WIN,
    LOSE,
};

COMMAND getCommand(const std::string& commandStr);
EntityType getType(const std::string& typeStr);

struct TransferData
{
    enum COMMAND command;
    std::array<int, 5> args;
};
