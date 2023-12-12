#include "commandsToServer.hpp"

#include <bitset>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

std::string binaryToText(const std::string& binaryString)
{
    int decimalValue = 0;
    char character = 0;
    std::string text;

    for (size_t i = 0; i < binaryString.length(); i += 8) {
        decimalValue = std::bitset<8>(binaryString.substr(i, 8)).to_ulong();
        character = static_cast<char>(decimalValue);
        text += character;
    }
    return text;
}

void handleReceive(const boost::system::error_code& error, size_t len, boost::array<char, 2048>& recvBuf, std::string& mNewPos)
{
    if (!error && len > 0) {
        std::string asciiString(binaryToText(recvBuf.data()));
        std::cout << asciiString;

        if (asciiString.find("NEW_POS") == 0) {
            mNewPos = asciiString;
        } else if (asciiString.find("UPDATE") == 0) {
            // updateEntity();
        } else if (asciiString.find("NEW") == 0) {
            // createEntity();
        } else if (asciiString.find("WIN") == 0) {
            // win();
        } else if (asciiString.find("LOOSE") == 0) {
            // loose();
        }
    } else {
        std::cerr << "Error in handleReceive: " << error.message() << std::endl;
    }
}

void sendToServer(boost::asio::ip::udp::socket& socket, const std::string& msg)
{
    boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);
    socket.send_to(boost::asio::buffer(msg), receiverEndpoint);
}

void asyncReceive(boost::asio::ip::udp::socket& socket, boost::array<char, 2048>& recvBuf, std::string& mNewPos)
{
    socket.async_receive(boost::asio::buffer(recvBuf), [&recvBuf, &mNewPos](auto&& pH1, auto&& pH2) {
        return handleReceive(std::forward<decltype(pH1)>(pH1), std::forward<decltype(pH2)>(pH2), recvBuf, mNewPos);
    });
}

std::future<void> CommandsToServer::sendToServerAsync(std::string msg)
{
    return std::async(std::launch::async, [this, msg = std::move(msg)] {
        try {
            boost::asio::io_service ioService;
            boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171);
            boost::asio::ip::udp::socket socket(ioService);
            boost::array<char, 2048> recvBuf{};

            socket.open(boost::asio::ip::udp::v4());
            sendToServer(socket, msg);
            asyncReceive(socket, recvBuf, m_newPos);
            ioService.run();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    });
}

std::string CommandsToServer::getNewPos() const
{
    return m_newPos;
}
