/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "server.hpp"

void Server::startListening()
{
    m_socket.async_receive_from(boost::asio::buffer(m_recvBuf),
                                m_remoteEndpoint,
                                [this](const boost::system::error_code& error, std::size_t bytesReceived)
                                {
                                    handleReceivedData(error, bytesReceived, m_remoteEndpoint);
                                    startListening();
                                });

    m_ioService.run();
}

void Server::handleReceivedData(const boost::system::error_code&      error,
                                std::size_t                           bytesReceived,
                                const boost::asio::ip::udp::endpoint& remoteEndpoint)
{
    if (!error && bytesReceived > 0) {
        std::cout << "Received: " << m_recvBuf.data() << std::endl;

        if (strcmp(m_recvBuf.data(), "TEST") == 0) {
            std::string message = "TEST_OK\n";

            // Convert ASCII message to binary
            std::string binaryMessage;
            for (char c : message) {
                binaryMessage += std::bitset<8>(c).to_string();
            }

            m_socket.async_send_to(boost::asio::buffer(binaryMessage),
                                   remoteEndpoint,
                                   [this](const boost::system::error_code&, std::size_t) {
                                       std::cout << "TEST_OK sent\n" << std::endl;
                                   });

        } else if (std::string(m_recvBuf.data(), 3) == "POS") {
            handlePositionUpdate();
        }
    }

    // Continue listening for the next packet
    m_socket.async_receive_from(boost::asio::buffer(m_recvBuf),
                                m_remoteEndpoint,
                                [this](const boost::system::error_code& nextError, std::size_t nextBytesReceived)
                                {
                                    handleReceivedData(nextError, nextBytesReceived, m_remoteEndpoint);
                                    m_recvBuf.fill(0);
                                });
}


void Server::handlePositionUpdate()
{
    std::string              posString = m_recvBuf.data();
    std::istringstream       iss(posString);
    std::vector<std::string> tokens;
    std::ostringstream       newPos;

    std::string token;
    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    float newPosX   = std::stof(tokens[1]);
    float newPosY   = std::stof(tokens[2]);
    float moveSpeed = std::stof(tokens[3]);

    if (std::stof(tokens[4]) == 1) {
        newPosY = newPosY - moveSpeed;
    } else if (std::stof(tokens[4]) == 2) {
        newPosX = newPosX + moveSpeed;
    } else if (std::stof(tokens[4]) == 3) {
        newPosY = newPosY + moveSpeed;
    } else if (std::stof(tokens[4]) == 4) {
        newPosX = newPosX - moveSpeed;
    }

    newPos << "NEW_POS " << newPosX << " " << newPosY << "\n";
    std::string message = newPos.str();

    std::string binaryMessage;
    for (char c : message) {
        binaryMessage += std::bitset<8>(c).to_string();
    }
    m_socket.async_send_to(boost::asio::buffer(binaryMessage),
                           m_remoteEndpoint,
                           [this](const boost::system::error_code&, std::size_t) {
                               std::cout << "NEW_POS sent\n" << std::endl;
                           });
}
