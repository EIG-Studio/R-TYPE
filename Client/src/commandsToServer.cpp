#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

#include "commandsToServer.hpp"
using boost::asio::ip::udp;

int CommandsToServer::sendToServer(std::string msg)
{
    try
    {
        boost::asio::io_service io_service;

        udp::endpoint receiver_endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);

        udp::socket socket(io_service); // (1)
        socket.open(udp::v4());

        boost::array<char, 1> send_buf = {0};                             // (2)
        socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint); // (3)

        boost::array<char, 128> recv_buf; // (4)
        udp::endpoint           sender_endpoint;
        size_t                  len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint); // (5)

        std::cout.write(recv_buf.data(), len); // (6)
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}