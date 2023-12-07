#include "commandsToServer.hpp"

#include <bitset>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
std::string binaryToText(const std::string& binaryString)
{
    std::string text;

    // Iterate over the binary string in groups of 8 characters
    for (size_t i = 0; i < binaryString.length(); i += 8)
    {
        // Get the current group of 8 characters
        std::string binaryGroup = binaryString.substr(i, 8);

        // Convert the binary group to its decimal value
        int decimalValue = std::bitset<8>(binaryGroup).to_ulong();

        // Convert the decimal value to its ASCII character representation
        char character = static_cast<char>(decimalValue);
        // Append the character to the text string
        text += character;
    }

    return text;
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

                              socket.send_to(boost::asio::buffer(msg), receiverEndpoint);

                              boost::array<char, 2048>       recvBuf{};
                              boost::asio::ip::udp::endpoint senderEndpoint;
                              size_t len = socket.receive_from(boost::asio::buffer(recvBuf), senderEndpoint);

                              std::string asciiString(binaryToText(recvBuf.data()));
                              std::cout << asciiString << std::endl;

                              if (len >= 7 && std::string(asciiString.data(), 7) == "NEW_POS")
                              {
                                  m_newPos = asciiString;
                              }
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
