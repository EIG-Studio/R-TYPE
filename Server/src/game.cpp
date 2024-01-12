/*
** EPITECH PROJECT, 2024
** 2
** File description:
** game
*/

#include "components.hpp"
#include "entities.hpp"
#include "server.hpp"

#include <iostream>

void Server::spawnBoss(Registry& registry)
{
    Entity score = registry.getScore();
    if (!registry.hasComponent(score, ScorePoint{}))
        return;
    ScorePoint& scorePoint = registry.getComponent(score, ScorePoint{});
    static int spawnBoss = 0;
    if (scorePoint.getScorePoint() == 1 && spawnBoss == 0) {
        createBoss(registry);
        spawnBoss = 1;
    }
}

void Server::projectileCollision(Registry& registry, Entity& projectile, std::size_t projectileId, std::vector<Entity> enemies)
{
}
//     Position projectilePosType = registry.getComponent(projectile, Position{});
//     std::pair<int, int> projectilePos = projectilePosType.getPosition();

//     for (auto& enemy : enemies) {
//         ID enemyId = registry.getComponent(enemy, ID{});
//         Position enemyPosType = registry.getComponent(enemy, Position{});
//         std::pair<int, int> enemyPos = enemyPosType.getPosition();

//         if (projectilePos.first < enemyPos.first + 50 && projectilePos.first + 50 > enemyPos.first &&
//             projectilePos.second < enemyPos.second + 50 && projectilePos.second + 50 > enemyPos.second) {

//             Entity score = registry.getScore();
//             ID scoreId = registry.getComponent(score, ID{});
//             ScorePoint& scorePoint = registry.getComponent(score, ScorePoint{});
//             scorePoint.setScorePoint((scorePoint.getScorePoint() + 1));
//             registry.setEntity(score, scoreId);
//             registry.getComponent(enemy, HealthPoint{})
//                 .setHealthPoint(
//                     registry.getComponent(enemy, HealthPoint{}).getHealthPoint() -
//                     registry.getComponent(projectile, Damage{}).getDamage());
//             registry.setEntity(enemy, enemyId);
//             registry.deleteById(projectileId);
//             addMessage("DELETE " + std::to_string(projectileId) + "\n");

//             if (registry.getComponent(enemy, HealthPoint{}).getHealthPoint() <= 0) {
//                 addMessage("DELETE " + std::to_string(enemyId.getID()) + "\n");
//                 addMessage("SCORE " + std::to_string(scorePoint.getScorePoint()) + "|");
//                 addMessage("PLAY_BOOM_ENEMIES");
//             }
//         }
//     }
// }

void Server::enemyMove(Registry& registry, Entity& entity, std::size_t id)
{
    float enemySpeed = registry.getComponent(entity, Speed{}).getSpeed();
    Position& positionComponent = registry.getComponent(entity, Position());

    if (positionComponent.getPosition().first < -100) {
        addMessage("DELETE " + std::to_string(id) + "\n");
        registry.deleteById(id);
    }

    positionComponent.setPosition(
        std::make_pair(positionComponent.getPosition().first - 2 * enemySpeed, positionComponent.getPosition().second));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

void Server::level1Loop(Registry& registry, std::vector<Entity> enemies, std::vector<Entity> playersProjectiles)
{
    for (auto& enemy : enemies) {
        m_registeryMutex.lock();
        enemyMove(registry, enemy, registry.getComponent(enemy, ID{}).getID());
        m_registeryMutex.unlock();
    }
    for (auto& playerProjectile : playersProjectiles) {
        m_registeryMutex.lock();
        std::ostringstream oss;
        oss << "NEW_POS " << registry.getComponent(playerProjectile, ID{}).getID() << " "
            << registry.getComponent(playerProjectile, Position{}).getPosition().first << " "
            << registry.getComponent(playerProjectile, Position{}).getPosition().second << "\n";
        addMessage(oss.str());
        projectileCollision(registry, playerProjectile, registry.getComponent(playerProjectile, ID{}).getID(), enemies);
        m_registeryMutex.unlock();
    }
    if ((1000.0 * (std::clock() - m_clock) / CLOCKS_PER_SEC) > 50 && enemies.size() < 5 && m_gameStarted) {

        std::cout << "New Enemy created in " << 1000.0 * (std::clock() - m_clock) / CLOCKS_PER_SEC << "ms\n";
        m_registeryMutex.lock();
        this->createEnemy(registry);
        m_registeryMutex.unlock();
        m_clock = std::clock();
    }
    if (m_gameStarted) {
        m_registeryMutex.lock();
        spawnBoss(registry);
        m_registeryMutex.unlock();
    }
}

void Server::gameLoop(Registry& registry)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        m_registeryMutex.lock();
        std::vector<Entity> enemies = registry.getListEnemies();
        std::vector<Entity> playersProjectiles = registry.getListPlayersProjectile();
        m_registeryMutex.unlock();

        if (m_currentLevel == 1)
            level1Loop(registry, enemies, playersProjectiles);
        std::vector<std::string> msg = registry.systemsManager();
        for (auto& message : msg) {
            addMessage(message);
        }
    }
}
