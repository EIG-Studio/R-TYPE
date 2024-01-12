/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** command
*/

#include "components.hpp"
#include "entities.hpp"
#include "server.hpp"

#include <iostream>
#include <ostream>
#include <random>
#include <string>

#include <cstdlib>

void Server::playerMove(Registry& registry, COMMAND direction, std::size_t id)
{
    Entity entity = registry.getEntity(id);
    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());

    if (direction == DOWN)
        positionComponent.setPosition(std::make_pair(
            positionComponent.getPosition().first,
            positionComponent.getPosition().second + 1 * speedComponent.getSpeed()));
    else if (direction == RIGHT)
        positionComponent.setPosition(std::make_pair(
            positionComponent.getPosition().first + 1 * speedComponent.getSpeed(),
            positionComponent.getPosition().second));
    else if (direction == UP)
        positionComponent.setPosition(std::make_pair(
            positionComponent.getPosition().first,
            positionComponent.getPosition().second - 1 * speedComponent.getSpeed()));
    else if (direction == LEFT)
        positionComponent.setPosition(std::make_pair(
            positionComponent.getPosition().first - 1 * speedComponent.getSpeed(),
            positionComponent.getPosition().second));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

void Server::sendAllEntites(Registry& registry)
{
    for (auto& entity : registry.getListEntities()) {
        std::ostringstream oss;
        EntityType type = registry.getComponent(entity, Type{}).getEntityType();
        if (type == Player)
            oss << "NEW_PLAYER ";
        else if (type == Enemy)
            oss << "NEW_ENEMY ";
        else if (type == Player_Projectile)
            oss << "PLAYER_PROJECTILE ";
        else if (type == Enemy_Projectile)
            oss << "ENEMY_PROJECTILE ";
        else if (type == HUD)
            oss << "NEW_HUD ";
        else
            oss << "UNKNOWN ";

        if (type == Player || type == Enemy || type == Player_Projectile || type == Enemy_Projectile) {
            auto positionComponent = registry.getComponent(entity, Position{});
            auto xPosition = positionComponent.getPosition().first;
            auto yPosition = positionComponent.getPosition().second;

            auto sizeComponent = registry.getComponent(entity, Size{});
            auto xSize = sizeComponent.getSize().first;
            auto ySize = sizeComponent.getSize().second;

            auto healthPoint = registry.getComponent(entity, HealthPoint{});
            auto health = healthPoint.getHealthPoint();

            oss << registry.getComponent(entity, ID{}).getID() << " " << xPosition << " " << yPosition << " " << health
                << " " << xSize << " " << ySize << " " << registry.getComponent(entity, Type{}).getEntityType()
                << std::endl;
            addMessage(oss.str());
        } else if (type == HUD) {
            std::cout << "SCOOOREEEE\n";
            ScorePoint score = registry.getComponent(entity, ScorePoint{});
            oss << registry.getComponent(entity, ID{}).getID() << " " << std::to_string(score.getScorePoint()) << std::endl;
            addMessage(oss.str());
        }
    }
}

void Server::refreshClientRegistry(Registry& registry, int id)
{
    if (!registry.hasEntity(id)) {
        addMessage("DELETE " + std::to_string(id) + "\n");
    }
}

void Server::handleReceivedData(
    const boost::system::error_code& error,
    std::size_t bytesReceived,
    Registry& registry,
    boost::asio::ip::udp::endpoint& remoteEndpoint)
{
    if (!error && bytesReceived > 0) {
        TransferData receivedData{};
        std::memcpy(&receivedData, m_buffer, sizeof(receivedData));

        if (receivedData.command == SHOOT) {
            createBullet(registry, receivedData.args[0], receivedData.args[1]);
        } else if (receivedData.command == HUHUHU) {
            createBullet2(registry, receivedData.args[0], receivedData.args[1]);
        } else if (receivedData.command == LOGIN) {
            if (!m_gameStarted)
                m_gameStarted = startGame(registry);
            std::size_t id = createPlayer(registry);
            addClient(remoteEndpoint, id);
            createArrow(registry);
            sendAllEntites(registry);
        } else if (receivedData.command == UPDATE) {
            sendAllEntites(registry);
        } else if (receivedData.command == NEW_ENEMY) {
            createEnemy(registry);
        } else if (
            receivedData.command == DOWN || receivedData.command == UP || receivedData.command == LEFT ||
            receivedData.command == RIGHT) {
            playerMove(registry, receivedData.command, receivedData.args[0]);
        } else if (receivedData.command == REFRESH) {
            refreshClientRegistry(registry, receivedData.args[0]);
        } else if (receivedData.command == LEVEL) {
            m_currentLevel = receivedData.args[0];
        } else if (receivedData.command == ALIVE) {
            m_clientMutex.lock();
            for (Client& client : m_clients) {
                if (client == m_remoteEndpoint) {
                    client.setAlive(true);
                }
            }
            m_clientMutex.unlock();
        } else {
            std::ostringstream cmd;
            cmd << "Unknown command: " << receivedData.command << std::endl;
            addMessage(cmd.str());
        }
    }
}
