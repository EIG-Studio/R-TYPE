/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** systems
*/

#include "Systems.hpp"

void shootingSystem(Entity entity)
{
    /*
    if !entity.component.has(shooter)
        return;
    if entity.component[Shooter].isShooting()
        create a projectile(entity.component[Position].getPos, velocity)
    */
}

void deathSystem(Entity entity)
{
    /*
    if !entity.component.has(HealthPoint)
        return;
    if entity.component[HealthPoint].getHealthPoint() <= 0
        destroy entity
    */
}

void damagedSystem(Entity entity, Entity otherEntity)
{
    /*
    if !entity.component.has(Damage, HitBox)
        return;
    if !otherEntity.component.has(HHealthPoint)
        return;
    otherEntity.component[HealthPoint].setHealthPoint(otherEntity.component[HealthPoint].getHealthPoint() - entity.component[Damage].getDamage());
    */
}

void movementSystem(Entity entity)
{
    /*
    if !entity.component.has(Speed, Velocity, Position)
        return;
    std::pair<int, int> pos = entity.component[Position].getPosition();
    std::pair<int, int> velo = entity.component[Velocity].getVelocity();
    if (velo.first != 0)
        pos.first += velo.first * entity.component[Speed].getSpeed();
    velo.first = 0;
    if (velo.second != 0)
        pos.second += velo.second * entity.component[Speed].getSpeed();
    velo.second = 0;
    entity.component[Position].setPosition(pos);
    entity.component[Velocity].setVelocity(velo);
    */
}

void collisionPlayer(Entity entity, Entity otherEntity)
{
    /*
    if (otherEntity.component[Type].getType() == "Projectile_Player")
        return;
    if (otherEntity.component[Type].getType() == "Enemy" || otherEntity.component[Type].getType() == "Projectile_Enemy")
        damagedSystem(entity, otherEntity)
    if (otherEntity.component[Type].getType() == "Player" || otherEntity.component[Type].getType() == "Wall")
        noMoveSystem(entity, otherEntity)
    */
}

void collisionEnemy(Entity entity, Entity otherEntity)
{
    /*
    if (otherEntity.component[Type].getType() == "Projectile_Enemy" || otherEntity.component[Type].getType() == "Enemy")
        return;
    if (otherEntity.component[Type].getType() == "Player" || otherEntity.component[Type].getType() == "Projectile_Player")
        damagedSystem(entity, otherEntity)
    if (otherEntity.component[Type].getType() == "Wall")
        noMoveSystem(entity, otherEntity)
    */
}

void collisionProjectile(Entity entity, Entity otherEntity)
{
    /*
    if (otherEntity.component[Type].getType() == "Projectile_Player" || otherEntity.component[Type].getType() == "EPlayer")
        return;
    if (otherEntity.component[Type].getType() == "Enemy" || otherEntity.component[Type].getType() == "Projectile_Player")
        damagedSystem(entity, otherEntity)
    if (otherEntity.component[Type].getType() == "Wall")
        destroy(entity)
    */
}

void collisionSystem(Entity entity, std::vector<Entity> entities)
{
    /*
    if !entity.component.has(Speed, Velocity, Position)
        return;
    for ent in entities {
        if !ent.component.has(HitBox) || ent.component[ID].getID() == entity.component[ID].getID()
            continues;
        if ent.component[HitBox].getHitBox() && entity.component[HitBox].getHitBox()
            map[entity.component[Type].getType()]()
    }
    */
}

void iaSystem(Entity entity)
{
}

void renderSystem(Entity entity)
{
}
