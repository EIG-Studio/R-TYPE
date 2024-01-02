/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** command
*/

#include "command.hpp"

#include "SFML/Graphics/Sprite.hpp"
#include "components.hpp"
#include "entities.hpp"

#include <algorithm>
#include <ostream>
#include <string>

void Server::createPlayer(Registry& registry)
{
    Entity entity = registry.createEntity();
    ID idComponent = ID();
    std::cout << "id: " << idComponent.getID() << std::endl;
    Position positionComponent = Position(std::make_pair(0, 0));
    Renderer rendererComponent("../Client/assets/Cars/189_neutral.png");
    Speed speedComponent(5);
    Type typeComponent = std::any_cast<EntityType>(Player);

    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, rendererComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);

    std::ostringstream newPlayer;
    newPlayer << "NEW " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
              << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
              << typeComponent << "\n";
    addMessage(newPlayer.str());
}

void Server::createEnnemy(Registry& registry)
{
    Entity entity = registry.createEntity();
    ID idComponent = ID();
    std::cout << "id: " << idComponent.getID() << std::endl;
    Position positionComponent = Position(std::make_pair(0, 0));
    Renderer rendererComponent("../Client/assets/Cars/189_neutral.png");
    Speed speedComponent(5);
    Type typeComponent = std::any_cast<EntityType>(Enemy);

    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, rendererComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);

    std::ostringstream newPlayer2;
    newPlayer2 << "ENNEMY " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
               << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
               << typeComponent << "\n";
    addMessage(newPlayer2.str());
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
        std::cout << "id cmd: " << id << std::endl;
    }
    std::cout << "id: " << id << std::endl;
    Entity entity = registry.getEntity(std::stoi(id));
    std::cout << "id UP: " << registry.getComponent(entity, ID()).getID() << std::endl;
    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());

    std::cout << "pos: " << positionComponent.getPosition().first << " " << positionComponent.getPosition().second
              << std::endl;
    positionComponent.setPosition(
        std::
            make_pair(positionComponent.getPosition().first, positionComponent.getPosition().second - 1 * speedComponent.getSpeed()));
    std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
                         std::to_string(positionComponent.getPosition().second) + "\n";
    std::cout << "new pos: " << newPos << std::endl;
    addMessage(newPos);
    registry.setEntity(entity, std::stoi(id));
}

void Server::goDown(Registry& registry, std::string& command)
{
    std::string id = " ";
    if (command.find("DOWN") + 4 < command.size()) {
        id = command.substr(command.find("DOWN") + 5);
        std::cout << "id cmd: " << id << std::endl;
    }
    std::cout << "id: " << id << std::endl;
    Entity entity = registry.getEntity(std::stoi(id));
    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());

    positionComponent.setPosition(
        std::
            make_pair(positionComponent.getPosition().first, positionComponent.getPosition().second + 1 * speedComponent.getSpeed()));
    std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
                         std::to_string(positionComponent.getPosition().second) + "\n";
    std::cout << "new pos: " << newPos << std::endl;
    addMessage(newPos);
    registry.setEntity(entity, std::stoi(id));
}

void Server::goRight(Registry& registry, std::string& command)
{
    std::string id = " ";
    if (command.find("RIGHT") + 5 < command.size()) {
        id = command.substr(command.find("RIGHT") + 6);
        std::cout << "id cmd: " << id << std::endl;
    }
    std::cout << "id: " << id << std::endl;
    Entity entity = registry.getEntity(std::stoi(id));

    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());

    positionComponent.setPosition(std::make_pair(
        positionComponent.getPosition().first + 1 * speedComponent.getSpeed(),
        positionComponent.getPosition().second));
    std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
                         std::to_string(positionComponent.getPosition().second) + "\n";
    std::cout << "new pos: " << newPos << std::endl;
    addMessage(newPos);
    registry.setEntity(entity, std::stoi(id));
}

void Server::goLeft(Registry& registry, std::string& command)
{
    std::string id = " ";
    if (command.find("LEFT") + 4 < command.size()) {
        id = command.substr(command.find("LEFT") + 5);
        std::cout << "id cmd: " << id << std::endl;
    }
    std::cout << "id: " << id << std::endl;
    Entity entity = registry.getEntity(std::stoi(id));
    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());


    positionComponent.setPosition(std::make_pair(
        positionComponent.getPosition().first - 1 * speedComponent.getSpeed(),
        positionComponent.getPosition().second));
    std::string newPos = "NEW_POS " + id + " " + std::to_string(positionComponent.getPosition().first) + " " +
                         std::to_string(positionComponent.getPosition().second) + "\n";
    std::cout << "new pos: " << newPos;
    addMessage(newPos);
    registry.setEntity(entity, std::stoi(id));
}

void Server::sendAllEntites(Registry& registry)
{
    std::ostringstream oss;
    oss << "ALL_ENTITY\n";
    for (auto& entity : registry.getListEntities()) {
        oss << registry.getComponent(entity, ID{}).getID() << " "
            << registry.getComponent(entity, Position{}).getPosition().first << " "
            << registry.getComponent(entity, Position{}).getPosition().second << " "
            << registry.getComponent(entity, Type{}).getEntityType() << "\n";
    }
    addMessage(oss.str());
}

void Server::handleReceivedData(const boost::system::error_code& error, std::size_t bytesReceived, Registry& registry)
{
    if (!error && bytesReceived > 0) {
        std::cout << "Received: " << m_recvBuf.data() << std::endl;
        std::string command = std::string(m_recvBuf.data());

        if (command.find("SHOOT") == 0) {
            addMessage("CREATED\n");
        } else if (command.find("LOGIN") == 0) {
            createPlayer(registry);
        } else if (command.find("UPDATE") == 0) {
            sendAllEntites(registry);
        } else if (command.find("ENNEMY") == 0) {
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
}

void FunctionPointer::executeCommand(const std::string& command)
{
    if (this->m_commands.count(command) == 0) {
        throw std::runtime_error("Command not found");
    }
    this->m_commands[command]();
}
