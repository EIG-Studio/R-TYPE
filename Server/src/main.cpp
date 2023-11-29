#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

using boost::array;
using boost::asio::ip::udp;

int main()
{
    try
    {
        boost::asio::io_service ioService;

        udp::socket socket(ioService, udp::endpoint(udp::v4(), 7171)); // (1)

        while (true)
        {
            boost::array<char, 128> recvBuf{}; // (2)
            udp::endpoint             remoteEndpoint;
            boost::system::error_code error;
            socket.receive_from(boost::asio::buffer(recvBuf), remoteEndpoint, 0, error); // (3)

            std::cout << "Received: " << recvBuf.data() << std::endl;

            if (error && error != boost::asio::error::message_size) // (4)
                throw boost::system::system_error(error);

            std::string message = "Bienvenue sur le serveur ! Mode non connecté.\n";

            boost::system::error_code ignoredError;
            socket.send_to(boost::asio::buffer(message), remoteEndpoint, 0, ignoredError); // (5)
        }
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
