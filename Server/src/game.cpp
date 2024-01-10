/*
** EPITECH PROJECT, 2024
** 2
** File description:
** game
*/

#include "entities.hpp"
#include "server.hpp"


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
    }
}
