/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** systems
*/
/*
- ShootingSystem -<Basic>-
- DeathSystem -<Basic>-
- DamagedSystem -<Basic>-
- MovementSystem -<Basic>-
- IASystem -<Basic>-
- RendererSystem -<Basic>-
*/

#pragma once
#include "entities.hpp"

void shootingSystem(Entity entity, Registry& registry);
void deathSystem(Entity entity, Registry& registry);
void damagedSystem(Entity entity, Entity otherEntity, Registry& registry);
void movementSystem(Entity entity, Registry& registry);
// void collisionPlayer(Entity entity, Entity otherEntity, Registry& registry);
// void collisionEnemy(Entity entity, Entity otherEntity, Registry& registry);
// void collisionProjectile(Entity entity, Entity otherEntity, Registry& registry);
void collisionSystem(Entity entity, std::vector<Entity> entities, Registry& registry);
void iaSystem(Entity entity, Registry& registry);
void renderSystem(Entity entity, Registry& registry);
