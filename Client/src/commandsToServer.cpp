/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** commandsToServer
*/

#include "commandsToServer.hpp"

#include "Systems.hpp"
#include "createEntity.hpp"

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

int setPlayer(int id)
{
    static int playerId = -1;
    if (id != -1)
        playerId = id;
    return playerId;
}

void handleReceive(
    Registry& registry,
    const boost::system::error_code& error,
    size_t len,
    unsigned char buffer[sizeof(TransferData)],
    std::string& /*mNewPos*/,
    Music& music)
{
    if (!error && len == 0) {
        std::cout << "No data received, non-blocking return." << std::endl;
        return;
    }

    if (!error && len > 0) {
        TransferData receivedData{.command = EMPTY};
        std::memcpy(&receivedData, buffer, sizeof(receivedData));

        switch (receivedData.command) {
            case NEW_POS:
                updatePosition(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2]);
                break;
            case NEW_HEALTH:
                updateHealth(registry, receivedData.args[0], receivedData.args[1]);
                break;
            case NEW_PLAYER:
                createPlayer(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2], receivedData.args[3]);
                break;
            case NEW_ENEMY:
                createEnemy(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2]);
                break;
            case NEW_BOSS:
                createBoss(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2], receivedData.args[3]);
                break;
            case PLAYER_PROJECTILE:
                createPlayerProjectile(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2]);
                break;
            case POWER_UP:
                createPowerUp(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2]);
                break;
            case BLUE_PROJECILE:
                createPlayerProjectile2(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2]);
                break;
            case DELETE_ENTITY:
                registry.deleteById(receivedData.args[0]);
                break;
            case GET_POWER_UP:
                registry.deleteById(receivedData.args[0]);
                break;
            case PLAY_BOOM_ENEMIES:
                music.boomEnemies.play();
                break;
            case NEW_HUD:
                createHud(registry, receivedData.args[0], receivedData.args[1]);
                break;
            case SCORE:
                createScore(registry, receivedData.args[0]);
                break;
            case ARROW_PLAYER:
                createArrow(registry, receivedData.args[0]);
                break;
            case LOGIN_OK:
                std::cout << "LOGIN OK " << std::to_string(receivedData.args[0]) << std::endl;
                setPlayer(receivedData.args[0]);
                break;
            default:
                std::cout << "[LOG] NO SCORE" << std::endl;
                break;
        }
    } else if (error) {
        std::cerr << "Error in handleReceive: " << error.message() << std::endl;
    }
}

void sendToServer(boost::asio::ip::udp::socket& socket, const std::string& msg, IpAdress& ipAdress)
{
    std::cout << "\033[1;31m"
              << "[CLIENT]: \033[0m" << msg << std::endl;
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
    if (ipAdress.getUserInput().empty()) {
        ipAdress.setUserInput("127.0.0.1");
    }
    boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string(ipAdress.getUserInput()), 7171);
    socket.async_send_to(boost::asio::buffer(buffer), receiverEndpoint, [](const boost::system::error_code& ec, std::size_t /*bytes_transferred*/) {
        if (ec) {
            std::cerr << "Send error: " << ec.message() << std::endl;
        }
    });
}

void CommandsToServer::asyncReceive(Registry& registry, Music& music)
{
    m_socket.async_receive(boost::asio::buffer(m_buffer), [this, &registry, &music](auto&& pH1, auto&& pH2) {
        this->mutex.lock();
        handleReceive(std::ref(registry), std::forward<decltype(pH1)>(pH1), std::forward<decltype(pH2)>(pH2), m_buffer, m_newPos, music);
        this->mutex.unlock();
        memset(m_buffer, 0, sizeof(TransferData));
        asyncReceive(std::ref(registry), music);
    });
}

std::future<void> CommandsToServer::sendToServerAsync(const std::string& msg, IpAdress& ipAdress)
{
    std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

    m_ioService.post([this, msg, promise, &ipAdress]() {
        try {
            sendToServer(m_socket, msg, ipAdress);
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
