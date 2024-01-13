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
    if (scorePoint.getScorePoint() >= 0 && m_spawnBoss == 0) {
        createBoss(registry);
        m_spawnBoss = 1;
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

void Server::bossMove(Registry& registry, Entity& entity, std::size_t id)
{
    int bossSpeed = registry.getComponent(entity, Speed{}).getSpeed();
    int threshold = bossSpeed;
    Position& bossPos = registry.getComponent(entity, Position());

    if (bossPos.getPosition().first <= 500) {
        bossPos.setPosition(std::make_pair(500, bossPos.getPosition().second));
    }

    Entity randomPlayer = registry.getPlayer();
    Position randomPlayerPos = registry.getComponent(randomPlayer, Position{});

    int deltaY = randomPlayerPos.getPosition().second - bossPos.getPosition().second;
    int futureBossPosY = bossPos.getPosition().second;

    if (std::abs(deltaY) > threshold) {
        if (futureBossPosY < randomPlayerPos.getPosition().second)
            futureBossPosY += bossSpeed;
        else
            futureBossPosY -= bossSpeed;
    }

    bossPos.setPosition(std::make_pair(bossPos.getPosition().first - bossSpeed, futureBossPosY));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(bossPos.getPosition().first) + " " +
                         std::to_string(futureBossPosY) + "\n";
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
    Position randomPlayerPos;
    if (!players.empty()) {
        srand(time(nullptr));
        int randomIndex = rand() % players.size();
        randomPlayer = players[randomIndex];
        randomPlayerPos = registry.getComponent(randomPlayer, Position{});
    }

    if (positionComponent.getPosition().second < randomPlayerPos.getPosition().second)
        positionComponent.setPosition(
            std::make_pair(positionComponent.getPosition().first - 1 * enemySpeed, positionComponent.getPosition().second + 8));
    else if (positionComponent.getPosition().second > randomPlayerPos.getPosition().second)
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

void Server::bossShootAndMove(Registry& registry, Entity& entity, std::size_t id)
{
    float enemySpeed = registry.getComponent(entity, Speed{}).getSpeed();
    Position& positionComponent = registry.getComponent(entity, Position());

    if (positionComponent.getPosition().first <= 450) {
        positionComponent.setPosition(std::make_pair(450, positionComponent.getPosition().second));
    }
    if (positionComponent.getPosition().first < -100) {
        addMessage("DELETE " + std::to_string(id) + "\n");
        registry.deleteById(id);
    }

    std::vector<Entity> players = registry.getListEntities(Player);
    Entity randomPlayer;
    Position randomPlayerPos;
    if (!players.empty()) {
        srand(time(nullptr));
        int randomIndex = rand() % players.size();
        randomPlayer = players[randomIndex];
        randomPlayerPos = registry.getComponent(randomPlayer, Position{});
    }

    if (positionComponent.getPosition().second < randomPlayerPos.getPosition().second)
        positionComponent.setPosition(
            std::make_pair(positionComponent.getPosition().first - 1 * enemySpeed, positionComponent.getPosition().second + 8));
    else if (positionComponent.getPosition().second > randomPlayerPos.getPosition().second)
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

void Server::level1Loop(Registry& registry, std::vector<Entity> enemies, std::vector<Entity> boss)
{
    if (m_spawnBoss == 0) {
        for (auto& enemy : enemies) {
            m_registeryMutex.lock();
            enemyMove(registry, enemy, registry.getComponent(enemy, ID{}).getID());
            m_registeryMutex.unlock();
        }
    }
    for (auto& entity : boss) {
        m_registeryMutex.lock();
        bossMove(registry, entity, registry.getComponent(entity, ID{}).getID());
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

void Server::level2Loop(Registry& registry, std::vector<Entity> enemies, std::vector<Entity> boss)
{
    for (auto& enemy : enemies) {
        m_registeryMutex.lock();
        enemyShootAndMove(registry, enemy, registry.getComponent(enemy, ID{}).getID());
        m_registeryMutex.unlock();
    }
    for (auto& entity : boss) {
        m_registeryMutex.lock();
        bossShootAndMove(registry, entity, registry.getComponent(entity, ID{}).getID());
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
        std::vector<Entity> enemies = registry.getListEntities(Enemy);
        std::vector<Entity> boss = registry.getListEntities(Boss);
        m_registeryMutex.unlock();

        if (m_currentLevel == 1)
            level1Loop(registry, enemies, boss);
        else
            level2Loop(registry, enemies, boss);
        std::vector<std::string> msg = registry.systemsManager();
        for (auto& message : msg) {
            addMessage(message);
        }
    }
}
