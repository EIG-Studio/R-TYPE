/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** server
*/

#pragma once

#include "Systems.hpp"
#include "client.hpp"
#include "entities.hpp"

#include <bitset>
#include <deque>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <utility>
#include <vector>

class Server
{
public:
    Server() : m_socket(m_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 7171))
    {
    }

    void startListening(Registry& registry);
    void startSending();
    void sendMessage(TransferData data);
    void sendAllEntites(Registry& registry);
    void createEnnemy(Registry& registry);
    void createBullet(Registry& registry, int posx, int posy);
    void GameLoop(Registry& registry);

private:
    boost::asio::io_service m_ioService;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_remoteEndpoint;
    boost::array<char, 128> m_recvBuf{};
    std::deque<TransferData> m_messages;
    std::mutex m_mutex;
    std::mutex m_registeryMutex;
    std::vector<Client> m_clients;
    unsigned char m_buffer[sizeof(TransferData)];

    void handleReceivedData(
        const boost::system::error_code& error,
        std::size_t bytesReceived,
        Registry& registry,
        boost::asio::ip::udp::endpoint& remoteEndpoint);
    void handlePositionUpdate();
    void addMessage(const std::string& message);
    std::size_t createPlayer(Registry& registry);
    void playerMove(Registry& registry, COMMAND direction, std::size_t id);
    void goUp(Registry& registry, std::string& command);
    void goDown(Registry& registry, std::string& command);
    void goRight(Registry& registry, std::string& command);
    void goLeft(Registry& registry, std::string& command);
    void ennemyMove(Registry& registry, Entity& entity, std::size_t id);
    void playerProjectileMove(Registry& registry, Entity& entity, std::size_t id);
    void addClient(const boost::asio::ip::udp::endpoint& clientEndpoint, std::size_t id);
    void refreshClientRegistry(Registry& registry, int id);
};
