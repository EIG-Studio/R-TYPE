#include "commandsToServer.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

int CommandsToServer::sendToServer(std::string msg)
{
    try
    {
        boost::asio::io_service ioService;

        boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);

        boost::asio::ip::udp::socket socket(ioService);
        socket.open(boost::asio::ip::udp::v4());

        socket.send_to(boost::asio::buffer(msg), receiverEndpoint);

        boost::array<char, 128>        recvBuf{};
        boost::asio::ip::udp::endpoint senderEndpoint;
        size_t                         len = socket.receive_from(boost::asio::buffer(recvBuf), senderEndpoint);

        std::cout.write(recvBuf.data(), len); // (6)
        if (boost::array<char, 128>::size() >= 7 && std::string(recvBuf.data(), 7) == "NEW_POS")
        {
            this->m_newPos = recvBuf.data();
        }
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

std::string CommandsToServer::getNewPos()
{
    return this->m_newPos;
}
