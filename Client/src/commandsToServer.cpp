/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** commandsToServer
*/

#include "commandsToServer.hpp"

#include "Systems.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/query.hpp>
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
    unsigned char buffer[sizeof(TransferData)],
    std::string& /*mNewPos*/)
{
    if (!error && len == 0) {
        std::cout << "No data received, non-blocking return." << std::endl;
        return;
    }

    if (!error && len > 0) {
        TransferData receivedData{.command = EMPTY};
        std::memcpy(&receivedData, buffer, sizeof(receivedData));

        if (receivedData.command == NEW_POS) {
            int id = receivedData.args[0];
            int xPos = receivedData.args[1];
            int yPos = receivedData.args[2];

            try {
                Entity entity = registry.getEntity(id);
                if (registry.hasComponent(entity, Position{})) {
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

            std::cout << "Ennemy created pos: " << pairPos.first << " " << pairPos.second << '\n';
        } else if (receivedData.command == PLAYER_PROJECTILE) {
            std::cout << "player projectile created" << std::endl;
            int id = receivedData.args[0];
            int xPos = receivedData.args[1];
            int yPos = receivedData.args[2];
            int xSize = receivedData.args[3];
            int ySize = receivedData.args[4];

            Entity playerProjectile = registry.createEntityWithID(id);
            playerProjectile = registry.addComponent(playerProjectile, Position(std::make_pair(xPos, yPos)));
            playerProjectile = registry.addComponent(playerProjectile, Renderer("../Client/assets/Cars/movement parts/thruster/flame.png"));
            playerProjectile = registry.addComponent(playerProjectile, Type(std::any_cast<EntityType>(Player_Projectile)));
            playerProjectile = registry.addComponent(playerProjectile, Size(std::make_pair(xSize, ySize)));

            Position playerProjectilePos = registry.getComponent(playerProjectile, Position{});
            std::pair<int, int> pairPos = playerProjectilePos.getPosition();
            std::cout << "player projectile created created pos: " << pairPos.first << " " << pairPos.second << '\n';
        } else if (receivedData.command == DELETE) {
            registry.deleteById(receivedData.args[0]);
        }
    } else if (error) {
        std::cerr << "Error in handleReceive: " << error.message() << std::endl;
    }
}

void sendToServer(boost::asio::ip::udp::socket& socket, const std::string& msg)
{
    std::cout << "Sending: " << msg << std::endl;
    TransferData data{};
    std::istringstream iss(msg);
    std::string word;
    iss >> word;
    data.command = getCommand(word);
    int i = 0;
    while (iss >> word) {
        try {
            data.args[i] = std::stoi(word);
        } catch (const std::exception& e) {
            data.args[i] = getType(word);
        }
        i++;
    }
    unsigned char buffer[sizeof(TransferData)];
    std::memcpy(buffer, &data, sizeof(TransferData));
    boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);
    socket.async_send_to(boost::asio::buffer(buffer), receiverEndpoint, [](const boost::system::error_code& ec, std::size_t bytes_transferred) {
        if (ec) {
            std::cerr << "Send error: " << ec.message() << std::endl;
        } else {
            // std::cout << "Sent " << bytes_transferred << " bytes to server." << std::endl;
        }
    });
}

void CommandsToServer::asyncReceiveSecondSocket(Registry& registry)
{
    m_socket.async_receive(boost::asio::buffer(m_buffer), [this, &registry](auto&& pH1, auto&& pH2) {
        this->mutex.lock();
        handleReceive(std::ref(registry), std::forward<decltype(pH1)>(pH1), std::forward<decltype(pH2)>(pH2), m_buffer, m_newPos);
        this->mutex.unlock();
        memset(m_buffer, 0, sizeof(TransferData));
        asyncReceiveSecondSocket(std::ref(registry));
    });
}

std::future<void> CommandsToServer::sendToServerAsync(std::string msg)
{
    std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

    m_ioService.post([this, msg, promise]() {
        try {
            sendToServer(m_socket, msg);
            promise->set_value();
        } catch (const std::exception& e) {
            promise->set_exception(std::current_exception());
        }
    });

    return promise->get_future();
}

std::string CommandsToServer::getNewPos() const
{
    return m_newPos;
}
