/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** command
*/

#include "components.hpp"
#include "entities.hpp"
#include "server.hpp"

#include <iostream>
#include <ostream>
#include <random>
#include <string>

std::size_t Server::createPlayer(Registry& registry)
{
    Entity entity = registry.createEntity();
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(100, 100));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(5);
    Type typeComponent = std::any_cast<EntityType>(Player);
    HealthPoint healthPoint(20);
    HitBox hb = HitBox(positionComponent.getPosition(), std::make_pair(100, 50));
    Velocity velocityComponent = Velocity();
    velocityComponent.setVelocity(0, 0);
    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);
    entity = registry.addComponent(entity, healthPoint);
    entity = registry.addComponent(entity, hb);
    entity = registry.addComponent(entity, velocityComponent);

    std::ostringstream newPlayer;
    newPlayer << "NEW_PLAYER " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
              << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
              << healthPoint.getHealthPoint() << " " << sizeComponent.getSize().first << " "
              << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayer.str());
    return registry.getComponent(entity, idComponent).getID();
}

int randNb(int x, int y)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(x, y);
    return distrib(gen);
}

void Server::createEnemy(Registry& registry)
{
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(randNb(1200, 2000), randNb(0, 500)));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(randNb(5, 10));
    Type typeComponent = std::any_cast<EntityType>(Enemy);
    HealthPoint healthPoint(5);
    HitBox hb = HitBox(positionComponent.getPosition(), std::make_pair(100, 50));
    Damage damage(1);

    Entity entity = registry.createEntity();
    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);
    entity = registry.addComponent(entity, healthPoint);
    entity = registry.addComponent(entity, hb);
    entity = registry.addComponent(entity, damage);

    std::ostringstream newPlayer2;
    newPlayer2 << "NEW_ENEMY " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
               << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
               << healthPoint.getHealthPoint() << " " << sizeComponent.getSize().first << " "
               << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayer2.str());
}

void Server::createBoss(Registry& registry)
{
    ID idComponent = ID();
    Position positionComponent = Position(std::make_pair(randNb(1000, 1100), randNb(0, 500)));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(randNb(1, 3));
    Type typeComponent = std::any_cast<EntityType>(Enemy);
    HealthPoint healthPointComponent(50);

    Entity entity = registry.createEntity();
    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);
    entity = registry.addComponent(entity, healthPointComponent);

    std::ostringstream newPlayer2;
    newPlayer2 << "NEW_BOSS " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
               << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
               << healthPointComponent.getHealthPoint() << " " << sizeComponent.getSize().first << " "
               << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayer2.str());
}

void Server::damageThePlayer(Registry& registry, int damage, int id)
{
    Entity entity = registry.getEntity(id);
    HealthPoint& healthPoint = registry.getComponent(entity, HealthPoint{});

    healthPoint.setHealthPoint(healthPoint.getHealthPoint() - damage);
    std::ostringstream newHealth;
    newHealth << "NEW_HEALTH " << id << " " << healthPoint.getHealthPoint() << "\n";
    addMessage(newHealth.str());
    registry.setEntity(entity, id);
}

void Server::createBullet(Registry& registry, int posx, int posy)
{
    Entity entity = registry.createEntity();
    ID idComponent = ID();
    auto positionComponent = Position(std::make_pair(posx, posy));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(15);
    Type typeComponent = std::any_cast<EntityType>(Player_Projectile);
    HealthPoint healthPoint(1);
    Damage damage(3);
    Velocity velocityComponent = Velocity();

    velocityComponent.setVelocity(1, 0);

    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);
    entity = registry.addComponent(entity, healthPoint);
    entity = registry.addComponent(entity, damage);
    entity = registry.addComponent(entity, velocityComponent);
    entity = registry.addComponent(entity, HitBox(positionComponent.getPosition(), std::make_pair(50, 50)));

    std::ostringstream newPlayerProjectile;
    newPlayerProjectile << "PLAYER_PROJECTILE " << static_cast<int>(registry.getComponent(entity, idComponent).getID())
                        << " " << positionComponent.getPosition().first << " " << positionComponent.getPosition().second
                        << " " << healthPoint.getHealthPoint() << " " << sizeComponent.getSize().first << " "
                        << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayerProjectile.str());
}

void Server::createPowerUp(Registry& registry, int posx, int posy)
{
    Entity entity = registry.createEntity();
    ID idComponent = ID();
    auto positionComponent = Position(std::make_pair(posx, posy));
    Size sizeComponent = Size(std::make_pair(1, 1));
    Speed speedComponent(15);
    Type typeComponent = std::any_cast<EntityType>(Power_Up);
    HealthPoint healthPoint(1);
    Damage damage(3);
    Velocity velocityComponent = Velocity();

    velocityComponent.setVelocity(1, 0);

    entity = registry.addComponent(entity, idComponent);
    entity = registry.addComponent(entity, positionComponent);
    entity = registry.addComponent(entity, sizeComponent);
    entity = registry.addComponent(entity, speedComponent);
    entity = registry.addComponent(entity, typeComponent);
    entity = registry.addComponent(entity, healthPoint);
    entity = registry.addComponent(entity, damage);
    entity = registry.addComponent(entity, velocityComponent);
    entity = registry.addComponent(entity, HitBox(positionComponent.getPosition(), std::make_pair(50, 50)));

    std::ostringstream newPlayerProjectile;
    newPlayerProjectile << "POWER_UP " << static_cast<int>(registry.getComponent(entity, idComponent).getID()) << " "
                        << positionComponent.getPosition().first << " " << positionComponent.getPosition().second << " "
                        << healthPoint.getHealthPoint() << " " << sizeComponent.getSize().first << " "
                        << sizeComponent.getSize().second << " " << typeComponent << "\n";
    addMessage(newPlayerProjectile.str());
}

void Server::addMessage(const std::string& message)
{
    this->m_messageMutex.lock();
    TransferData data{.command = EMPTY, .args = {0, 0, 0, 0}};
    std::istringstream iss(message);
    int i = 0;
    std::cout << "\033[1;32m"
              << "[SERVER]: \033[0m" << message;
    std::string word;
    iss >> word;
    data.command = getCommand(word);
    while (iss >> word) {
        try {
            data.args[i] = std::stoi(word);
        } catch (const std::exception& e) {
            data.args[i] = getType(word);
        }
        i++;
    }
    m_messages.emplace_front(data);
    this->m_messageMutex.unlock();
}

void Server::playerMove(Registry& registry, COMMAND direction, std::size_t id)
{
    Entity entity = registry.getEntity(id);
    Position& positionComponent = registry.getComponent(entity, Position());
    Speed speedComponent = registry.getComponent(entity, Speed());

    if (direction == DOWN)
        positionComponent.setPosition(std::make_pair(
            positionComponent.getPosition().first,
            positionComponent.getPosition().second + 1 * speedComponent.getSpeed()));
    else if (direction == RIGHT)
        positionComponent.setPosition(std::make_pair(
            positionComponent.getPosition().first + 1 * speedComponent.getSpeed(),
            positionComponent.getPosition().second));
    else if (direction == UP)
        positionComponent.setPosition(std::make_pair(
            positionComponent.getPosition().first,
            positionComponent.getPosition().second - 1 * speedComponent.getSpeed()));
    else if (direction == LEFT)
        positionComponent.setPosition(std::make_pair(
            positionComponent.getPosition().first - 1 * speedComponent.getSpeed(),
            positionComponent.getPosition().second));

    std::string newPos = "NEW_POS " + std::to_string(id) + " " + std::to_string(positionComponent.getPosition().first) +
                         " " + std::to_string(positionComponent.getPosition().second) + "\n";
    addMessage(newPos);
    registry.setEntity(entity, id);
}

void Server::sendAllEntites(Registry& registry)
{
    for (auto& entity : registry.getListEntities()) {
        std::ostringstream oss;
        EntityType type = registry.getComponent(entity, Type{}).getEntityType();
        if (type == Player)
            oss << "NEW_PLAYER ";
        else if (type == Enemy)
            oss << "NEW_ENEMY ";
        else if (type == Player_Projectile)
            oss << "PLAYER_PROJECTILE ";
        else if (type == Power_Up)
            oss << "POWER_UP ";
        else if (type == Enemy_Projectile)
            oss << "ENEMY_PROJECTILE ";
        else if (type == HUD)
            oss << "NEW_HUD ";
        else
            oss << "UNKNOWN ";

        if (type == Player || type == Enemy || type == Player_Projectile || type == Power_Up || type == Enemy_Projectile) {
            auto positionComponent = registry.getComponent(entity, Position{});
            auto xPosition = positionComponent.getPosition().first;
            auto yPosition = positionComponent.getPosition().second;

            auto sizeComponent = registry.getComponent(entity, Size{});
            auto xSize = sizeComponent.getSize().first;
            auto ySize = sizeComponent.getSize().second;

            auto healthPoint = registry.getComponent(entity, HealthPoint{});
            auto health = healthPoint.getHealthPoint();

            oss << registry.getComponent(entity, ID{}).getID() << " " << xPosition << " " << yPosition << " " << health
                << " " << xSize << " " << ySize << " " << registry.getComponent(entity, Type{}).getEntityType()
                << std::endl;
            addMessage(oss.str());
        } else if (type == HUD) {
            std::cout << "SCOOOREEEE\n";
            ScorePoint score = registry.getComponent(entity, ScorePoint{});
            oss << registry.getComponent(entity, ID{}).getID() << " " << std::to_string(score.getScorePoint()) << std::endl;
            addMessage(oss.str());
        }
    }
}

void Server::refreshClientRegistry(Registry& registry, int id)
{
    if (!registry.hasEntity(id)) {
        addMessage("DELETE " + std::to_string(id) + "\n");
    }
}

void createWall(Registry& registry, int posx, int posy, int sizex, int sizey)
{
    Entity wall = registry.createEntity();
    Position position = Position{std::make_pair(posx, posy)};
    Size size = Size{std::make_pair(sizex, sizey)};
    Type type = Type{std::any_cast<EntityType>(Wall)};
    HitBox hitbox = HitBox{position.getPosition(), size.getSize()};
    HealthPoint healthPoint = HealthPoint{10000};
    ID idComponent = ID();

    wall = registry.addComponent(wall, idComponent);
    wall = registry.addComponent(wall, position);
    wall = registry.addComponent(wall, healthPoint);
    wall = registry.addComponent(wall, type);
    wall = registry.addComponent(wall, hitbox);
}

bool Server::startGame(Registry& registry)
{
    std::cout << "Game started" << std::endl;
    createEnemy(registry);
    createEnemy(registry);
    createEnemy(registry);
    createEnemy(registry);
    createWall(registry, 800, -10, 100, 600);
    createWall(registry, -100, -10, 90, 600);
    createWall(registry, -10, -100, 800, 100);
    createWall(registry, -10, 600, 800, 100);

    Entity entityScore = registry.createEntity();
    ID scoreId = registry.getComponent(entityScore, ID());
    Type type = HUD;
    ScorePoint score{};
    score.setScorePoint(0);
    entityScore = registry.addComponent(entityScore, type);
    entityScore = registry.addComponent(entityScore, score);
    addMessage("NEW_HUD " + std::to_string(scoreId.getID()) + " " + std::to_string(score.getScorePoint()) + "\n");
    registry.setEntity(entityScore, scoreId);
    std::cout << "CREATE\n";
    return true;
}

void Server::handleReceivedData(
    const boost::system::error_code& error,
    std::size_t bytesReceived,
    Registry& registry,
    boost::asio::ip::udp::endpoint& remoteEndpoint)
{
    if (!error && bytesReceived > 0) {
        TransferData receivedData{};
        std::memcpy(&receivedData, m_buffer, sizeof(receivedData));

        if (receivedData.command == SHOOT) {
            createBullet(registry, receivedData.args[0], receivedData.args[1]);
        } else if (receivedData.command == POWER_UP) {
            createPowerUp(registry, receivedData.args[0], receivedData.args[1]);
        } else if (receivedData.command == DAMAGE_TO_PLAYER) {
            damageThePlayer(registry, receivedData.args[0], receivedData.args[1]);
        } else if (receivedData.command == LOGIN) {
            if (!m_gameStarted)
                m_gameStarted = startGame(registry);
            std::size_t id = createPlayer(registry);
            addClient(remoteEndpoint, id);
            sendAllEntites(registry);
        } else if (receivedData.command == UPDATE) {
            sendAllEntites(registry);
        } else if (receivedData.command == NEW_ENEMY) {
            createEnemy(registry);
        } else if (
            receivedData.command == DOWN || receivedData.command == UP || receivedData.command == LEFT ||
            receivedData.command == RIGHT) {
            playerMove(registry, receivedData.command, receivedData.args[0]);
        } else if (receivedData.command == REFRESH) {
            refreshClientRegistry(registry, receivedData.args[0]);
        } else if (receivedData.command == LEVEL) {
            m_currentLevel = receivedData.args[0];
        } else if (receivedData.command == ALIVE) {
            m_clientMutex.lock();
            for (Client& client : m_clients) {
                if (client == m_remoteEndpoint) {
                    client.setAlive(true);
                }
            }
            m_clientMutex.unlock();
        } else {
            std::ostringstream cmd;
            cmd << "Unknown command: " << receivedData.command << std::endl;
            addMessage(cmd.str());
        }
    }
}
