/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** commandsToServer
*/

#pragma once

#include "Systems.hpp"
#include "components.hpp"
#include "entities.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class CommandsToServer
{
public:
    CommandsToServer(const CommandsToServer&) = delete;
    CommandsToServer& operator=(const CommandsToServer&) = delete;

    CommandsToServer() :
    socket(ioService),
    secondSocket(ioService),
    receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171),
    work(std::make_unique<boost::asio::io_service::work>(ioService))
    {
        std::cout << "CommandsToServer constructor called." << std::endl;

        socket.open(boost::asio::ip::udp::v4());
        secondSocket.open(boost::asio::ip::udp::v4());

        ioServiceThread = std::thread([this]() {
            std::cout << "ioService thread starting." << std::endl;
            ioService.run();
            std::cout << "ioService thread ending." << std::endl;
        });

        std::cout << "CommandsToServer constructor finished." << std::endl;
    }

    ~CommandsToServer()
    {
        work.reset(); // Allow io_service to exit
        if (ioServiceThread.joinable()) {
            ioServiceThread.join();
        }
    }

    std::string getNewPos() const;

    std::future<void> sendToServerAsync(std::string msg);
    void asyncReceive(Registry& registry);
    void asyncReceiveSecondSocket(Registry& registry);
    // void handlReceiveSecondSocket(
    //     Registry& registry,
    //     const boost::system::error_code& error,
    //     size_t len,
    //     boost::array<char, 128> recvBuf,
    //     std::string& mNewPos);
    // void processMessage(const std::string& asciiString, Registry& registry);

    std::mutex mutex;

private:
    std::string m_newPos;
    boost::asio::io_service ioService;
    std::thread ioServiceThread;
    std::unique_ptr<boost::asio::io_service::work> work;

    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint receiverEndpoint;

    boost::asio::ip::udp::socket secondSocket;
    boost::asio::ip::udp::endpoint senderEndpoint;

    unsigned char m_buffer[sizeof(transferData)];
};
