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
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>

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
        std::cout << asciiString << std::endl;

        if (asciiString.find("NEW_POS") == 0) {
            std::vector<std::string> parts = split(asciiString, ' ');

            int id = std::stoi(parts[1]);
            float xPos = std::stof(parts[2]);
            float yPos = std::stof(parts[3]);

            Entity entity = registry.getEntity(id);
            Position& entityPos = registry.getComponent(entity, Position{});
            entityPos.setPosition(std::make_pair(xPos, yPos));
            registry.setEntity(entity, id);
        } else if (asciiString.find("UPDATE") == 0) {
            std::vector<std::string> lines = split(asciiString, '\n');
            for (const std::string& line : lines) {
                if (line == "UPDATE")
                    continue;

                std::vector<std::string> parts = split(line, ' ');

                int id = std::stoi(parts[0]);
                float xPos = std::stof(parts[1]);
                float yPos = std::stof(parts[2]);
                int type = std::stoi(parts[3]);
                if (registry.hasEntity(id)) {
                    Entity entity = registry.getEntity(id);
                    Position& entityPos = registry.getComponent(entity, Position{});
                    entityPos.setPosition(std::make_pair(xPos, yPos));
                    registry.setEntity(entity, id);
                } else {
                    Entity newEntity = registry.createEntityWithID(id);
                    newEntity = registry.addComponent(newEntity, Position(std::make_pair(xPos, yPos)));
                    if (type == Player) {
                        newEntity = registry.addComponent(newEntity, Renderer("../Client/assets/Cars/189.png"));
                        newEntity = registry.addComponent(newEntity, Type(std::any_cast<EntityType>(Player)));
                    } else if (type == Enemy) {
                        newEntity = registry.addComponent(newEntity, Renderer("../Client/assets/Cars/cars/190.png"));
                        newEntity = registry.addComponent(newEntity, Type(std::any_cast<EntityType>(Enemy)));
                    }
                }
            }
        } else if (asciiString.find("NEW") == 0) {
            std::vector<Entity> list = registry.getListEntities();
            std::cout << "SIZE " << list.size() << "\n";
            std::vector<std::string> parts = split(asciiString, ' ');

            int id = std::stoi(parts[1]);
            float xPos = std::stof(parts[2]);
            float yPos = std::stof(parts[3]);
            std::string playerType = parts[4];

            log("get id:" + std::to_string(id));

            Entity player = registry.createEntityWithID(id);
            player = registry.addComponent(player, Position(std::make_pair(xPos, yPos)));
            player = registry.addComponent(player, Renderer("../Client/assets/Cars/189.png"));
            player = registry.addComponent(player, Type(std::any_cast<EntityType>(Player)));
            registry.setEntity(player, id);
            list = registry.getListEntities();
        } else if (asciiString.find("ENNEMY") == 0) {
            std::vector<std::string> parts = split(asciiString, ' ');

            int id = std::stoi(parts[1]);
            float xPos = std::stof(parts[2]);
            float yPos = std::stof(parts[3]);
            std::string playerType = parts[4];


            Entity ennemy = registry.createEntityWithID(id);
            ennemy = registry.addComponent(ennemy, Position(std::make_pair(randNb(200, 700), randNb(0, 500))));
            ennemy = registry.addComponent(ennemy, Renderer("../Client/assets/Cars/cars/190.png"));
            ennemy = registry.addComponent(ennemy, Type(std::any_cast<EntityType>(Enemy)));

            Position ennemyPos = registry.getComponent(ennemy, Position{});
            std::pair<float, float> pairPos = ennemyPos.getPosition();
            Renderer ennemyRenderer = registry.getComponent(ennemy, Renderer{});
            sf::Sprite ennemySprite = ennemyRenderer.getRenderer();

            sf::Vector2f spritePos = ennemySprite.getPosition();
            std::cout << "Ennemy created pos: " << pairPos.first << " " << pairPos.second << '\n';
        } else if (asciiString.find("PLAYER_PROJECTILE") == 0) {
            std::cout << "player projectile created" << std::endl;
            std::vector<std::string> parts = split(asciiString, ' ');

            int id = std::stoi(parts[1]);
            float xPos = std::stof(parts[2]);
            float yPos = std::stof(parts[3]);
            std::string playerType = parts[4];

            std::cout << "get id: " << id << "\n";

            Entity playerProjectile = registry.createEntityWithID(id);
            playerProjectile = registry.addComponent(playerProjectile, Position(std::make_pair(xPos, yPos)));
            playerProjectile = registry.addComponent(playerProjectile, Renderer("../Client/assets/Cars/movement parts/thruster/flame.png"));
            playerProjectile = registry.addComponent(playerProjectile, Type(std::any_cast<EntityType>(Player_Projectile)));

            Position playerProjectilePos = registry.getComponent(playerProjectile, Position{});
            std::pair<float, float> pairPos = playerProjectilePos.getPosition();
            Renderer playerProjectileRenderer = registry.getComponent(playerProjectile, Renderer{});
            sf::Sprite playerProjectileSprite = playerProjectileRenderer.getRenderer();

            sf::Vector2f spritePos = playerProjectileSprite.getPosition();
            std::cout << "player projectile created created pos: " << pairPos.first << " " << pairPos.second << '\n';
        } else if (asciiString.find("DESTROY PROJECTILE") == 0) {
            std::vector<std::string> parts = split(asciiString, ' ');

            int id = std::stoi(parts[1]);


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
    recvBuf.fill(0);
}

void sendToServer(boost::asio::ip::udp::socket& socket, const std::string& msg)
{
    std::cout << "Sending: " << msg << std::endl;
    boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);
    socket.async_send_to(boost::asio::buffer(msg), receiverEndpoint, [](const boost::system::error_code& ec, std::size_t bytes_transferred) {
        //std::cout << "Async send callback called." << std::endl;
        if (ec) {
            std::cerr << "Send error: " << ec.message() << std::endl;
        } else {
            std::cout << "Sent " << bytes_transferred << " bytes to server." << std::endl;
        }
    });

    //std::cout << "sendToServer call completed." << std::endl;
}


void CommandsToServer::handleReceiveSecondSocket(
    Registry& registry,
    const boost::system::error_code& error,
    size_t len,
    boost::array<char, 2048>& recvBuf,
    std::string& mNewPos)
{
    if (error) {
        std::cerr << "Error in handleReceiveSecondSocket: " << error.message() << std::endl;
        return;
    }

    if (len == 0) {
        std::cout << "No data received, non-blocking return." << std::endl;
        return;
    }

    try {
        std::string asciiString(binaryToText(recvBuf.data()));
        log("handleReceived message:\n" + asciiString);
        //std::cout << "handleReceived message: " << asciiString << std::endl;


        processMessage(asciiString, registry);
    } catch (const std::exception& e) {
        std::cerr << "Exception in processing received data: " << e.what() << std::endl;
    }
}

void CommandsToServer::processMessage(const std::string& asciiString, Registry& registry)
{
    if (asciiString.find("NEW_POS") == 0) {
        std::vector<std::string> parts = split(asciiString, ' ');

        int id = std::stoi(parts[1]);
        float xPos = std::stof(parts[2]);
        float yPos = std::stof(parts[3]);

        Entity entity = registry.getEntity(id);
        Position& entityPos = registry.getComponent(entity, Position{});
        entityPos.setPosition(std::make_pair(xPos, yPos));
        registry.setEntity(entity, id);
    } else if (asciiString.find("UPDATE") == 0) {
        std::vector<std::string> lines = split(asciiString, '\n');

        for (const std::string& line : lines) {
            if (line == "UPDATE")
                continue;

            std::vector<std::string> parts = split(line, ' ');

            int id = std::stoi(parts[0]);
            float xPos = std::stof(parts[1]);
            float yPos = std::stof(parts[2]);
            int type = std::stoi(parts[3]);

            if (registry.hasEntity(id)) {
                Entity entity = registry.getEntity(id);
                Position& entityPos = registry.getComponent(entity, Position{});
                entityPos.setPosition(std::make_pair(xPos, yPos));
                registry.setEntity(entity, id);
            } else {
                Entity newEntity = registry.createEntityWithID(id);
                newEntity = registry.addComponent(newEntity, Position(std::make_pair(xPos, yPos)));
                if (type == Player) {
                    newEntity = registry.addComponent(newEntity, Renderer("../Client/assets/Cars/189.png"));
                    newEntity = registry.addComponent(newEntity, Type(std::any_cast<EntityType>(Other_Player)));
                } else if (type == Enemy) {
                    newEntity = registry.addComponent(newEntity, Renderer("../Client/assets/Cars/cars/190.png"));
                    newEntity = registry.addComponent(newEntity, Type(std::any_cast<EntityType>(Enemy)));
                }
            }
        }
    } else if (asciiString.find("NEW") == 0) {
        std::vector<std::string> parts = split(asciiString, ' ');

        int id = std::stoi(parts[1]);
        float xPos = std::stof(parts[2]);
        float yPos = std::stof(parts[3]);
        std::string playerType = parts[4];

        std::cout << "get id:" << id << "\n";

        Entity player = registry.createEntityWithID(id);
        player = registry.addComponent(player, Position(std::make_pair(xPos, yPos)));
        player = registry.addComponent(player, Renderer("../Client/assets/Cars/189.png"));
        player = registry.addComponent(player, Type(std::any_cast<EntityType>(Player)));

    } else if (asciiString.find("ENNEMY") == 0) {
        std::vector<std::string> parts = split(asciiString, ' ');

        int id = std::stoi(parts[1]);
        float xPos = std::stof(parts[2]);
        float yPos = std::stof(parts[3]);
        std::string playerType = parts[4];


        Entity ennemy = registry.createEntityWithID(id);
        ennemy = registry.addComponent(ennemy, Position(std::make_pair(randNb(200, 700), randNb(0, 500))));
        ennemy = registry.addComponent(ennemy, Renderer("../Client/assets/Cars/cars/190.png"));
        ennemy = registry.addComponent(ennemy, Type(std::any_cast<EntityType>(Enemy)));

        Position ennemyPos = registry.getComponent(ennemy, Position{});
        std::pair<float, float> pairPos = ennemyPos.getPosition();
        Renderer ennemyRenderer = registry.getComponent(ennemy, Renderer{});
        sf::Sprite ennemySprite = ennemyRenderer.getRenderer();

        sf::Vector2f spritePos = ennemySprite.getPosition();
    } else if (asciiString.find("WIN") == 0) {
        // win();
    } else if (asciiString.find("LOOSE") == 0) {
        // loose();
    } else if (
        asciiString.find("RIGHT") == 0 || asciiString.find("LEFT") == 0 || asciiString.find("UP") == 0 ||
        asciiString.find("DOWN") == 0) {
        std::cout << "TEST\n";
    }
}

void CommandsToServer::asyncReceiveSecondSocket(Registry& registry)
{
    socket.async_receive(boost::asio::buffer(recvBuf), [this, &registry](auto&& pH1, auto&& pH2) {
        this->mutex.lock();
        handleReceive(std::ref(registry), std::forward<decltype(pH1)>(pH1), std::forward<decltype(pH2)>(pH2), recvBuf, m_newPos);
        this->mutex.unlock();
        recvBuf.fill(0);
        asyncReceiveSecondSocket(std::ref(registry));
    });
}

void CommandsToServer::asyncReceive(Registry& registry)
{
    socket.async_receive(boost::asio::buffer(recvBuf), [this, &registry](auto&& pH1, auto&& pH2) {
        return handleReceive(registry, std::forward<decltype(pH1)>(pH1), std::forward<decltype(pH2)>(pH2), recvBuf, m_newPos);
    });
}

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
