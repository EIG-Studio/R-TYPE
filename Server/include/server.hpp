
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
    boost::asio::io_service      m_ioService;
    boost::asio::ip::udp::socket m_socket;

    void handleReceivedData(const boost::array<char, 128>&        recvBuf,
                            const boost::asio::ip::udp::endpoint& remoteEndpoint,
                            const boost::system::error_code&      error);

    void handlePositionUpdate(const boost::array<char, 128>& recvBuf, const boost::asio::ip::udp::endpoint& remoteEndpoint);
};
