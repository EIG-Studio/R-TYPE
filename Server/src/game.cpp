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
    if (scorePoint.getScorePoint() == 0 && spawnBoss == 0) {
        createBoss(registry);
        Entity boss = registry.getBoss();
        std::size_t bossId = registry.getComponent(boss, ID{}).getID();
        std::cout << "Boss created with id: " << bossId << std::endl;
        enemyMove(registry, boss, bossId);
        spawnBoss = 1;
    }
}

void Server::enemyMove(Registry& registry, Entity& entity, std::size_t id)
{
    float enemySpeed = registry.getComponent(entity, Speed{}).getSpeed();
    Position& positionComponent = registry.getComponent(entity, Position());

    if (positionComponent.getPosition().first < -100) {
        addMessage("DELETE " + std::to_string(id) + "\n");
        registry.deleteById(id);
    }
    positionComponent.setPosition(
        std::make_pair(positionComponent.getPosition().first - 1 * enemySpeed, positionComponent.getPosition().second));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

void Server::enemyShootAndMove(Registry& registry, Entity& entity, std::size_t id)
{
    float enemySpeed = registry.getComponent(entity, Speed{}).getSpeed();
    Position& positionComponent = registry.getComponent(entity, Position());

    if (positionComponent.getPosition().first < -100) {
        addMessage("DELETE " + std::to_string(id) + "\n");
        registry.deleteById(id);
    }

    std::vector<Entity> players = registry.getListEntities(Player);
    Entity randomPlayer;
    Position randomPlayer_pos;
    if (!players.empty()) {
        srand(time(0));
        int randomIndex = rand() % players.size();
        randomPlayer = players[randomIndex];
        randomPlayer_pos = registry.getComponent(randomPlayer, Position{});
    }

    if (positionComponent.getPosition().second < randomPlayer_pos.getPosition().second)
        positionComponent.setPosition(
            std::make_pair(positionComponent.getPosition().first - 1 * enemySpeed, positionComponent.getPosition().second + 8));
    else if (positionComponent.getPosition().second > randomPlayer_pos.getPosition().second)
        positionComponent.setPosition(
            std::make_pair(positionComponent.getPosition().first - 1 * enemySpeed, positionComponent.getPosition().second - 8));
    else
        positionComponent.setPosition(
            std::make_pair(positionComponent.getPosition().first - 1 * enemySpeed, positionComponent.getPosition().second));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

void Server::Level1_Loop(Registry& registry, std::vector<Entity> enemies)
{
    for (auto& enemy : enemies) {
        m_registeryMutex.lock();
        enemyMove(registry, enemy, registry.getComponent(enemy, ID{}).getID());
        m_registeryMutex.unlock();
    }
    if ((1000.0 * (std::clock() - m_clock) / CLOCKS_PER_SEC) > 20 && enemies.size() < 5 && m_gameStarted) {
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

void Server::Level2_Loop(Registry& registry, std::vector<Entity> enemies)
{
    for (auto& enemy : enemies) {
        m_registeryMutex.lock();
        enemyShootAndMove(registry, enemy, registry.getComponent(enemy, ID{}).getID());
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

void Server::GameLoop(Registry& registry)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        m_registeryMutex.lock();
        std::vector<Entity> enemies = registry.getListEntities(Enemy);
        m_registeryMutex.unlock();

        if (m_currentLevel == 1)
            Level1_Loop(registry, enemies);
        else
            Level2_Loop(registry, enemies);
        std::vector<std::string> msg = registry.systemsManager();
        for (auto& message : msg) {
            addMessage(message);
        }
    }
}
