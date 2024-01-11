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
        registry.deleteById(registry.getComponent(entity, ID{}).getID());
}

void damagedSystem(Entity entity, Entity otherEntity, Registry& registry)
{
    // if (!registry.hasComponent(entity, Damage{}) || !registry.hasComponent(otherEntity, HealthPoint{}))
    //     return;

    // auto& healthPoint = registry.getComponent(otherEntity, HealthPoint{});
    // healthPoint.setHealthPoint(healthPoint.getHealthPoint() - registry.getComponent(entity, Damage{}).getDamage());
}

void movementSystem(Entity entity, Registry& registry)
{
    if (!registry.hasComponent(entity, Speed{}) || !registry.hasComponent(entity, Velocity{}) ||
        !registry.hasComponent(entity, Position{}))
        return;

    auto& position = registry.getComponent(entity, Position{});
    auto& velocity = registry.getComponent(entity, Velocity{});
    auto& speed = registry.getComponent(entity, Speed{});

    std::cout << "Pos Before x: "<< position.getPosition().first << ", y: " << position.getPosition().second << std::endl;
    position.setPosition(
        {position.getPosition().first + velocity.getVelocity().first * speed.getSpeed(),
         position.getPosition().second + velocity.getVelocity().second * speed.getSpeed()});
    std::cout << "Pos After x: "<< position.getPosition().first << ", y: " << position.getPosition().second << std::endl;
    registry.setEntity(entity, registry.getComponent(entity, ID{}).getID());
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


bool checkHitBox(float x, float y, std::pair<float, float> origin, std::pair<float, float> size)
{
    return x >= origin.first && x <= origin.first + size.first &&
           y >= origin.second && y <= origin.second + size.second;
}

bool checkCollisionForFourCorners(Entity entity, Entity otherEntity, Registry& registry)
{
    if (!registry.hasComponent(entity, HitBox{}) || !registry.hasComponent(otherEntity, HitBox{}))
        return false;

    std::pair<float, float> originEntity = registry.getComponent(entity, HitBox{}).getOriPos();
    std::pair<float, float> sizeEntity = registry.getComponent(entity, HitBox{}).getSize();
    std::pair<float, float> originOther = registry.getComponent(otherEntity, HitBox{}).getOriPos();
    std::pair<float, float> sizeOther = registry.getComponent(otherEntity, HitBox{}).getSize();

    float xOther = originOther.first;
    float yOther = originOther.second;
    float xOtherEnd = xOther + sizeOther.first;
    float yOtherEnd = yOther + sizeOther.second;

    // Check for collision
    bool topLeft = checkHitBox(xOther, yOther, originEntity, sizeEntity);
    bool topRight = checkHitBox(xOtherEnd, yOther, originEntity, sizeEntity);
    bool bottomLeft = checkHitBox(xOther, yOtherEnd, originEntity, sizeEntity);
    bool bottomRight = checkHitBox(xOtherEnd, yOtherEnd, originEntity, sizeEntity);

    return topLeft || topRight || bottomLeft || bottomRight;
}

void collisionSystem(Entity entity, std::vector<Entity> entities, Registry& registry)
{
    if (entity.mComponents.empty())
        return;

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
        if (!registry.hasComponent(otherEntity, HitBox{}) || !registry.hasComponent(otherEntity, Type{}))
            continue;
        if (registry.getComponent(otherEntity, ID{}).getID() == registry.getComponent(entity, ID{}).getID())
            continue;
        if (checkCollisionForFourCorners(entity, otherEntity, registry)) {
            auto it = map.find(entityType);
            if (it != map.end()) {
                it->second(entity, otherEntity, registry);
            } else {
                continue;
            }
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
    if (!registry.hasComponent(entity, Renderer{}) || !registry.hasComponent(entity, Position{}) || !registry.hasComponent(entity, Type{}))
        return;

    Type& typeComponent = registry.getComponent(entity, Type{});
    if (typeComponent.getEntityType() == EntityType::Player) {
        Position entityPos = registry.getComponent(entity, Position{});
        std::pair<float, float> pos = entityPos.getPosition();
    }

    sf::Texture text = registry.getComponent(entity, Renderer{}).getTexture();
    sf::Sprite sprite = registry.getComponent(entity, Renderer{}).getRenderer();
    sprite.setScale(registry.getComponent(entity, Size{}).getSize().first,
        registry.getComponent(entity, Size{}).getSize().second);
    sprite.setPosition(registry.getComponent(entity, Position{}).getPosition().first,
    registry.getComponent(entity, Position{}).getPosition().second);
    sprite.setTexture(text);
    window.draw(sprite);
}
