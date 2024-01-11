/*
** EPITECH PROJECT, 2024
** 2
** File description:
** game
*/

#include "entities.hpp"
#include "server.hpp"

void Server::projectileCollision(Registry& registry, Entity& projectile, std::size_t projectile_id, std::vector<Entity> enemies)
{
    Position projectile_pos_type = registry.getComponent(projectile, Position{});
    std::pair<int, int> projectile_pos = projectile_pos_type.getPosition();

    for (auto& enemy : enemies) {
        ID enemy_id = registry.getComponent(enemy, ID{});
        Position enemy_pos_type = registry.getComponent(enemy, Position{});
        std::pair<int, int> enemy_pos = enemy_pos_type.getPosition();

        if (projectile_pos.first < enemy_pos.first + 50 && projectile_pos.first + 50 > enemy_pos.first &&
            projectile_pos.second < enemy_pos.second + 50 && projectile_pos.second + 50 > enemy_pos.second) {

            Entity score = registry.getScore();
            ID score_id = registry.getComponent(score, ID{});
            ScorePoint& score_point = registry.getComponent(score, ScorePoint{});
            score_point.setScorePoint((score_point.getScorePoint() + 1));
            registry.setEntity(score, score_id);
            // std::cout << std::to_string(score_point.getScorePoint()) << std::endl;
            registry.deleteById(projectile_id);

            addMessage("DELETE " + std::to_string(projectile_id) + "\n");
            registry.deleteById(enemy_id.getID());
            addMessage("DELETE " + std::to_string(enemy_id.getID()) + "\n");
            addMessage("PLAY_BOOM_ENEMIES");
        }
    }
}

void Server::playerProjectileMove(Registry& registry, Entity& entity, std::size_t id)
{
    if (registry.hasComponent(entity, Position()) == false || registry.hasComponent(entity, Speed()) == false)
        return;
    Position& positionComponent = registry.getComponent(entity, Position());
    int speed = registry.getComponent(entity, Speed()).getSpeed();

    if (positionComponent.getPosition().first > 800) {
        registry.deleteById(id);
        addMessage("DELETE " + std::to_string(id) + "\n");
        return;
    }

    positionComponent.setPosition(
        std::make_pair(positionComponent.getPosition().first + 1 * speed, positionComponent.getPosition().second));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

void Server::enemyMove(Registry& registry, Entity& entity, std::size_t id)
{
    float enemySpeed = registry.getComponent(entity, Speed{}).getSpeed();
    Position& positionComponent = registry.getComponent(entity, Position());

    if (positionComponent.getPosition().first < -100) {
        addMessage("DELETE " + std::to_string(id) + "\n");
        registry.deleteById(id);
        // for (auto& client : m_clients) {
        //     damageThePlayer(registry, 3, client.getId());
        // }
    }

    positionComponent.setPosition(
        std::make_pair(positionComponent.getPosition().first - 1 * enemySpeed, positionComponent.getPosition().second));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

void Server::GameLoop(Registry& registry)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        m_registeryMutex.lock();
        std::vector<Entity> enemies = registry.getListEnemies();
        std::vector<Entity> playersProjectiles = registry.getListPlayersProjectile();
        m_registeryMutex.unlock();
        for (auto& enemy : enemies) {
            m_registeryMutex.lock();
            enemyMove(registry, enemy, registry.getComponent(enemy, ID{}).getID());
            m_registeryMutex.unlock();
        }
        for (auto& playerProjectile : playersProjectiles) {
            m_registeryMutex.lock();
            playerProjectileMove(registry, playerProjectile, registry.getComponent(playerProjectile, ID{}).getID());
            projectileCollision(registry, playerProjectile, registry.getComponent(playerProjectile, ID{}).getID(), enemies);
            m_registeryMutex.unlock();
        }
        if ((1000.0 * (std::clock() - m_clock) / CLOCKS_PER_SEC) > 50 && enemies.size() < 5 && gameStarted) {

            std::cout << "New Enemy created in " << 1000.0 * (std::clock() - m_clock) / CLOCKS_PER_SEC << "ms\n";
            m_registeryMutex.lock();
            this->createEnemy(registry);
            m_registeryMutex.unlock();
            m_clock = std::clock();
        }
    }
}