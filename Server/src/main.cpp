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
            boost::array<char, 128>   recvBuf{}; // (2)
            udp::endpoint             remoteEndpoint;
            boost::system::error_code error;
            socket.receive_from(boost::asio::buffer(recvBuf), remoteEndpoint, 0, error); // (3)

            std::cout << "Received: " << recvBuf.data() << std::endl;
            if (strcmp(recvBuf.data(), "TEST") == 0)
            {

                if (error && error != boost::asio::error::message_size) // (4)
                    throw boost::system::system_error(error);

                std::string message = "TEST_OK\n";

                boost::system::error_code ignoredError;
                socket.send_to(boost::asio::buffer(message), remoteEndpoint, 0, ignoredError); // (5)
            }
            // Jules
            if (recvBuf.size() >= 3 && std::string(recvBuf.data(), 3) == "POS")
            {
                if (error && error != boost::asio::error::message_size) // (4)
                    throw boost::system::system_error(error);
                
                std::string posString = recvBuf.data();
                std::istringstream iss(posString);
                std::vector<std::string> tokens;
                std::ostringstream newPos;

                // Reception et séparation pour plus de facilité de modification
                std::string token;
                while (std::getline(iss, token, ' '))
                {
                    tokens.push_back(token);
                }

                // Calcul (ne marche que pour up pour l'instant)
                float newPosX = std::stof(tokens[1]);
                float newPosY = std::stof(tokens[2]);
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
                // to string, envoie vers client
                newPos << "NEW_POS " << newPosX << " " << newPosY << "\n";
                std::string message = newPos.str();

                boost::system::error_code ignoredError;
                socket.send_to(boost::asio::buffer(message), remoteEndpoint, 0, ignoredError); // (5)
            }
            // Jules
        }
    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
