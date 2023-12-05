/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "server.hpp"

void Server::startListening()
{
    while (true) {
        boost::array<char, 128>        recvBuf{};
        boost::asio::ip::udp::endpoint remoteEndpoint;
        boost::system::error_code      error;

        m_socket.receive_from(boost::asio::buffer(recvBuf), remoteEndpoint, 0, error);

        std::cout << "Received: " << recvBuf.data() << std::endl;

        handleReceivedData(recvBuf, remoteEndpoint, error);
    }
}

void Server::handleReceivedData(const boost::array<char, 128>&        recvBuf,
                                const boost::asio::ip::udp::endpoint& remoteEndpoint,
                                const boost::system::error_code&      error)
{
    if (strcmp(recvBuf.data(), "TEST") == 0) {
        if (error && error != boost::asio::error::message_size)
            throw boost::system::system_error(error);

        std::string message = "TEST_OK\n";

        boost::system::error_code ignoredError;
        m_socket.send_to(boost::asio::buffer(message), remoteEndpoint, 0, ignoredError);
    }
    else if (std::string(recvBuf.data(), 3) == "POS") {
        if (error && error != boost::asio::error::message_size)
            throw boost::system::system_error(error);

        handlePositionUpdate(recvBuf, remoteEndpoint);
    }
}

void Server::handlePositionUpdate(const boost::array<char, 128>& recvBuf, const boost::asio::ip::udp::endpoint& remoteEndpoint)
{
    std::string              posString = recvBuf.data();
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
    }
    else if (std::stof(tokens[4]) == 2) {
        newPosX = newPosX + moveSpeed;
    }
    else if (std::stof(tokens[4]) == 3) {
        newPosY = newPosY + moveSpeed;
    }
    else if (std::stof(tokens[4]) == 4) {
        newPosX = newPosX - moveSpeed;
    }

    newPos << "NEW_POS " << newPosX << " " << newPosY << "\n";
    std::string message = newPos.str();

    boost::system::error_code ignoredError;
    m_socket.send_to(boost::asio::buffer(message), remoteEndpoint, 0, ignoredError);
}

int main()
{
    try {
        Server server;
        server.startListening();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
