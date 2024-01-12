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
#include <iostream>
#include <map>
#include <utility>

void shootingSystem(Entity entity, Registry& registry)
{
    if (entity.mComponents.empty())
        return;
    if (!registry.hasComponent(entity, Shooter{}) || !registry.hasComponent(entity, Position{}))
        return;

    if (registry.getComponent(entity, Shooter{}).isShooting()) {
        auto position = registry.getComponent(entity, Position{}).getPosition();
        // Create a projectile using the position and velocity sendChange(ID POS)
    }
}

void deathSystem(Entity entity, Registry& registry)
{
    if (entity.mComponents.empty())
        return;
    if (!registry.hasComponent(entity, HealthPoint{}))
        return;

    if (registry.getComponent(entity, HealthPoint{}).getHealthPoint() <= 0) {
        registry.toDelete.push_back(registry.getComponent(entity, ID{}).getID());
        // registry.deleteById(registry.getComponent(entity, ID{}).getID());
    }
}

std::string damagedSystem(Entity entity, Entity otherEntity, Registry& registry)
{
    if (!registry.hasComponent(entity, Damage{}) || !registry.hasComponent(otherEntity, HealthPoint{}))
        return "";

    auto& healthPoint = registry.getComponent(otherEntity, HealthPoint{});
    healthPoint.setHealthPoint(healthPoint.getHealthPoint() - registry.getComponent(entity, Damage{}).getDamage());
    registry.setEntity(otherEntity, registry.getComponent(otherEntity, ID{}).getID());
    std::cout << "healthPoint: " << healthPoint.getHealthPoint() << std::endl;
    return "NEW_HEALTH " + std::to_string(registry.getComponent(otherEntity, ID{}).getID()) + " " +
           std::to_string(registry.getComponent(otherEntity, HealthPoint{}).getHealthPoint());
}

std::string movementSystem(Entity entity, Registry& registry)
{
    if (entity.mComponents.empty())
        return "";
    if (!registry.hasComponent(entity, Speed{}) || !registry.hasComponent(entity, Velocity{}) ||
        !registry.hasComponent(entity, Position{}))
        return "";

    auto& position = registry.getComponent(entity, Position{});
    auto& velocity = registry.getComponent(entity, Velocity{});
    auto& speed = registry.getComponent(entity, Speed{});

    position.setPosition(
        {position.getPosition().first + velocity.getVelocity().first * speed.getSpeed(),
         position.getPosition().second + velocity.getVelocity().second * speed.getSpeed()});
    registry.setEntity(entity, registry.getComponent(entity, ID{}).getID());
    return "NEW_POS " + std::to_string(registry.getComponent(entity, ID{}).getID()) + " " +
           std::to_string(registry.getComponent(entity, Position{}).getPosition().first) + " " +
           std::to_string(registry.getComponent(entity, Position{}).getPosition().second) + "\n";
}

void noMoveSystem(Entity entity, Entity otherEntity, Registry& registry)
{
    if (!registry.hasComponent(entity, Position{}) || !registry.hasComponent(otherEntity, Position{}))
        return;

    auto& positionEntity = registry.getComponent(entity, Position{});
    auto& positionOtherEntity = registry.getComponent(otherEntity, Position{});

    positionEntity.setPosition({100, 100});
    registry.setEntity(entity, registry.getComponent(entity, ID{}).getID());
}

std::string collisionPlayer(const Entity& entity, Entity otherEntity, Registry& registry)
{
    if (!registry.hasComponent(otherEntity, Type{}))
        return "";

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player_Projectile)
        return "";

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy_Projectile)
        return damagedSystem(entity, otherEntity, registry);


    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Wall)
        noMoveSystem(entity, otherEntity, registry);
    return "";
}

std::string collisionEnemy(const Entity& entity, Entity otherEntity, Registry& registry)
{
    if (!registry.hasComponent(otherEntity, Type{}))
        return "";

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy_Projectile ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy)
        return "";

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player_Projectile)
        return damagedSystem(entity, otherEntity, registry);

    // if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Wall)
    // noMoveSystem(entity, otherEntity, registry);
    return "";
}

std::string collisionProjectile(Entity entity, Entity otherEntity, Registry& registry)
{
    if (!registry.hasComponent(otherEntity, Type{}))
        return "";

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player_Projectile ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Player)
        return "";

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy ||
        registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Enemy_Projectile)
        return damagedSystem(entity, otherEntity, registry);

    if (registry.getComponent(otherEntity, Type{}).getEntityType() == EntityType::Wall) {
        registry.destroyEntity(entity);
        return "DELETE " + std::to_string(registry.getComponent(entity, ID{}).getID()) + "\n";
    }
    return "";
}

bool isCollision(
    const std::pair<int, int>& pos1,
    const std::pair<int, int>& size1,
    const std::pair<int, int>& pos2,
    const std::pair<int, int>& size2)
{
    // Calculate the boundaries of the first object
    int left1 = pos1.first;
    int right1 = pos1.first + size1.first;
    int top1 = pos1.second;
    int bottom1 = pos1.second + size1.second;

    // Calculate the boundaries of the second object
    int left2 = pos2.first;
    int right2 = pos2.first + size2.first;
    int top2 = pos2.second;
    int bottom2 = pos2.second + size2.second;

    // Check for collision
    if (right1 >= left2 && left1 <= right2 && bottom1 >= top2 && top1 <= bottom2) {
        return true;
    }
    return false;
}

bool checkCollision(Entity entity, Entity otherEntity, Registry& registry)
{
    if (!registry.hasComponent(entity, HitBox{}) || !registry.hasComponent(otherEntity, HitBox{}))
        return false;
    std::pair<float, float> originEntity = registry.getComponent(entity, Position{}).getPosition();
    std::pair<float, float> sizeEntity = registry.getComponent(entity, HitBox{}).getSize();
    std::pair<float, float> originOther = registry.getComponent(otherEntity, Position{}).getPosition();
    std::pair<float, float> sizeOther = registry.getComponent(otherEntity, HitBox{}).getSize();

    return isCollision(originEntity, sizeEntity, originOther, sizeOther);
}

std::string collisionSystem(Entity entity, std::vector<Entity> entities, Registry& registry)
{
    if (entity.mComponents.empty())
        return "";

    std::map<EntityType, std::function<std::string(Entity, Entity, Registry&)>> map = {
        {EntityType::Player, collisionPlayer},
        {EntityType::Enemy, collisionEnemy},
        {EntityType::Player_Projectile, collisionProjectile},
        {EntityType::Enemy_Projectile, collisionProjectile},
    };
    EntityType entityType;

    if (!registry.hasComponent(entity, HitBox{}) || !registry.hasComponent(entity, Type{}))
        return "";

    entityType = registry.getComponent(entity, Type{}).getEntityType();
    for (auto& otherEntity : entities) {
        if (!registry.hasComponent(otherEntity, HitBox{}) || !registry.hasComponent(otherEntity, Type{}))
            continue;
        if (registry.getComponent(otherEntity, ID{}).getID() == registry.getComponent(entity, ID{}).getID() ||
            registry.getComponent(otherEntity, Type{}).getEntityType() == entityType)
            continue;
        if (checkCollision(entity, otherEntity, registry)) {
            auto it = map.find(entityType);
            if (it != map.end()) {
                return it->second(entity, otherEntity, registry);
            } else {
                continue;
            }
        }
    }
    return "";
}

void iaSystem(Entity entity, Registry& registry)
{
    // Implementation for AI system
}

void renderSystem(Entity entity, Registry& registry, sf::RenderWindow& window)
{
    if (entity.mComponents.empty())
        return;
    if (!registry.hasComponent(entity, Renderer{}) || !registry.hasComponent(entity, Position{}) ||
        !registry.hasComponent(entity, Type{}))
        return;

    Type& typeComponent = registry.getComponent(entity, Type{});
    if (typeComponent.getEntityType() == EntityType::Player) {
        Position entityPos = registry.getComponent(entity, Position{});
        std::pair<float, float> pos = entityPos.getPosition();
    }

    sf::Texture text = registry.getComponent(entity, Renderer{}).getTexture();
    sf::Sprite sprite = registry.getComponent(entity, Renderer{}).getRenderer();
    sprite
        .setScale(registry.getComponent(entity, Size{}).getSize().first, registry.getComponent(entity, Size{}).getSize().second);
    sprite.setPosition(
        registry.getComponent(entity, Position{}).getPosition().first,
        registry.getComponent(entity, Position{}).getPosition().second);
    sprite.setTexture(text);
    window.draw(sprite);
}
