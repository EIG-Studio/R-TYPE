/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "server.hpp"

void Server::startListening()
{
    auto receiveCallback = [this](const boost::system::error_code& error, std::size_t bytesReceived) {
        handleReceivedData(error, bytesReceived);
        m_recvBuf.fill(0);
        startListening();
    };
    m_socket.async_receive_from(boost::asio::buffer(m_recvBuf), m_remoteEndpoint, receiveCallback);
    m_ioService.run();
}

void Server::sendMessage(const std::string& message)
{
    std::string binaryMessage;

    for (char c : message) {
        binaryMessage += std::bitset<8>(c).to_string();
    }

    m_socket.async_send_to(boost::asio::buffer(binaryMessage), m_remoteEndpoint, [this](const boost::system::error_code&, std::size_t) {
        std::cout << "message sent to: " << m_remoteEndpoint << std::endl;
    });
}
