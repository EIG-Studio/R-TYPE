/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** server
*/

#pragma once

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
    void sendMessage(const std::string& message);
    void sendAllEntites(Registry& registry);
    void createEnnemy(Registry& registry);

private:
    boost::asio::io_service m_ioService;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_remoteEndpoint;
    boost::array<char, 128> m_recvBuf{};
    std::deque<std::pair<std::string, int>> m_messages;
    std::mutex m_mutex;
    std::vector<Client> m_clients;

    void handleReceivedData(
        const boost::system::error_code& error,
        std::size_t bytesReceived,
        Registry& registry,
        boost::asio::ip::udp::endpoint remoteEndpoint);
    void handlePositionUpdate();
    void addMessage(const std::string& message);
    void createPlayer(Registry& registry);
    void goUp(Registry& registry, std::string& command);
    void goDown(Registry& registry, std::string& command);
    void goRight(Registry& registry, std::string& command);
    void goLeft(Registry& registry, std::string& command);
    void addClient(const boost::asio::ip::udp::endpoint& clientEndpoint);
};
