/*
** EPITECH PROJECT, 2024
** 3
** File description:
** communication
*/

#include "server.hpp"

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

void Server::addMessage(const std::string& message)
{
    this->m_messageMutex.lock();
    TransferData data{.command = EMPTY, .args = {0, 0, 0, 0}};
    std::istringstream iss(message);
    int i = 0;
    std::cout << "\033[1;32m"
              << "[SERVER]: \033[0m" << message;
    std::string word;
    iss >> word;
    data.command = getCommand(word);
    while (iss >> word) {
        try {
            data.args[i] = std::stoi(word);
        } catch (const std::exception& e) {
            data.args[i] = getType(word);
        }
        i++;
    }
    m_messages.emplace_front(data);
    this->m_messageMutex.unlock();
}

void Server::startSending()
{
    TransferData data{};
    while (true) {
        data = {.command = EMPTY};
        this->m_messageMutex.lock();
        if (!m_messages.empty()) {
            data = m_messages.back();
        }
        this->m_messageMutex.unlock();
        if (!(data.command == EMPTY)) {
            sendMessage(data);
            this->m_messageMutex.lock();
            m_messages.pop_back();
            this->m_messageMutex.unlock();
        }
    }
}

void Server::sendMessage(TransferData data)
{
    unsigned char buffer[sizeof(TransferData)];
    std::memcpy(buffer, &data, sizeof(TransferData));

    for (const auto& client : m_clients) {
        m_socket.async_send_to(boost::asio::buffer(buffer), client.getEndpoint(), [](const boost::system::error_code&, std::size_t) {
        });
    }
}
