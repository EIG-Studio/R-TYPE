/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** commandsToServer
*/

#pragma once

#include "../../GameEngine/include/components.hpp"
#include "../../GameEngine/include/entities.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <future>
#include <iostream>
#include <string>

class CommandsToServer
{
public:
    CommandsToServer(const CommandsToServer&) = delete;
    CommandsToServer& operator=(const CommandsToServer&) = delete;

    CommandsToServer() : socket(ioService), receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171)
    {
        socket.open(boost::asio::ip::udp::v4());
    }

    std::string getNewPos() const;

    std::future<void> sendToServerAsync(std::string msg, Registry& registry);
    void asyncReceive(Registry& registry);

private:
    std::string m_newPos;
    boost::asio::io_service ioService;
    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint receiverEndpoint;
    boost::array<char, 2048> recvBuf;
};
