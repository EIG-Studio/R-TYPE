/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** command
*/

#include "components.hpp"
#include "entities.hpp"
#include "server.hpp"

#include <ostream>
#include <random>
#include <string>

std::size_t Server::createPlayer(Registry& registry)
{
    Entity entity = registry.createEntity();
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(0, 0));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(5);
    Type typeComponent = std::any_cast<EntityType>(Player);

    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);

    std::ostringstream newPlayer;
    newPlayer << "NEW_PLAYER " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
              << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
              << sizeComponent.getSize().first << " " << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayer.str());
    return registry.getComponent(entity, idComponent).getID();
}

int randNb(int x, int y)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(x, y);
    return distrib(gen);
}

void Server::createEnnemy(Registry& registry)
{
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(randNb(1200, 2000), randNb(0, 500)));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(randNb(5, 10));
    Type typeComponent = std::any_cast<EntityType>(Enemy);

    Entity entity = registry.createEntity();
    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);

    std::ostringstream newPlayer2;
    newPlayer2 << "NEW_ENNEMY " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
               << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
               << sizeComponent.getSize().first << " " << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayer2.str());
}

void Server::createBullet(Registry& registry, int posx, int posy)
{

    Entity entity = registry.createEntity();
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(posx, posy));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(7);
    Type typeComponent = std::any_cast<EntityType>(Player_Projectile);

    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);

    std::ostringstream newPlayerProjectile;
    newPlayerProjectile << "PLAYER_PROJECTILE " << static_cast<int>(registry.getComponent(entity, idComponent).getID())
                        << " " << positionComponent.getPosition().first << " " << positionComponent.getPosition().second
                        << " " << sizeComponent.getSize().first << " " << sizeComponent.getSize().second << " "
                        << typeComponent << "\n";
    addMessage(newPlayerProjectile.str());
}

void Server::addMessage(const std::string& message)
{
    this->m_MessageMutex.lock();
    TransferData data{.command = EMPTY, .args = {0, 0, 0, 0}};
    std::istringstream iss(message);
    int i = 0;
    std::cout << "\033[1;32m"
              << "[SERVER]: \033[0m" << message;
    std::string word;
    iss >> word;
    data.command = getCommand(word);
    while (iss >> word) {
        try {
            data.args[i] = std::stoi(word);
        } catch (const std::exception& e) {
            data.args[i] = getType(word);
        }
        i++;
    }
    m_messages.emplace_front(data);
    this->m_MessageMutex.unlock();
}

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
            oss << "NEW_ENNEMY ";
        else if (type == Player_Projectile)
            oss << "PLAYER_PROJECTILE ";
        else if (type == Enemy_Projectile)
            oss << "ENEMY_PROJECTILE ";
        else
            oss << "UNKNOWN ";
        auto positionComponent = registry.getComponent(entity, Position{});
        auto xPosition = positionComponent.getPosition().first;
        auto yPosition = positionComponent.getPosition().second;

        auto sizeComponent = registry.getComponent(entity, Size{});
        auto xSize = sizeComponent.getSize().first;
        auto ySize = sizeComponent.getSize().second;

        oss << registry.getComponent(entity, ID{}).getID() << " " << xPosition << " " << yPosition << " " << xSize
            << " " << ySize << " " << registry.getComponent(entity, Type{}).getEntityType() << std::endl;
        addMessage(oss.str());
    }
}

void Server::refreshClientRegistry(Registry& registry, int id)
{
    if (!registry.hasEntity(id)) {
        addMessage("DELETE " + std::to_string(id) + "\n");
    }
}

bool Server::startGame(Registry& registry)
{
    std::cout << "Game started" << std::endl;
    createEnnemy(registry);
    createEnnemy(registry);
    createEnnemy(registry);
    createEnnemy(registry);
    return true;
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
        } else if (receivedData.command == LOGIN) {
            if (!gameStarted)
                gameStarted = startGame(registry);
            std::size_t id = createPlayer(registry);
            addClient(remoteEndpoint, id);
            sendAllEntites(registry);
        } else if (receivedData.command == UPDATE) {
            sendAllEntites(registry);
        } else if (receivedData.command == NEW_ENNEMY) {
            createEnnemy(registry);
        } else if (
            receivedData.command == DOWN || receivedData.command == UP || receivedData.command == LEFT ||
            receivedData.command == RIGHT) {
            playerMove(registry, receivedData.command, receivedData.args[0]);
        } else if (receivedData.command == REFRESH) {
            refreshClientRegistry(registry, receivedData.args[0]);
        } else if (receivedData.command == ALIVE) {
            m_ClientMutex.lock();
            for (Client& client : m_clients) {
                if (client == m_remoteEndpoint) {
                    client.setAlive(true);
                }
            }
            m_ClientMutex.unlock();
        } else {
            std::ostringstream cmd;
            cmd << "Unknown command: " << receivedData.command << std::endl;
            addMessage(cmd.str());
        }
    }
}
