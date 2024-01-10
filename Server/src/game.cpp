/*
** EPITECH PROJECT, 2024
** 2
** File description:
** game
*/

#include "entities.hpp"
#include "server.hpp"

void Server::projectileCollision(Registry& registry, Entity& projectile, std::size_t projectile_id, std::vector<Entity> ennemies)
{
    Position projectile_pos_type = registry.getComponent(projectile, Position{});
    std::pair<int, int> projectile_pos = projectile_pos_type.getPosition();

    for (auto& ennemy : ennemies) {
        ID enemy_id = registry.getComponent(ennemy, ID{});
        Position enemy_pos_type = registry.getComponent(ennemy, Position{});
        std::pair<int, int> enemy_pos = enemy_pos_type.getPosition();

        if (projectile_pos.first < enemy_pos.first + 50 && projectile_pos.first + 50 > enemy_pos.first &&
            projectile_pos.second < enemy_pos.second + 50 && projectile_pos.second + 50 > enemy_pos.second) {

            registry.deleteById(projectile_id);
            addMessage("DELETE " + std::to_string(projectile_id) + "\n");
            registry.deleteById(enemy_id.getID());
            addMessage("DELETE " + std::to_string(enemy_id.getID()) + "\n");
        }
    }
}

void Server::playerProjectileMove(Registry& registry, Entity& entity, std::size_t id)
{
    Position& positionComponent = registry.getComponent(entity, Position());

    if (positionComponent.getPosition().first > 800) {
        registry.deleteById(id);
        addMessage("DELETE " + std::to_string(id) + "\n");
        return;
    }

    positionComponent.setPosition(
        std::make_pair(positionComponent.getPosition().first + 1 * 7, positionComponent.getPosition().second));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

void Server::ennemyMove(Registry& registry, Entity& entity, std::size_t id)
{
    float ennemySpeed = registry.getComponent(entity, Speed{}).getSpeed();
    Position& positionComponent = registry.getComponent(entity, Position());

    if (positionComponent.getPosition().first < -100) {
        addMessage("DELETE " + std::to_string(id) + "\n");
        registry.deleteById(id);
        this->createEnnemy(registry);
        return;
    }

    positionComponent.setPosition(
        std::make_pair(positionComponent.getPosition().first - 1 * ennemySpeed, positionComponent.getPosition().second));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

void Server::GameLoop(Registry& registry)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        m_registeryMutex.lock();
        std::vector<Entity> ennemies = registry.getListEnemies();
        std::vector<Entity> playersProjectiles = registry.getListPlayersProjectile();
        m_registeryMutex.unlock();
        for (auto& ennemy : ennemies) {
            m_registeryMutex.lock();
            ennemyMove(registry, ennemy, registry.getComponent(ennemy, ID{}).getID());
            m_registeryMutex.unlock();
        }
        for (auto& playerProjectile : playersProjectiles) {
            m_registeryMutex.lock();
            playerProjectileMove(registry, playerProjectile, registry.getComponent(playerProjectile, ID{}).getID());
            m_registeryMutex.unlock();
        }
        for (auto& playerProjectile : playersProjectiles) {
            m_registeryMutex.lock();
            projectileCollision(registry, playerProjectile, registry.getComponent(playerProjectile, ID{}).getID(), ennemies);
            m_registeryMutex.unlock();
        }
    }
}