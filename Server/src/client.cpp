/*
** EPITECH PROJECT, 2024
** 2
** File description:
** client
*/

#include "client.hpp"

bool Client::operator==(const boost::asio::ip::udp::endpoint& endpoint) const
{
    return m_remoteEndpoint == endpoint;
}

boost::asio::ip::udp::endpoint Client::getEndpoint() const
{
    return m_remoteEndpoint;
}

void Client::setId(std::size_t id)
{
    m_id = id;
}

std::size_t Client::getId() const
{
    return m_id;
}

void Client::setAlive(bool alive)
{
    m_alive = alive;
}

bool Client::isAlive() const
{
    return m_alive;
}
