/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** commandsToServer
*/

#include "commandsToServer.hpp"

#include <bitset>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/query.hpp>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>

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

std::string binaryToText(const std::string& binaryString)
{
    int decimalValue = 0;
    char character = 0;
    std::string text;

    for (size_t i = 0; i < binaryString.length(); i += 8) {
        decimalValue = std::bitset<8>(binaryString.substr(i, 8)).to_ulong();
        character = static_cast<char>(decimalValue);
        text += character;
    }
    return text;
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
    boost::array<char, 2048>& recvBuf,
    std::string& mNewPos)
{
    if (!error && len == 0) {
        std::cout << "No data received, non-blocking return." << std::endl;
        return;
    }

    if (!error && len > 0) {
        std::string asciiString(binaryToText(recvBuf.data()));
        std::cout << asciiString;

        if (asciiString.find("NEW_POS") == 0) {
            mNewPos = asciiString;
        } else if (asciiString.find("UPDATE") == 0) {
            // updateEntity();
        } else if (asciiString.find("NEW") == 0) {
            std::vector<std::string> parts = split(asciiString, ' ');

            int id = std::stoi(parts[1]);
            float xPos = std::stof(parts[2]);
            float yPos = std::stof(parts[3]);
            std::string playerType = parts[4];

            std::cout << "get id:" << id << "\n";

            Entity player = registry.createEntityWithID(id);
            //Entity player;
            //player = registry.createEntity();
            //player = registry.addComponent(player, ID(id));
            player = registry.addComponent(player, Position(std::make_pair(xPos, yPos)));
            player = registry.addComponent(player, Renderer("../Client/assets/Cars/189.png"));
            player = registry.addComponent(player, Type(std::any_cast<EntityType>(Player)));

            if (registry.hasComponent(player, ID{})) {
                std::cout << "TEST\n";
            }

            std::cout << "player id: " << registry.getComponent(player, ID{}) << "\nPlayer pos: " << xPos << " " << yPos
                      << '\n';
        } else if (asciiString.find("ENNEMY") == 0) {
            std::cout << "Ennemy created" << std::endl;
            Entity ennemy;
            ennemy = registry.createEntity();
            ennemy = registry.addComponent(ennemy, ID(1));
            ennemy = registry.addComponent(ennemy, Position(std::make_pair(randNb(200, 700), randNb(0, 500))));
            ennemy = registry.addComponent(ennemy, Renderer("../Client/assets/Cars/cars/190.png"));
            ennemy = registry.addComponent(ennemy, Type(std::any_cast<EntityType>(Enemy)));

            Position ennemy_pos = registry.getComponent(ennemy, Position{});
            std::pair<float, float> pair_pos = ennemy_pos.getPosition();
            Renderer ennemy_renderer = registry.getComponent(ennemy, Renderer{});
            sf::Sprite ennemy_sprite = ennemy_renderer.getRenderer();

            sf::Vector2f sprite_pos = ennemy_sprite.getPosition();
            std::cout << "Ennemy created pos: " << pair_pos.first << " " << pair_pos.second << '\n';
        } else if (asciiString.find("WIN") == 0) {
            // win();
        } else if (asciiString.find("LOOSE") == 0) {
            // loose();
        } else if (
            asciiString.find("RIGHT") == 0 || asciiString.find("LEFT") == 0 || asciiString.find("UP") == 0 ||
            asciiString.find("DOWN") == 0) {
            std::cout << "TEST\n";
        }
    } else if (error) {
        std::cerr << "Error in handleReceive: " << error.message() << std::endl;
    }
}

void sendToServer(boost::asio::ip::udp::socket& socket, const std::string& msg)
{
    boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);
    socket.send_to(boost::asio::buffer(msg), receiverEndpoint);
}

void CommandsToServer::asyncReceive(Registry& registry)
{
    socket.async_receive(boost::asio::buffer(recvBuf), [this, &registry](auto&& pH1, auto&& pH2) {
        return handleReceive(registry, std::forward<decltype(pH1)>(pH1), std::forward<decltype(pH2)>(pH2), recvBuf, m_newPos);
    });
}

std::future<void> CommandsToServer::sendToServerAsync(std::string msg, Registry& registry)
{
    return std::async(std::launch::async, [this, msg = std::move(msg), &registry]() {
        try {
            boost::array<char, 2048> recvBuf{};

            sendToServer(socket, msg);
            asyncReceive(registry);
            ioService.run();
            ioService.reset();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    });
}

std::string CommandsToServer::getNewPos() const
{
    return m_newPos;
}
