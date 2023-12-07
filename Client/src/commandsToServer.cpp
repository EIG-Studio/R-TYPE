#include "commandsToServer.hpp"

#include <bitset>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

std::string binaryToText(const std::string& binaryString)
{
    std::string text;

    for (size_t i = 0; i < binaryString.length(); i += 8)
    {
        std::string binaryGroup = binaryString.substr(i, 8);

        int decimalValue = std::bitset<8>(binaryGroup).to_ulong();

        char character = static_cast<char>(decimalValue);
        text += character;
    }

    return text;
}

void handleReceive(const boost::system::error_code& error, size_t len, boost::array<char, 2048>& recvBuf, std::string& mNewPos)
{
    if (!error && len >= 7)
    {
        std::string asciiString(binaryToText(recvBuf.data()));
        std::cout << asciiString << std::endl;

        if (std::string(asciiString.data(), 7) == "NEW_POS")
        {
            mNewPos = asciiString;
        }
    }
    else
    {
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
    socket.async_receive(boost::asio::buffer(recvBuf),
                         [&recvBuf, &mNewPos](auto&& pH1, auto&& pH2) {
                             return handleReceive(std::forward<decltype(pH1)>(pH1),
                                                  std::forward<decltype(pH2)>(pH2),
                                                  recvBuf,
                                                  mNewPos);
                         });
}

std::future<void> CommandsToServer::sendToServerAsync(std::string msg)
{
    return std::async(std::launch::async,
                      [this, msg = std::move(msg)]
                      {
                          try
                          {
                              boost::asio::io_service ioService;

                              boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string(
                                                                                  "12"
                                                                                  "7."
                                                                                  "0."
                                                                                  "0."
                                                                                  "1"),
                                                                              7171);

                              boost::asio::ip::udp::socket socket(ioService);
                              socket.open(boost::asio::ip::udp::v4());

                              sendToServer(socket, msg);

                              boost::array<char, 2048> recvBuf{};
                              asyncReceive(socket, recvBuf, m_newPos);

                              ioService.run();
                          } catch (std::exception& e)
                          {
                              std::cerr << e.what() << std::endl;
                          }
                      });
}

std::string CommandsToServer::getNewPos() const
{
    return m_newPos;
}
