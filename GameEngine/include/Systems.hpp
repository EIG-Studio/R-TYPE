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

void shootingSystem(Entity entity);
void deathSystem(Entity entity);
void damagedSystem(Entity entity, std::vector<Entity> entList);
void movementSystem(Entity entity);
void iaSystem(Entity entity);
void renderSystem(Entity entity);
