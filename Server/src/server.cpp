/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "server.hpp"

#include "entities.hpp"

void Server::startListening(Registry& registry)
{
    auto receiveCallback = [this, &registry](const boost::system::error_code& error, std::size_t bytesReceived) {
        m_registeryMutex.lock();
        handleReceivedData(error, bytesReceived, registry, m_remoteEndpoint);
        m_registeryMutex.unlock();
        startListening(registry);
    };
    m_socket.async_receive_from(boost::asio::buffer(m_buffer), m_remoteEndpoint, receiveCallback);
    m_ioService.run();
}

void Server::startSending()
{
    transferData data;
    while (true) {
        data = {.command = EMPTY};
        this->m_mutex.lock();
        if (!m_messages.empty()) {
            data = m_messages.back();
        }
        this->m_mutex.unlock();
        if (!(data.command == EMPTY)) {
            sendMessage(data);
            this->m_mutex.lock();
            m_messages.pop_back();
            this->m_mutex.unlock();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(010));
        }
    }
}

void Server::sendMessage(transferData data)
{
    unsigned char buffer[sizeof(transferData)];
    std::memcpy(buffer, &data, sizeof(transferData));

    for (const auto& client : m_clients) {
        m_socket.async_send_to(boost::asio::buffer(buffer), client.getEndpoint(), [](const boost::system::error_code&, std::size_t) {
        });
    }
}

void Server::addClient(const boost::asio::ip::udp::endpoint& clientEndpoint, std::size_t id)
{
    if (find(m_clients.begin(), m_clients.end(), clientEndpoint) == m_clients.end()) {
        Client client(clientEndpoint, id);
        m_clients.push_back(client);
        std::cout << "Client added: " << clientEndpoint.address().to_string() << ":" << clientEndpoint.port() << std::endl;
    }
}
