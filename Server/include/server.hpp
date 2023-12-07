#include <bitset>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

#pragma once

class Server
{
public:
    Server() : m_socket(m_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 7171))
    {
    }

    void startListening();

private:
    boost::asio::io_service m_ioService;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_remoteEndpoint; // Add this line
    boost::array<char, 128> m_recvBuf{};

    void handleReceivedData(const boost::system::error_code& error, std::size_t bytesReceived);

    void handlePositionUpdate();
};
