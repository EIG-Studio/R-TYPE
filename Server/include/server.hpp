/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** server
*/

#pragma once

#include <bitset>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>

class Server
{
public:
    Server() : m_socket(m_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 7171))
    {
    }

    void startListening();
    void startSending();
    void sendMessage(const std::string& message);

private:
    boost::asio::io_service m_ioService;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_remoteEndpoint;
    boost::array<char, 128> m_recvBuf{};
    std::vector<std::string> m_messages;
    std::mutex m_mutex;

    void handleReceivedData(const boost::system::error_code& error, std::size_t bytesReceived);
    void handlePositionUpdate();
};
