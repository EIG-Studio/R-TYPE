/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** systems
*/

#include "Systems.hpp"

#include "components.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Window/Window.hpp>

#include <functional>
#include <map>
#include <utility>

void shootingSystem(Entity entity, Registry& registry)
{
    if (!registry.hasComponent(entity, Shooter{}) || !registry.hasComponent(entity, Position{}))
        return;

    if (registry.getComponent(entity, Shooter{}).isShooting()) {
        auto position = registry.getComponent(entity, Position{}).getPosition();
        // Create a projectile using the position and velocity sendChange(ID POS)
    }
}

void deathSystem(Entity entity, Registry& registry)
{
    if (!registry.hasComponent(entity, HealthPoint{}))
        return;

    if (registry.getComponent(entity, HealthPoint{}).getHealthPoint() <= 0)
        registry.destroyEntity(entity);
}

void damagedSystem(Entity entity, Entity otherEntity, Registry& registry)
{
    if (!registry.hasComponent(entity, Damage{}) || !registry.hasComponent(otherEntity, HealthPoint{}))
        return;

    auto& healthPoint = registry.getComponent(otherEntity, HealthPoint{});
    healthPoint.setHealthPoint(healthPoint.getHealthPoint() - registry.getComponent(entity, Damage{}).getDamage());
}

void movementSystem(Entity entity, Registry& registry)
{
    if (!registry.hasComponent(entity, Speed{}) || !registry.hasComponent(entity, Velocity{}) ||
        !registry.hasComponent(entity, Position{}))
        return;

    auto& position = registry.getComponent(entity, Position{});
    auto& velocity = registry.getComponent(entity, Velocity{});
    auto& speed = registry.getComponent(entity, Speed{});

    position.setPosition(
        {position.getPosition().first + velocity.getVelocity().first * speed.getSpeed(),
         position.getPosition().second + velocity.getVelocity().second * speed.getSpeed()});

    velocity.setVelocity(0, 0);
}

void noMoveSystem(Entity entity, Entity otherEntity, Registry& registry)
{
    if (!registry.hasComponent(entity, Position{}) || !registry.hasComponent(otherEntity, Position{}))
        return;

    auto& positionEntity = registry.getComponent(entity, Position{});
    auto& positionOtherEntity = registry.getComponent(otherEntity, Position{});

    positionEntity.setPosition({positionEntity.getPosition().first + 1, positionEntity.getPosition().second + 1});
    positionOtherEntity.setPosition(
        {positionOtherEntity.getPosition().first - 1, positionOtherEntity.getPosition().second - 1});
}

void collisionPlayer(const Entity& entity, Entity otherEntity, Registry& registry)
{
    if (registry.hasComponent(otherEntity, Type{}))
        return;

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player_Projectile)
        return;

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy_Projectile)
        damagedSystem(entity, otherEntity, registry);

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Wall)
        noMoveSystem(entity, otherEntity, registry);
}

void collisionEnemy(const Entity& entity, Entity otherEntity, Registry& registry)
{
    if (registry.hasComponent(otherEntity, Type{}))
        return;

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy_Projectile ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy)
        return;

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player_Projectile)
        damagedSystem(entity, otherEntity, registry);

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Wall)
        noMoveSystem(entity, otherEntity, registry);
}

void collisionProjectile(const Entity& entity, Entity otherEntity, Registry& registry)
{
    if (registry.hasComponent(otherEntity, Type{}))
        return;

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player_Projectile ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player)
        return;

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy_Projectile)
        damagedSystem(entity, otherEntity, registry);

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Wall)
        registry.destroyEntity(entity);
}


bool checkHitBox(float x, float y, std::pair<float, float> origin, std::pair<float, float> end)
{
    return x > origin.first && x < origin.first + end.first && y > origin.second && y < origin.second + end.second;
}

void collisionSystem(Entity entity, std::vector<Entity> entities, Registry& registry)
{
    std::map<EntityType, std::function<void(Entity, Entity, Registry&)>> map = {
        {EntityType::Player, collisionPlayer},
        {EntityType::Enemy, collisionEnemy},
        {EntityType::Player_Projectile, collisionProjectile},
        {EntityType::Enemy_Projectile, collisionProjectile},
    };
    EntityType entityType;

    if (!registry.hasComponent(entity, HitBox{}) || !registry.hasComponent(entity, Type{}))
        return;

    entityType = registry.getComponent(entity, Type{}).getEntityType();
    for (auto& otherEntity : entities) {
        if (!registry.hasComponent(entity, HitBox{}) || !registry.hasComponent(entity, Type{}))
            continue;
        if (registry.getComponent(otherEntity, ID{}).getID() == registry.getComponent(entity, ID{}).getID())
            continue;

        auto it = map.find(entityType);
        if (it != map.end()) {
            it->second(entity, otherEntity, registry);
        } else {
            continue;
        }
    }
}

void iaSystem(Entity entity, Registry& registry)
{
    // Implementation for AI system
}

#include <iostream>
void renderSystem(Entity entity, Registry& registry, sf::RenderWindow& window)
{
    if (!registry.hasComponent(entity, Renderer{}) || !registry.hasComponent(entity, Position{}))
        return;

    registry.getComponent(entity, Renderer{})
        .getRenderer()
        .setPosition(
            registry.getComponent(entity, Position{}).getPosition().first,
            registry.getComponent(entity, Position{}).getPosition().second);
    window.draw(registry.getComponent(entity, Renderer{}).getRenderer());
}
