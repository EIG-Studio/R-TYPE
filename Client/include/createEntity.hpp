/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** createEntity
*/

#pragma once
#include "entities.hpp"
#include "sprite/sprite.hpp"

int setPlayer(int id);
void updatePosition(Registry& registry, int id, int xPos, int yPos);
void updateHealth(Registry& registry, int id, int health);
void createPlayer(Registry& registry, int id, int xPos, int yPos, int healthPoint);
void createEnemy(Registry& registry, int id, int xPos, int yPos, Sprite& sprite);
void createBoss(Registry& registry, int id, int xPos, int yPos, int healthPoint, Sprite& sprite);
void createPlayerProjectile(Registry& registry, int id, int xPos, int yPos);
void createEnemyProjectile(Registry& registry, int id, int xPos, int yPos);
void createPowerUp(Registry& registry, int id, int xPos, int yPos);
void createPlayerProjectile2(Registry& registry, int id, int xPos, int yPos);
void createHud(Registry& registry, int id, int dataScore);
void createScore(Registry& registry, int dataScore);
void createArrow(Registry& registry, int id);
void projectileIsBlue(Registry& registry, int id);
