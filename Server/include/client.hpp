/*
** EPITECH PROJECT, 2024
** 2
** File description:
** client
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>

class Client
{
public:
    Client() = default;
    Client(boost::asio::ip::udp::endpoint remoteEndpoint) : m_remoteEndpoint{remoteEndpoint} {};
    ~Client() = default;
    bool operator==(const boost::asio::ip::udp::endpoint& endpoint) const
    {
        return m_remoteEndpoint == endpoint;
    }
    void sendMessage(const std::string message);
    std::string receiveMessage();
    boost::asio::ip::udp::endpoint getEndpoint() const
    {
        return m_remoteEndpoint;
    }

private:
    boost::asio::ip::udp::endpoint m_remoteEndpoint;
};
