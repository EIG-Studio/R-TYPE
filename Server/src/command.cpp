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

void Server::createPlayer()
{
    Registry registry = Registry();
    Entity entity;
    entity = registry.createEntity();
    entity = registry.addComponent(entity, Position(std::make_pair(200, 600)));
    entity = registry.addComponent(entity, Renderer("../Client/assets/Cars/189_neutral.png"));
    entity = registry.addComponent(entity, Type(std::any_cast<EntityType>(Player)));
}

void Server::addMessage(const std::string& message)
{
    this->m_mutex.lock();
    m_messages.emplace_front(std::make_pair(message, 0));
    this->m_mutex.unlock();
}

void Server::handleReceivedData(const boost::system::error_code& error, std::size_t bytesReceived)
{
    if (!error && bytesReceived > 0) {
        std::cout << "Received: " << m_recvBuf.data() << std::endl;
        std::string command = std::string(m_recvBuf.data());
        if (command.find("SHOOT") == 0) {
            addMessage("CREATED\n");
        } else if (command.find("POS") == 0) {
            handlePositionUpdate();
        } else if (command.find("LOGIN") == 0) {
            createPlayer();
        } else if (command.find("EXIT") == 0) {
            // deletePlayer();
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
