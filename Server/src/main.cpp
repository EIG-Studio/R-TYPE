#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main()
{
    try
    {
        boost::asio::io_service io_service;

        udp::socket socket(io_service, udp::endpoint(udp::v4(), 7171)); // (1)

        while (1)
        {
            boost::array<char, 1>     recv_buf; // (2)
            udp::endpoint             remote_endpoint;
            boost::system::error_code error;
            socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint, 0, error); // (3)

            if (error && error != boost::asio::error::message_size) // (4)
                throw boost::system::system_error(error);

            std::string message = "Bienvenue sur le serveur ! Mode non connecté.";

            boost::system::error_code ignored_error;
            socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error); // (5)
        }
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}