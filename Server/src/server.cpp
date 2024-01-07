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
        m_recvBuf.fill(0);
        startListening(registry);
    };
    m_socket.async_receive_from(boost::asio::buffer(m_recvBuf), m_remoteEndpoint, receiveCallback);
    m_ioService.run();
}

void Server::startSending()
{
    std::string message;

    while (true) {
        message = "";
        this->m_mutex.lock();
        if (!m_messages.empty()) {
            message = m_messages.back().first;
            m_messages.back().second++;
        }
        this->m_mutex.unlock();
        if (!message.empty()) {
            sendMessage(message);
            this->m_mutex.lock();
            m_messages.pop_back();
            this->m_mutex.unlock();
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(010));
        }
    }
}

void Server::sendMessage(const std::string& message)
{
    std::string binaryMessage;

    for (char c : message) {
        binaryMessage += std::bitset<8>(c).to_string();
    }
    for (const auto& client : m_clients) {
        m_socket.async_send_to(boost::asio::buffer(binaryMessage), client.getEndpoint(), [](const boost::system::error_code&, std::size_t) {
        });
    }
}

void Server::addClient(const boost::asio::ip::udp::endpoint& clientEndpoint)
{
    if (find(m_clients.begin(), m_clients.end(), clientEndpoint) == m_clients.end()) {
        Client client(clientEndpoint);
        m_clients.push_back(clientEndpoint);
        std::cout << "Client added: " << clientEndpoint.address().to_string() << ":" << clientEndpoint.port() << std::endl;
    }
}
