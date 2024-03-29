/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** commandsToServer
*/

#pragma once

#include "Systems.hpp"
#include "entities.hpp"
#include "ipAdress.hpp"
#include "menu/menus.hpp"
#include "music/sounds.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <future>
#include <mutex>
#include <string>
#include <thread>

int setPlayer(int id);

class Game;
class Sprite;

class CommandsToServer
{
public:
    CommandsToServer(const CommandsToServer&) = delete;
    CommandsToServer& operator=(const CommandsToServer&) = delete;

    CommandsToServer() :
    m_socket(m_ioService),
    m_receiverEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 7171),
    m_work(std::make_unique<boost::asio::io_service::work>(m_ioService))
    {
        m_socket.open(boost::asio::ip::udp::v4());
        m_ioServiceThread = std::thread([this]() { m_ioService.run(); });
    }

    ~CommandsToServer()
    {
        m_work.reset();
        if (m_ioServiceThread.joinable()) {
            m_ioServiceThread.join();
        }
    }

    std::string getNewPos() const;

    std::future<void> sendToServerAsync(const std::string& msg, IpAdress& ipAdress);
    void asyncReceive(Registry& registry, Music& music, Game& game, YouWinMenu& youWinMenu, YouLooseMenu& youLooseMenu, Sprite& sprite);
    std::mutex mutex;

private:
    std::string m_newPos;
    boost::asio::io_service m_ioService;
    std::thread m_ioServiceThread;
    std::unique_ptr<boost::asio::io_service::work> m_work;

    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_receiverEndpoint;

    unsigned char m_buffer[sizeof(TransferData)]{};
};
