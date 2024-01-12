/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** commandsToServer
*/

#include "commandsToServer.hpp"

#include "Systems.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/query.hpp>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>

#include <cstdlib>

void log(const std::string& message)
{
    std::cout << "[LOG] " << message << std::endl;
}

std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
}

int randNb(int x, int y)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(x, y);
    return distrib(gen);
}

void updatePosition(Registry& registry, int id, int xPos, int yPos)
{
    try {
        Entity entity = registry.getEntity(id);
        if (registry.hasComponent(entity, Position{})) {
            Position& entityPos = registry.getComponent(entity, Position{});
            entityPos.setPosition(std::make_pair(xPos, yPos));
            registry.setEntity(entity, id);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in updatePosition: " << e.what() << std::endl;
    }
}

void updateHealth(Registry& registry, int id, int health)
{
    try {
        Entity entity = registry.getEntity(id);
        if (registry.hasComponent(entity, HealthPoint{})) {
            HealthPoint& entityPos = registry.getComponent(entity, HealthPoint{});
            entityPos.setHealthPoint(health);
            registry.setEntity(entity, id);
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in updateHealth: " << e.what() << std::endl;
    }
}

void createPlayer(Registry& registry, int id, int xPos, int yPos, int healthPoint)
{
    if (registry.hasEntity(id))
        return;
    Entity player = registry.createEntityWithID(id);
    player = registry.addComponent(player, Position(std::make_pair(xPos, yPos)));
    player = registry.addComponent(player, HealthPoint(healthPoint));
    player = registry.addComponent(player, Renderer("../Client/assets/Cars/189.png"));
    player = registry.addComponent(player, Type(std::any_cast<EntityType>(Player)));
    player = registry.addComponent(
        player,
        Size(std::make_pair(
            103 / registry.getComponent(player, Renderer{}).getRenderer().getLocalBounds().width,
            56.25 / registry.getComponent(player, Renderer{}).getRenderer().getLocalBounds().height)));
    registry.setEntity(player, id);
}

void createEnemy(Registry& registry, int id, int xPos, int yPos)
{
    Entity enemy = registry.createEntityWithID(id);
    enemy = registry.addComponent(enemy, Position(std::make_pair(xPos, yPos)));
    enemy = registry.addComponent(enemy, Renderer("../Client/assets/Cars/cars/190.png"));
    enemy = registry.addComponent(enemy, Type(std::any_cast<EntityType>(Enemy)));
    enemy = registry.addComponent(
        enemy,
        Size(std::make_pair(
            103 / registry.getComponent(enemy, Renderer{}).getRenderer().getLocalBounds().width,
            56.25 / registry.getComponent(enemy, Renderer{}).getRenderer().getLocalBounds().height)));

    Position enemyPos = registry.getComponent(enemy, Position{});
    std::pair<int, int> pairPos = enemyPos.getPosition();

    std::cout << "Enemy created pos: " << pairPos.first << " " << pairPos.second << '\n';
}

void createBoss(Registry& registry, int id, int xPos, int yPos)
{
    Entity boss = registry.createEntityWithID(id);
    boss = registry.addComponent(boss, Position(std::make_pair(xPos, yPos)));
    boss = registry.addComponent(boss, Renderer("../Client/assets/Boss/v-police.png"));
    boss = registry.addComponent(boss, Type(std::any_cast<EntityType>(Enemy)));
    boss = registry.addComponent(boss, Size(std::make_pair(2, 2)));

    Position bossPos = registry.getComponent(boss, Position{});
    std::pair<int, int> pairPos = bossPos.getPosition();

    std::cout << "Boss created pos: " << pairPos.first << " " << pairPos.second << '\n';
}

void createPlayerProjectile(Registry& registry, int id, int xPos, int yPos)
{
    std::cout << "Player projectile created" << std::endl;
    Entity playerProjectile = registry.createEntityWithID(id);
    playerProjectile = registry.addComponent(playerProjectile, Position(std::make_pair(xPos, yPos)));
    playerProjectile = registry.addComponent(playerProjectile, Renderer("../Client/assets/Cars/movement parts/thruster/flame.png"));
    playerProjectile = registry.addComponent(playerProjectile, Type(std::any_cast<EntityType>(Player_Projectile)));
    playerProjectile = registry.addComponent(
        playerProjectile,
        Size(std::make_pair(
            68.5 / registry.getComponent(playerProjectile, Renderer{}).getRenderer().getLocalBounds().width,
            21.25 / registry.getComponent(playerProjectile, Renderer{}).getRenderer().getLocalBounds().height)));

    Position playerProjectilePos = registry.getComponent(playerProjectile, Position{});
    std::pair<int, int> pairPos = playerProjectilePos.getPosition();
    std::cout << "Player projectile created pos: " << pairPos.first << " " << pairPos.second << '\n';
}

void createHud(Registry& registry, int id, int dataScore)
{
    std::cout << "NEW_HUD" << std::endl;
    Entity hud = registry.createEntityWithID(id);
    ScorePoint score{};

    score.setScorePoint(dataScore);
    hud = registry.addComponent(hud, Type(std::any_cast<EntityType>(HUD)));
    hud = registry.addComponent(hud, score);
    registry.setEntity(hud, id);
}

void createScore(Registry& registry, int dataScore)
{
    if (registry.hasEntityType(HUD)) {
        std::cout << "SCORE " << std::endl;
        Entity score = registry.getScore();
        ID scoreId = registry.getComponent(score, ID{});
        ScorePoint& scorePoints = registry.getComponent(score, ScorePoint{});
        scorePoints.setScorePoint(dataScore);
        registry.setEntity(score, scoreId);
    } else {
        std::cout << "[LOG] NO SCORE" << std::endl;
    }
}

void handleReceive(
    Registry& registry,
    const boost::system::error_code& error,
    size_t len,
    unsigned char buffer[sizeof(TransferData)],
    std::string& /*mNewPos*/,
    Music& music)
{
    if (!error && len == 0) {
        std::cout << "No data received, non-blocking return." << std::endl;
        return;
    }

    if (!error && len > 0) {
        TransferData receivedData{.command = EMPTY};
        std::memcpy(&receivedData, buffer, sizeof(receivedData));

        switch (receivedData.command) {
            case NEW_POS:
                updatePosition(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2]);
                break;
            case NEW_HEALTH:
                updateHealth(registry, receivedData.args[0], receivedData.args[1]);
                break;
            case NEW_PLAYER:
                createPlayer(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2], receivedData.args[3]);
                break;
            case NEW_ENEMY:
                createEnemy(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2]);
                break;
            case NEW_BOSS:
                createBoss(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2]);
                break;
            case PLAYER_PROJECTILE:
                createPlayerProjectile(registry, receivedData.args[0], receivedData.args[1], receivedData.args[2]);
                break;
            case DELETE:
                registry.deleteById(receivedData.args[0]);
                break;
            case PLAY_BOOM_ENEMIES:
                music.boomEnemies.play();
                break;
            case NEW_HUD:
                createHud(registry, receivedData.args[0], receivedData.args[1]);
                break;
            case SCORE:
                createScore(registry, receivedData.args[0]);
                break;
            default:
                std::cout << "[LOG] NO SCORE" << std::endl;
                break;
        }
    } else if (error) {
        std::cerr << "Error in handleReceive: " << error.message() << std::endl;
    }
}

void sendToServer(boost::asio::ip::udp::socket& socket, const std::string& msg, IpAdress& ipAdress)
{
    std::cout << "\033[1;31m"
              << "[CLIENT]: \033[0m" << msg << std::endl;
    TransferData data{};
    std::istringstream iss(msg);
    std::string word;
    iss >> word;
    data.command = getCommand(word);
    int i = 0;
    while (iss >> word) {
        try {
            data.args[i] = std::stoi(word);
        } catch (const std::exception& e) {
            data.args[i] = getType(word);
        }
        i++;
    }
    unsigned char buffer[sizeof(TransferData)];
    std::memcpy(buffer, &data, sizeof(TransferData));
    if (ipAdress.getUserInput().empty()) {
        ipAdress.setUserInput("127.0.0.1");
    }
    boost::asio::ip::udp::endpoint receiverEndpoint(boost::asio::ip::address::from_string(ipAdress.getUserInput()), 7171);
    socket.async_send_to(boost::asio::buffer(buffer), receiverEndpoint, [](const boost::system::error_code& ec, std::size_t /*bytes_transferred*/) {
        if (ec) {
            std::cerr << "Send error: " << ec.message() << std::endl;
        } else {
            // std::cout << "Sent " << bytes_transferred << " bytes to server." << std::endl;
        }
    });
}

void CommandsToServer::asyncReceive(Registry& registry, Music& music)
{
    m_socket.async_receive(boost::asio::buffer(m_buffer), [this, &registry, &music](auto&& pH1, auto&& pH2) {
        this->mutex.lock();
        handleReceive(std::ref(registry), std::forward<decltype(pH1)>(pH1), std::forward<decltype(pH2)>(pH2), m_buffer, m_newPos, music);
        this->mutex.unlock();
        memset(m_buffer, 0, sizeof(TransferData));
        asyncReceive(std::ref(registry), music);
    });
}

std::future<void> CommandsToServer::sendToServerAsync(const std::string& msg, IpAdress& ipAdress)
{
    std::shared_ptr<std::promise<void>> promise = std::make_shared<std::promise<void>>();

    m_ioService.post([this, msg, promise, &ipAdress]() {
        try {
            sendToServer(m_socket, msg, ipAdress);
            promise->set_value();
        } catch (const std::exception& e) {
            promise->set_exception(std::current_exception());
        }
    });

    return promise->get_future();
}

std::string CommandsToServer::getNewPos() const
{
    return m_newPos;
}
