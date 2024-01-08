/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** command
*/


#include "SFML/Graphics/Sprite.hpp"
#include "components.hpp"
#include "entities.hpp"
#include "server.hpp"

#include <algorithm>
#include <ostream>
#include <random>
#include <string>

void Server::createPlayer(Registry& registry)
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

    // m_ennemyMutex.lock();
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
    // m_ennemyMutex.unlock();
    addMessage(newPlayer2.str());
}

void Server::createBullet(Registry& registry, std::string& command)
{
    std::istringstream iss(command);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    Entity entity = registry.createEntity();
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(std::stof(tokens[1]), std::stof(tokens[2])));
    Speed speedComponent(7);
    Type typeComponent = std::any_cast<EntityType>(Player_Projectile);

    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);

    std::ostringstream newPlayerProjectile;
    newPlayerProjectile << "PLAYER_PROJECTILE " << static_cast<int>(registry.getComponent(entity, idComponent).getID())
                        << " " << positionComponent.getPosition().first << " " << positionComponent.getPosition().second
                        << " " << typeComponent << "\n";
    addMessage(newPlayerProjectile.str());
}


void Server::addMessage(const std::string& message)
{
    this->m_mutex.lock();
    m_messages.emplace_front(std::make_pair(message, 0));
    this->m_mutex.unlock();
}

void Server::goUp(Registry& registry, std::string& command)
{
    std::string id = " ";
    if (command.find("UP") + 2 < command.size()) {
        id = command.substr(command.find("UP") + 3);
    }
    Entity entity = registry.getEntity(std::stoi(id));
    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());

    positionComponent.setPosition(
        std::
            make_pair(positionComponent.getPosition().first, positionComponent.getPosition().second - 1 * speedComponent.getSpeed()));
    std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
                         std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, std::stoi(id));
}

void Server::goDown(Registry& registry, std::string& command)
{
    std::string id = " ";
    if (command.find("DOWN") + 4 < command.size()) {
        id = command.substr(command.find("DOWN") + 5);
    }
    Entity entity = registry.getEntity(std::stoi(id));
    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());

    positionComponent.setPosition(
        std::
            make_pair(positionComponent.getPosition().first, positionComponent.getPosition().second + 1 * speedComponent.getSpeed()));
    std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
                         std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, std::stoi(id));
}

void Server::goRight(Registry& registry, std::string& command)
{
    std::string id = " ";
    if (command.find("RIGHT") + 5 < command.size()) {
        id = command.substr(command.find("RIGHT") + 6);
    }
    Entity entity = registry.getEntity(std::stoi(id));

    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());

    positionComponent.setPosition(std::make_pair(
        positionComponent.getPosition().first + 1 * speedComponent.getSpeed(),
        positionComponent.getPosition().second));
    std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
                         std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, std::stoi(id));
}

void Server::goLeft(Registry& registry, std::string& command)
{
    std::string id = " ";
    if (command.find("LEFT") + 4 < command.size()) {
        id = command.substr(command.find("LEFT") + 5);
    }
    Entity entity = registry.getEntity(std::stoi(id));
    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());


    positionComponent.setPosition(std::make_pair(
        positionComponent.getPosition().first - 1 * speedComponent.getSpeed(),
        positionComponent.getPosition().second));
    std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
                         std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, std::stoi(id));
}

// void Server::ennemyMove(Registry& registry, std::string& command)
// {
//     std::string id = " ";
//     if (command.find("MOVE_ENNEMIES") + 13 < command.size()) {
//         id = command.substr(command.find("MOVE_ENNEMIES") + 14);
//     }
//     Entity entity = registry.getEntity(std::stoi(id));
//     float ennemySpeed = registry.getComponent(entity, Speed{}).getSpeed();
//     Position& positionComponent = registry.getComponent(entity, Position());

//     if (positionComponent.getPosition().first < -100) {
//         addMessage("DELETE_ENNEMY " + id);
//         registry.deleteById(std::stoi(id));
//         this->createEnnemy(registry);
//         return;
//     }
//     positionComponent.setPosition(
//         std::make_pair(positionComponent.getPosition().first - 1 * ennemySpeed, positionComponent.getPosition().second));

//     std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
//                          std::to_string(positionComponent.getPosition().second) + "\n";
//     addMessage(newPos);
//     registry.setEntity(entity, std::stoi(id));
// }

// void Server::playerProjectileMove(Registry& registry, std::string& command)
// {
//     std::string id = std::string("");
//     if (command.find("MOVE_PROJECTILE") + 15 < command.size()) {
//         id = command.substr(command.find("MOVE_PROJECTILE") + 16);
//     }
//     Entity entity = registry.getEntity(std::stoi(id));
//     Position& positionComponent = registry.getComponent(entity, Position());

//     if (positionComponent.getPosition().first > 800) {
//         registry.deleteById(std::stoi(id));
//         addMessage("DELETE_PROJECTILE " + id);
//         return;
//     }

//     positionComponent.setPosition(
//         std::make_pair(positionComponent.getPosition().first + 1 * 7, positionComponent.getPosition().second));

//     std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
//                          std::to_string(positionComponent.getPosition().second) + "\n";
//     addMessage(newPos);
//     registry.setEntity(entity, std::stoi(id));
// }

void Server::sendAllEntites(Registry& registry)
{
    std::ostringstream oss;
    for (auto& entity : registry.getListEntities()) {
        oss << "UPDATE" << std::endl;
        auto positionComponent = registry.getComponent(entity, Position{});
        auto xPosition = positionComponent.getPosition().first;
        auto yPosition = positionComponent.getPosition().second;

        oss << registry.getComponent(entity, ID{}).getID() << " " << xPosition << " " << yPosition << " "
            << registry.getComponent(entity, Type{}).getEntityType() << std::endl;
        addMessage(oss.str());
    }
}

void Server::handleReceivedData(
    const boost::system::error_code& error,
    std::size_t bytesReceived,
    Registry& registry,
    boost::asio::ip::udp::endpoint& remoteEndpoint)
{
    if (!error && bytesReceived > 0) {
        std::cout << "Received: " << m_recvBuf.data() << std::endl;
        std::string command = std::string(m_recvBuf.data());

        if (command.find("SHOOT") == 0) {
            createBullet(registry, command);
        } else if (command.find("LOGIN") == 0) {
            addClient(remoteEndpoint);
            createPlayer(registry);
        } else if (command.find("UPDATE") == 0) {
            sendAllEntites(registry);
        } else if (command.find("NEW_ENNEMY") == 0) {
            createEnnemy(registry);
        } else if (command.find("EXIT") == 0) {
            // deletePlayer();
        } else if (command.find("RIGHT") == 0) {
            goRight(registry, command);
        } else if (command.find("LEFT") == 0) {
            goLeft(registry, command);
        } else if (command.find("UP") == 0) {
            goUp(registry, command);
        } else if (command.find("DOWN") == 0) {
            goDown(registry, command);
        } else {
            std::ostringstream cmd;
            cmd << "Unknown command: " << command << std::endl;
            addMessage(cmd.str());
        }
    }
}

void Server::handlePositionUpdate()
{
    std::string posString = m_recvBuf.data();
    std::istringstream iss(posString);
    std::vector<std::string> tokens;
    std::ostringstream newPos;
    std::string token;

    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    int newPosX = std::stoi(tokens[1]);
    int newPosY = std::stoi(tokens[2]);
    int moveSpeed = std::stoi(tokens[3]);
    int direction = std::stoi(tokens[4]);

    if (direction == 1)
        newPosY -= moveSpeed;
    else if (direction == 2)
        newPosX += moveSpeed;
    else if (direction == 3)
        newPosY += moveSpeed;
    else if (direction == 4)
        newPosX -= moveSpeed;
    newPos << "NEW_POS " << newPosX << " " << newPosY << "\n";
    addMessage(newPos.str());
    m_recvBuf.fill(0);
}
