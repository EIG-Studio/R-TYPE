/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** createEntity
*/

#include "createEntity.hpp"

#include <iostream>

void updatePosition(Registry& registry, int id, int xPos, int yPos)
{
    try {
        Entity entity = registry.getEntity(id);
        if (registry.hasComponent(entity, Position{})) {
            Position& entityPos = registry.getComponent(entity, Position{});
            entityPos.setPosition(std::make_pair(xPos, yPos));
            registry.setEntity(entity, id);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in updatePosition: " << e.what() << std::endl;
    }
}

void updateHealth(Registry& registry, int id, int health)
{
    try {
        Entity entity = registry.getEntity(id);
        if (registry.hasComponent(entity, HealthPoint{})) {
            HealthPoint& entityPos = registry.getComponent(entity, HealthPoint{});
            entityPos.setHealthPoint(health);
            registry.setEntity(entity, id);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in updateHealth: " << e.what() << std::endl;
    }
}

void createPlayer(Registry& registry, int id, int xPos, int yPos, int healthPoint)
{
    if (registry.hasEntity(id))
        return;
    Entity player = registry.createEntityWithID(id);
    player = registry.addComponent(player, Position(std::make_pair(xPos, yPos)));
    player = registry.addComponent(player, HealthPoint(healthPoint));
    player = registry.addComponent(player, Renderer("../Client/assets/Cars/189.png"));
    player = registry.addComponent(player, Type(std::any_cast<EntityType>(Player)));
    player = registry.addComponent(
        player,
        Size(std::make_pair(
            103 / registry.getComponent(player, Renderer{}).getRenderer().getLocalBounds().width,
            56.25 / registry.getComponent(player, Renderer{}).getRenderer().getLocalBounds().height)));
    registry.setEntity(player, id);
}

void createEnemy(Registry& registry, int id, int xPos, int yPos)
{
    Entity enemy = registry.createEntityWithID(id);
    enemy = registry.addComponent(enemy, Position(std::make_pair(xPos, yPos)));
    enemy = registry.addComponent(enemy, Renderer("../Client/assets/Cars/cars/190.png"));
    enemy = registry.addComponent(enemy, Type(std::any_cast<EntityType>(Enemy)));
    enemy = registry.addComponent(
        enemy,
        Size(std::make_pair(
            103 / registry.getComponent(enemy, Renderer{}).getRenderer().getLocalBounds().width,
            56.25 / registry.getComponent(enemy, Renderer{}).getRenderer().getLocalBounds().height)));

    Position enemyPos = registry.getComponent(enemy, Position{});
    std::pair<int, int> pairPos = enemyPos.getPosition();

    std::cout << "Enemy created pos: " << pairPos.first << " " << pairPos.second << '\n';
}

void createBoss(Registry& registry, int id, int xPos, int yPos)
{
    Entity boss = registry.createEntityWithID(id);
    boss = registry.addComponent(boss, Position(std::make_pair(xPos, yPos)));
    boss = registry.addComponent(boss, Renderer("../Client/assets/Boss/v-police.png"));
    boss = registry.addComponent(boss, Type(std::any_cast<EntityType>(Enemy)));
    boss = registry.addComponent(boss, Size(std::make_pair(2, 2)));

    Position bossPos = registry.getComponent(boss, Position{});
    std::pair<int, int> pairPos = bossPos.getPosition();

    std::cout << "Boss created pos: " << pairPos.first << " " << pairPos.second << '\n';
}

void createPlayerProjectile(Registry& registry, int id, int xPos, int yPos)
{
    std::cout << "Player projectile created" << std::endl;
    Entity playerProjectile = registry.createEntityWithID(id);
    playerProjectile = registry.addComponent(playerProjectile, Position(std::make_pair(xPos, yPos)));
    playerProjectile = registry.addComponent(playerProjectile, Renderer("../Client/assets/Cars/movement parts/thruster/flame.png"));
    playerProjectile = registry.addComponent(playerProjectile, Type(std::any_cast<EntityType>(Player_Projectile)));
    playerProjectile = registry.addComponent(
        playerProjectile,
        Size(std::make_pair(
            68.5 / registry.getComponent(playerProjectile, Renderer{}).getRenderer().getLocalBounds().width,
            21.25 / registry.getComponent(playerProjectile, Renderer{}).getRenderer().getLocalBounds().height)));

    Position playerProjectilePos = registry.getComponent(playerProjectile, Position{});
    std::pair<int, int> pairPos = playerProjectilePos.getPosition();
    std::cout << "Player projectile created pos: " << pairPos.first << " " << pairPos.second << '\n';
}

void createPowerUp(Registry& registry, int id, int xPos, int yPos)
{
    std::cout << "Power up created" << std::endl;
    Entity powerUp = registry.createEntityWithID(id);
    powerUp = registry.addComponent(powerUp, Position(std::make_pair(xPos, yPos)));
    powerUp = registry.addComponent(powerUp, Renderer("../Client/assets/Cars/cars/191.png"));
    powerUp = registry.addComponent(powerUp, Type(std::any_cast<EntityType>(Power_Up)));
    powerUp = registry.addComponent(
        powerUp,
        Size(std::make_pair(
            68.5 / registry.getComponent(powerUp, Renderer{}).getRenderer().getLocalBounds().width,
            21.25 / registry.getComponent(powerUp, Renderer{}).getRenderer().getLocalBounds().height)));

    Position powerUpPos = registry.getComponent(powerUp, Position{});
    std::pair<int, int> pairPos = powerUpPos.getPosition();
    std::cout << "Power up created pos: " << pairPos.first << " " << pairPos.second << '\n';
}

void createHud(Registry& registry, int id, int dataScore)
{
    std::cout << "NEW_HUD" << std::endl;
    Entity hud = registry.createEntityWithID(id);
    ScorePoint score{};

    score.setScorePoint(dataScore);
    hud = registry.addComponent(hud, Type(std::any_cast<EntityType>(HUD)));
    hud = registry.addComponent(hud, score);
    registry.setEntity(hud, id);
}

void createScore(Registry& registry, int dataScore)
{
    if (registry.hasEntityType(HUD)) {
        std::cout << "SCORE " << std::endl;
        Entity score = registry.getScore();
        ID scoreId = registry.getComponent(score, ID{});
        ScorePoint& scorePoints = registry.getComponent(score, ScorePoint{});
        scorePoints.setScorePoint(dataScore);
        registry.setEntity(score, scoreId);
    } else {
        std::cout << "[LOG] NO SCORE" << std::endl;
    }
}
