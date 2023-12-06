#include "commandsToServer.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>

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

                              boost::array<char, 128>        recvBuf{};
                              boost::asio::ip::udp::endpoint senderEndpoint;
                              size_t len = socket.receive_from(boost::asio::buffer(recvBuf), senderEndpoint);

                              std::cout.write(recvBuf.data(), len);

                              if (len >= 7 && std::string(recvBuf.data(), 7) == "NEW_POS")
                              {
                                  m_newPos = recvBuf.data();
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
