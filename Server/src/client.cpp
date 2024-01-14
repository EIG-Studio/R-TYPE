/*
** EPITECH PROJECT, 2024
** 2
** File description:
** client
*/

#include "client.hpp"

#include "server.hpp"

#include <iostream>

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

bool Server::isClient(const boost::asio::ip::udp::endpoint& clientEndpoint)
{
    std::any_of(m_clients.begin(), m_clients.end(), [clientEndpoint](const auto& client) {
        return client == clientEndpoint;
    });

    return false;
}

void Server::addClient(Registry& registry, const boost::asio::ip::udp::endpoint& clientEndpoint, std::size_t id)
{
    if (find(m_clients.begin(), m_clients.end(), clientEndpoint) == m_clients.end()) {
        Client client(clientEndpoint, id);
        m_clients.push_back(client);
        sendMessage(TransferData{.command = LOGIN_OK, .args = {static_cast<int>(id), 0, 0, 0}}, client);
        sendMessage(TransferData{.command = LEVEL, .args = {m_currentLevel, 0, 0, 0}}, client);
        std::cout << "Client added: " << clientEndpoint.address().to_string() << ":" << clientEndpoint.port() << std::endl;
    }
}
