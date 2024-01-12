/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** createEntity
*/

#include "createEntity.hpp"

#include "components.hpp"

#include <iostream>

#include <cstdlib>

void updatePosition(Registry& registry, int id, int xPos, int yPos)
{
    try {
        Entity entity = registry.getEntity(id);
        if (registry.hasComponent(entity, Position{})) {
            Position& entityPos = registry.getComponent(entity, Position{});
            entityPos.setPosition(std::make_pair(xPos, yPos));
            registry.setEntity(entity, id);
        }
        if (registry.hasEntityType(Arrow_Player) && registry.hasEntityType(Player)) {
            Entity arrow = registry.getArrow();
            Position& arrowPos = registry.getComponent(arrow, Position{});
            std::pair<int, int> arrowPairPos = arrowPos.getPosition();
            Entity player = registry.getPlayer();
            Position& playerPos = registry.getComponent(player, Position{});
            std::pair<int, int> playerPairPos = playerPos.getPosition();
            arrowPos.setPosition(std::make_pair(playerPairPos.first + 46, playerPairPos.second - 30));
            registry.setEntity(arrow, registry.getComponent(arrow, ID{}).getID());
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
    boss = registry.addComponent(boss, Type(std::any_cast<EntityType>(Boss)));
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

void createPlayerProjectile2(Registry& registry, int id, int xPos, int yPos)
{
    std::cout << "Player projectile created" << std::endl;
    Entity playerProjectile = registry.createEntityWithID(id);
    playerProjectile = registry.addComponent(playerProjectile, Position(std::make_pair(xPos, yPos)));
    playerProjectile = registry.addComponent(playerProjectile, Renderer("../Client/assets/Cars/movement parts/thruster/flame2.png"));
    playerProjectile = registry.addComponent(playerProjectile, Type(std::any_cast<EntityType>(Player_Projectile)));
    playerProjectile = registry.addComponent(
        playerProjectile,
        Size(std::make_pair(
            68.5 / registry.getComponent(playerProjectile, Renderer{}).getRenderer().getLocalBounds().width,
            21.25 / registry.getComponent(playerProjectile, Renderer{}).getRenderer().getLocalBounds().height)));

    Position playerProjectilePos = registry.getComponent(playerProjectile, Position{});
    std::pair<int, int> pairPos = playerProjectilePos.getPosition();
    std::cout << "HUHUHU created pos: " << pairPos.first << " " << pairPos.second << '\n';
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

void createArrow(Registry& registry, int id)
{
    Entity player = registry.getPlayer();
    Position playerPos = registry.getComponent(player, Position{});

    Entity arrow = registry.createEntityWithID(id);
    arrow = registry.addComponent(arrow, Position(playerPos));
    arrow = registry.addComponent(arrow, Renderer("../Client/assets/arrow.png"));
    arrow = registry.addComponent(arrow, Size(std::make_pair(0.04, 0.04)));
    arrow = registry.addComponent(arrow, Type(std::any_cast<EntityType>(Arrow_Player)));

    registry.setEntity(arrow, id);
}
