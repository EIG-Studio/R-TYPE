/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** commandsToServer
*/

#include "commandsToServer.hpp"

#include "Systems.hpp"

#include <bitset>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/query.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>

#include <cstdlib>

void log(const std::string& message)
{
    std::cout << "[LOG] " << message << std::endl;
}

std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

int randNb(int x, int y)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(x, y);
    return distrib(gen);
}

void handleReceive(
    Registry& registry,
    const boost::system::error_code& error,
    size_t len,
    unsigned char buffer[sizeof(transferData)],
    std::string& mNewPos)
{
    if (!error && len == 0) {
        std::cout << "No data received, non-blocking return." << std::endl;
        return;
    }

    if (!error && len > 0) {
        transferData receivedData{.command = EMPTY};
        std::memcpy(&receivedData, buffer, sizeof(receivedData));
        //std::string asciiString(binaryToText(recvBuf.data()));
        //std::cout << asciiString;

        if (receivedData.command == NEW_POS) {
            int id = receivedData.args[0];
            int xPos = receivedData.args[1];
            int yPos = receivedData.args[2];

            std::cout << "id= " << id << "| xPos= " << xPos << "| yPos= " << yPos << '\n';
            try {
                Entity entity = registry.getEntity(id);
                if (registry.hasComponent(entity, Position{})) {
                    std::cout << "entity has position" << std::endl;
                    Position& entityPos = registry.getComponent(entity, Position{});
                    entityPos.setPosition(std::make_pair(xPos, yPos));
                    registry.setEntity(entity, id);
                }
            } catch (const std::exception& e) {
                std::cerr << "Exception in handleReceive: " << e.what() << std::endl;
            }
        } else if (receivedData.command == NEW_PLAYER) {
            std::vector<Entity> list = registry.getListEntities();

            int id = receivedData.args[0];
            int xPos = receivedData.args[1];
            int yPos = receivedData.args[2];
            int xSize = receivedData.args[3];
            int ySize = receivedData.args[4];

            log("id= " + std::to_string(id) + "| xPos= " + std::to_string(xPos) + "| yPos= " + std::to_string(yPos));

            if (registry.hasEntity(id))
                return;
            Entity player = registry.createEntityWithID(id);
            player = registry.addComponent(player, Position(std::make_pair(xPos, yPos)));
            player = registry.addComponent(player, Renderer("../Client/assets/Cars/189.png"));
            player = registry.addComponent(player, Type(std::any_cast<EntityType>(Player)));
            player = registry.addComponent(player, Size(std::make_pair(xSize, ySize)));
            registry.setEntity(player, id);
            list = registry.getListEntities();
        } else if (receivedData.command == NEW_ENNEMY) {

            int id = receivedData.args[0];
            int xPos = receivedData.args[1];
            int yPos = receivedData.args[2];
            int xSize = receivedData.args[3];
            int ySize = receivedData.args[4];

            Entity ennemy = registry.createEntityWithID(id);
            ennemy = registry.addComponent(ennemy, Position(std::make_pair(xPos, yPos)));
            ennemy = registry.addComponent(ennemy, Renderer("../Client/assets/Cars/cars/190.png"));
            ennemy = registry.addComponent(ennemy, Type(std::any_cast<EntityType>(Enemy)));
            ennemy = registry.addComponent(ennemy, Size(std::make_pair(xSize, ySize)));

            Position ennemyPos = registry.getComponent(ennemy, Position{});
            std::pair<int, int> pairPos = ennemyPos.getPosition();
            Renderer ennemyRenderer = registry.getComponent(ennemy, Renderer{});
            sf::Sprite ennemySprite = ennemyRenderer.getRenderer();
            Size ennemySize = registry.getComponent(ennemy, Size{});
            std::pair<float, float> pairSize = ennemySize.getSize();

            sf::Vector2f spritePos = ennemySprite.getPosition();
            std::cout << "Ennemy created pos: " << pairPos.first << " " << pairPos.second << '\n';
        } else if (receivedData.command == PLAYER_PROJECTILE) {
            std::cout << "player projectile created" << std::endl;

            int id = receivedData.args[0];
            int xPos = receivedData.args[1];
            int yPos = receivedData.args[2];
            int xSize = receivedData.args[3];
            int ySize = receivedData.args[4];

            std::cout << "get id: " << id << "\n";

            Entity playerProjectile = registry.createEntityWithID(id);
            playerProjectile = registry.addComponent(playerProjectile, Position(std::make_pair(xPos, yPos)));
            playerProjectile = registry.addComponent(playerProjectile, Renderer("../Client/assets/Cars/movement parts/thruster/flame.png"));
            playerProjectile = registry.addComponent(playerProjectile, Type(std::any_cast<EntityType>(Player_Projectile)));
            playerProjectile = registry.addComponent(playerProjectile, Size(std::make_pair(xSize, ySize)));

            Position playerProjectilePos = registry.getComponent(playerProjectile, Position{});
            std::pair<int, int> pairPos = playerProjectilePos.getPosition();
            Renderer playerProjectileRenderer = registry.getComponent(playerProjectile, Renderer{});
            sf::Sprite playerProjectileSprite = playerProjectileRenderer.getRenderer();
            Size playerProjectileSize = registry.getComponent(playerProjectile, Size{});
            std::pair<int, int> pairSize = playerProjectileSize.getSize();

            sf::Vector2f spritePos = playerProjectileSprite.getPosition();
            std::cout << "player projectile created created pos: " << pairPos.first << " " << pairPos.second << '\n';
        } else if (receivedData.command == DELETE_PROJECTILE) {

            int id = receivedData.args[0];

            registry.deleteById(id);
        } else if (receivedData.command == DELETE_ENNEMY) {

            int id = receivedData.args[0];

            registry.deleteById(id);
        }
    } else if (error) {
        std::cerr << "Error in handleReceive: " << error.message() << std::endl;
    }
}

void sendToServer(boost::asio::ip::udp::socket& socket, const std::string& msg)
{
    std::cout << "Sending: " << msg << std::endl;
    transferData data;
    std::istringstream iss(msg);
    std::string word;
    iss >> word;
    data.command = getCommand(word);
    int i = 0;
    while (iss >> word) {
        try {
            data.args[i] = std::stoi(word);
        } catch (std::exception) {
            data.args[i] = getType(word);
        }
        i++;
    }
    //unsigned char buffer[sizeof(transferData)];
    unsigned char buffer[sizeof(transferData)];
    std::memcpy(buffer, &data, sizeof(transferData));
    boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);
    socket.async_send_to(boost::asio::buffer(buffer), receiverEndpoint, [](const boost::system::error_code& ec, std::size_t bytes_transferred) {
        //std::cout << "Async send callback called." << std::endl;
        if (ec) {
            std::cerr << "Send error: " << ec.message() << std::endl;
        } else {
            std::cout << "Sent " << bytes_transferred << " bytes to server." << std::endl;
        }
    });

    //std::cout << "sendToServer call completed." << std::endl;
}

void CommandsToServer::asyncReceiveSecondSocket(Registry& registry)
{
    socket.async_receive(boost::asio::buffer(m_buffer), [this, &registry](auto&& pH1, auto&& pH2) {
        this->mutex.lock();
        handleReceive(std::ref(registry), std::forward<decltype(pH1)>(pH1), std::forward<decltype(pH2)>(pH2), m_buffer, m_newPos);
        this->mutex.unlock();
        memset(m_buffer, 0, sizeof(transferData));
        asyncReceiveSecondSocket(std::ref(registry));
    });
}

// void CommandsToServer::asyncReceive(Registry& registry)
// {
//     socket.async_receive(boost::asio::buffer(m_buffer), [this, &registry](auto&& pH1, auto&& pH2) {
//         return handleReceive(registry, std::forward<decltype(pH1)>(pH1), std::forward<decltype(pH2)>(pH2), m_buffer, m_newPos);
//     });
// }

std::future<void> CommandsToServer::sendToServerAsync(std::string msg)
{
    //std::cout << "sendToServerAsync called with message: " << msg << std::endl;
    std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

    ioService.post([this, msg, promise]() {
        //std::cout << "Inside ioService post lambda for message: " << msg << std::endl;
        try {
            sendToServer(socket, msg);
            promise->set_value();
            //std::cout << "Message sent to server successfully." << std::endl;
        } catch (const std::exception& e) {
            //std::cerr << "Exception in sendToServerAsync: " << e.what() << std::endl;
            promise->set_exception(std::current_exception());
        }
    });

    //std::cout << "sendToServerAsync post operation completed." << std::endl;
    return promise->get_future();
}

std::string CommandsToServer::getNewPos() const
{
    return m_newPos;
}
