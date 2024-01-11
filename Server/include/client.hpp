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
    Client(boost::asio::ip::udp::endpoint remoteEndpoint, std::size_t id) :
    m_remoteEndpoint{remoteEndpoint},
    m_id{id} {};
    ~Client() = default;
    bool operator==(const boost::asio::ip::udp::endpoint& endpoint) const;

    boost::asio::ip::udp::endpoint getEndpoint() const;
    void setId(std::size_t id);
    std::size_t getId() const;
    void setAlive(bool alive);
    bool isAlive() const;
    void setTmpAlive(bool alive);
    bool isTmpAlive() const;

private:
    boost::asio::ip::udp::endpoint m_remoteEndpoint;
    std::size_t m_id;
    bool m_alive{true};
};
