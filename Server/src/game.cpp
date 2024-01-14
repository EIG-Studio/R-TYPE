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

void Server::checkPlayerHealth(Registry& registry)
{
    try {
        std::vector<Entity> players = registry.getListEntities(Player);
        for (auto& player : players) {
            if (registry.hasComponent(player, HealthPoint{})) {
                HealthPoint& health = registry.getComponent(player, HealthPoint{});
                if (health.getHealthPoint() <= 0) {
                    addMessage("LOSE\n");
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Server::spawnBoss(Registry& registry)
{
    Entity score = registry.getFirstEntityOfType(EntityType::HUD);
    if (!registry.hasComponent(score, ScorePoint{}))
        return;
    ScorePoint& scorePoint = registry.getComponent(score, ScorePoint{});
    if (scorePoint.getScorePoint() >= 10 && m_spawnBoss == 0) {
        createBoss(registry);
        m_spawnBoss = 1;
    } else if (m_spawnBoss == 1 && !registry.hasEntityType(Boss)) {
        std::cout << "Boss killed" << std::endl;
        addMessage("WIN\n");
    }
}

void Server::spawnPowerUp(Registry& registry)
{
    Entity score = registry.getFirstEntityOfType(EntityType::HUD);
    if (!registry.hasComponent(score, ScorePoint{}))
        return;
    ScorePoint& scorePoint = registry.getComponent(score, ScorePoint{});
    if (scorePoint.getScorePoint() >= 20 && m_spawnPowerUp == 0) {
        createPowerUp(registry, 400, 300);
        m_spawnPowerUp = 1;
    }
}

// ### Enemy Move

void Server::enemyMoveLevel1(Registry& registry, Entity& entity, std::size_t id)
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

void Server::enemyMoveLevel2(Registry& registry, Entity& enemy, std::size_t id)
{
    Position& positionComponent = registry.getComponent(enemy, Position());
    Clock& enemyClock = registry.getComponent(enemy, Clock{});
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

    int deltaY = randomPlayerPos.getPosition().second - positionComponent.getPosition().second;
    int futureEnemyPosY = positionComponent.getPosition().second;
    int threshold = registry.getComponent(enemy, Speed{}).getSpeed();
    int enemySpeed = threshold;

    if (std::abs(deltaY) > threshold) {
        if (futureEnemyPosY < randomPlayerPos.getPosition().second)
            futureEnemyPosY += enemySpeed;
        else
            futureEnemyPosY -= enemySpeed;
    } else if (enemyClock.getClock() > 3) {
        createEnemyBullet(registry, positionComponent.getPosition().first - 1, futureEnemyPosY);
        enemyClock.restartClock();
    }

    positionComponent.setPosition(std::make_pair(positionComponent.getPosition().first - 1 * enemySpeed, futureEnemyPosY));
    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(enemy, id);
}

// ### Boss Move

void Server::bossMoveLevel1(Registry& registry, Entity& entity, std::size_t id)
{
    int bossSpeed = registry.getComponent(entity, Speed{}).getSpeed();
    int threshold = bossSpeed;
    Position& bossPos = registry.getComponent(entity, Position());

    // boss waiting goes too far
    if (bossPos.getPosition().first <= 600 && m_bossPhase == 1 && !m_bossIsAttacking) {
        m_bossWaiting = false;
        bossPos.setPosition(std::make_pair(600, bossPos.getPosition().second));
        std::cout << "TEST3\n";
    } else if (bossPos.getPosition().first >= -170 && m_bossPhase == 2 && !m_bossIsAttacking) {
        m_bossWaiting = false;
        bossPos.setPosition(std::make_pair(-170, bossPos.getPosition().second));
        std::cout << "TEST4\n";
    }

    // boss stop attacking
    if (bossPos.getPosition().first <= -450 && m_bossPhase == 1) {
        m_bossWaiting = true;
        m_bossIsAttacking = false;
        m_bossPhase = 2;
    } else if (bossPos.getPosition().first >= 750 && m_bossPhase == 2) {
        m_bossWaiting = true;
        m_bossIsAttacking = false;
        m_bossPhase = 1;
    }

    Entity randomPlayer = registry.getFirstEntityOfType(EntityType::Player);
    Position randomPlayerPos = registry.getComponent(randomPlayer, Position{});

    int deltaY = randomPlayerPos.getPosition().second - bossPos.getPosition().second;
    int futureBossPosY = bossPos.getPosition().second;

    if (std::abs(deltaY) > threshold && !m_bossIsAttacking) {
        if (futureBossPosY < randomPlayerPos.getPosition().second)
            futureBossPosY += bossSpeed;
        else
            futureBossPosY -= bossSpeed;
    } else if (!m_bossWaiting) {
        m_bossIsAttacking = true;
    }

    // boss moves
    if (!m_bossIsAttacking && m_bossPhase == 1)
        bossPos.setPosition(std::make_pair(bossPos.getPosition().first - bossSpeed, futureBossPosY));
    else if (!m_bossIsAttacking && m_bossPhase == 2)
        bossPos.setPosition(std::make_pair(bossPos.getPosition().first + bossSpeed, futureBossPosY));
    else if (m_bossPhase == 1 && !m_bossWaiting)
        bossPos.setPosition(std::make_pair(bossPos.getPosition().first - bossSpeed * 5, futureBossPosY));
    else if (m_bossPhase == 2 && !m_bossWaiting)
        bossPos.setPosition(std::make_pair(bossPos.getPosition().first + bossSpeed * 5, futureBossPosY));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(bossPos.getPosition().first) + " " +
                         std::to_string(futureBossPosY) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}


void Server::bossMoveLevel2(Registry& registry, Entity& entity, std::size_t id)
{
    int bossSpeed = registry.getComponent(entity, Speed{}).getSpeed();
    int threshold = bossSpeed;
    Position& bossPos = registry.getComponent(entity, Position());

    // boss waiting goes too far
    if (bossPos.getPosition().first <= 600 && m_bossPhase == 1 && !m_bossIsAttacking) {
        m_bossWaiting = false;
        bossPos.setPosition(std::make_pair(600, bossPos.getPosition().second));
    } else if (bossPos.getPosition().first >= -170 && m_bossPhase == 2 && !m_bossIsAttacking) {
        m_bossWaiting = false;
        bossPos.setPosition(std::make_pair(-170, bossPos.getPosition().second));
    }

    // boss stop attacking
    if (bossPos.getPosition().first <= -450 && m_bossPhase == 1) {
        m_bossWaiting = true;
        m_bossIsAttacking = false;
        m_bossPhase = 2;
    } else if (bossPos.getPosition().first >= 750 && m_bossPhase == 2) {
        m_bossWaiting = true;
        m_bossIsAttacking = false;
        m_bossPhase = 1;
    }

    Entity randomPlayer = registry.getFirstEntityOfType(EntityType::Player);
    Position randomPlayerPos = registry.getComponent(randomPlayer, Position{});

    int deltaY = randomPlayerPos.getPosition().second - bossPos.getPosition().second;
    int futureBossPosY = bossPos.getPosition().second;

    if (std::abs(deltaY) > threshold && !m_bossIsAttacking) {
        if (futureBossPosY < randomPlayerPos.getPosition().second)
            futureBossPosY += bossSpeed;
        else
            futureBossPosY -= bossSpeed;
    } else if (!m_bossWaiting) {
        m_bossIsAttacking = true;
    }

    // boss moves
    if (!m_bossIsAttacking && m_bossPhase == 1)
        bossPos.setPosition(std::make_pair(bossPos.getPosition().first - bossSpeed, futureBossPosY));
    else if (!m_bossIsAttacking && m_bossPhase == 2)
        bossPos.setPosition(std::make_pair(bossPos.getPosition().first + bossSpeed, futureBossPosY));
    else if (m_bossPhase == 1 && !m_bossWaiting)
        bossPos.setPosition(std::make_pair(bossPos.getPosition().first - bossSpeed * 5, futureBossPosY));
    else if (m_bossPhase == 2 && !m_bossWaiting)
        bossPos.setPosition(std::make_pair(bossPos.getPosition().first + bossSpeed * 5, futureBossPosY));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(bossPos.getPosition().first) + " " +
                         std::to_string(futureBossPosY) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

// ###

void Server::level1Loop(Registry& registry, std::vector<Entity> enemies, std::vector<Entity> boss)
{
    for (auto& enemy : enemies) {
        m_registeryMutex.lock();
        enemyMoveLevel1(registry, enemy, registry.getComponent(enemy, ID{}).getID());
        m_registeryMutex.unlock();
    }
    for (auto& entity : boss) {
        m_registeryMutex.lock();
        bossMoveLevel1(registry, entity, registry.getComponent(entity, ID{}).getID());
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
        spawnPowerUp(registry);
        m_registeryMutex.unlock();
    }
}

void Server::level2Loop(Registry& registry, std::vector<Entity> enemies, std::vector<Entity> boss)
{
    for (auto& enemy : enemies) {
        m_registeryMutex.lock();
        enemyMoveLevel2(registry, enemy, registry.getComponent(enemy, ID{}).getID());
        m_registeryMutex.unlock();
    }
    for (auto& entity : boss) {
        m_registeryMutex.lock();
        bossMoveLevel2(registry, entity, registry.getComponent(entity, ID{}).getID());
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
        spawnPowerUp(registry);
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
        std::vector<Entity> players = registry.getListEntities(Player);
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
