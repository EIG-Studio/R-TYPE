#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

#include "commandsToServer.hpp"
using boost::asio::ip::udp;

int CommandsToServer::sendToServer(std::string msg)
{
    try
    {
        boost::asio::io_service ioService;

        udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);

        udp::socket socket(ioService); // (1)
        socket.open(udp::v4());

        std::string message = "Bienvenue sur le client ! Mode non connecté.\n";
        // boost::array<char, 1> sendBuf = {0};                             // (2)
        socket.send_to(boost::asio::buffer(message), receiverEndpoint); // (3)

        boost::array<char, 128> recvBuf{}; // (4)
        udp::endpoint           senderEndpoint;
        size_t                  len = socket.receive_from(boost::asio::buffer(recvBuf), senderEndpoint); // (5)

        std::cout.write(recvBuf.data(), len); // (6)
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
