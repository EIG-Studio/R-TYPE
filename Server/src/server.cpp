/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "server.hpp"

#include "entities.hpp"

#include <iostream>

void Server::PlayerLoop(Registry& registry)
{
    while (true) {
        std::vector<Client> clients;
        m_clientMutex.lock();
        for (auto& client : m_clients) {
            if (registry.hasEntity(client.getId())) {
                clients.push_back(client);
            }
        }
        m_clients = clients;
        m_clientMutex.unlock();
        if (m_clients.empty() && m_gameStarted) {
            std::vector<std::size_t> ids;
            m_registeryMutex.lock();
            for (Entity& entity : registry.getListEntities()) {
                ids.push_back(registry.getComponent(entity, ID()).getID());
            }
            for (std::size_t id : ids) {
                registry.deleteById(id);
            }
            m_spawnBoss = 0;
            m_registeryMutex.unlock();
            m_gameStarted = false;
            std::cout << "No more clients, reset done" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        for (auto& client : m_clients) {
            std::cout << "Client " << client.getEndpoint() << " is alive: " << client.isAlive() << std::endl;
            if (!client.isAlive()) {
                addMessage("DELETE " + std::to_string(client.getId()) + "\n");
                m_registeryMutex.lock();
                registry.deleteById(client.getId());
                m_registeryMutex.unlock();
            }
            m_clientMutex.lock();
            client.setAlive(false);
            m_clientMutex.unlock();
        }
    }
}

bool Server::startGame(Registry& registry)
{
    std::cout << "Game started" << std::endl;
    createEnemy(registry);
    createEnemy(registry);
    createEnemy(registry);
    createEnemy(registry);
    createWall(registry, 800, -10, 100, 600);
    createWall(registry, -100, -10, 90, 600);
    createWall(registry, -10, -100, 800, 100);
    createWall(registry, -10, 625, 800, 100);

    Entity entityScore = registry.createEntity();
    ID scoreId = registry.getComponent(entityScore, ID());
    Type type = HUD;
    ScorePoint score{};
    score.setScorePoint(0);
    entityScore = registry.addComponent(entityScore, type);
    entityScore = registry.addComponent(entityScore, score);
    addMessage("NEW_HUD " + std::to_string(scoreId.getID()) + " " + std::to_string(score.getScorePoint()) + "\n");
    registry.setEntity(entityScore, scoreId);
    std::cout << "CREATE\n";
    return true;
}
