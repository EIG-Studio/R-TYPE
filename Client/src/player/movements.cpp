/*
** EPITECH PROJECT, 2023
** Client
** File description:
** movements
*/

#include "components.hpp"
#include "entities.hpp"
#include "ipAdress.hpp"
#include "menu/inGame.hpp"

#include <iostream>
#include <sstream>

const float joystickThreshold = 20.0f;
const float spriteWidth = 103.0f;
const float spriteHeight = 37.75f;

struct MovementConfig
{
    sf::Keyboard::Key key;
    float deltaX;
    float deltaY;
    std::string spritePath;
    float windowLimit;
    float spriteLimit;
};

void updateSpriteTexture(sf::Sprite& sprite, const std::string& texturePath)
{
    static std::map<std::string, sf::Texture> textureCache;
    auto it = textureCache.find(texturePath);
    if (it == textureCache.end()) {
        sf::Texture texture;
        if (texture.loadFromFile(texturePath)) {
            auto inserted = textureCache.insert({texturePath, texture});
            it = inserted.first;
        } else {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
            return;
        }
    }
    sprite.setTexture(it->second);
}

void updateSpritePositionAndPath(sf::Sprite& sprite, float newX, float newY, const std::string& texturePath)
{
    sprite.setPosition(newX, newY);

    updateSpriteTexture(sprite, texturePath);
}

void Game::movePlayer(
    Registry& registry,
    float movementSpeed,
    float /*winX*/,
    float winY,
    CommandsToServer& commandsToServer,
    const Sprite& /*mSprite*/,
    IpAdress& ipAdress)
{
    Entity player;
    try {
        player = registry.getEntity(setPlayer(-1));
        if (!this->hasFocus) {
            return;
        }
    } catch (std::exception& e) {
        std::cout << "Player not found: " << e.what() << std::endl;
        return;
    }
    std::vector<Entity> list = registry.getListEntities();
    Position playerPos = registry.getComponent(player, Position{});
    std::pair<float, float> pairPos = playerPos.getPosition();
    Renderer playerRenderer = registry.getComponent(player, Renderer{});
    float initialPosX = pairPos.first;
    float initialPosY = pairPos.second;

    ID idP = registry.getComponent(player, ID{});
    std::vector<MovementConfig> movements =
        {{sf::Keyboard::Up, 0, -movementSpeed, "../Client/assets/Cars/189_toUp.png", winY, spriteHeight},
         {sf::Keyboard::Z, 0, -movementSpeed, "../Client/assets/Cars/189_toUp.png", winY, spriteHeight},
         {sf::Keyboard::Right, 0, -movementSpeed, "../Client/assets/Cars/189_toRight.png", winY, spriteHeight},
         {sf::Keyboard::D, 0, -movementSpeed, "../Client/assets/Cars/189_toRight.png", winY, spriteHeight},
         {sf::Keyboard::Down, 0, -movementSpeed, "../Client/assets/Cars/189_toDown.png", winY, spriteHeight},
         {sf::Keyboard::S, 0, -movementSpeed, "../Client/assets/Cars/189_toDown.png", winY, spriteHeight},
         {sf::Keyboard::Left, 0, -movementSpeed, "../Client/assets/Cars/189_toLeft.png", winY, spriteHeight},
         {sf::Keyboard::Q, 0, -movementSpeed, "../Client/assets/Cars/189_toLeft.png", winY, spriteHeight}};

    for (const auto& config : movements) {
        handleMovement(
            registry,
            config.key,
            commandsToServer,
            movementSpeed,
            config.deltaX,
            config.deltaY,
            config.spritePath,
            config.windowLimit,
            config.spriteLimit,
            ipAdress);
    }
    if (initialPosX == pairPos.first && initialPosY == pairPos.second) {
        playerRenderer.setRenderer("../Client/assets/Cars/189_neutral.png");
    }
}

std::string Game::inputTypeToString(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::Left:
        case sf::Keyboard::Q:
            return "LEFT";

        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            return "RIGHT";

        case sf::Keyboard::Up:
        case sf::Keyboard::Z:
            return "UP";

        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            return "DOWN";

        default:
            return "UNKNOWN";
    }
}

void Game::handleMovement(
    Registry& registry,
    sf::Keyboard::Key key,
    CommandsToServer& commandsToServer,
    float /*movementSpeed*/,
    float deltaX,
    float deltaY,
    const std::string& path,
    float windowLimit,
    float spriteLimit,
    IpAdress& ipAdress)
{
    bool keyPressed = sf::Keyboard::isKeyPressed(key);

    Entity player = registry.getEntity(setPlayer(-1));
    Position playerPos = registry.getComponent(player, Position{});
    std::pair<float, float> pairPos = playerPos.getPosition();
    Renderer playerRenderer = registry.getComponent(player, Renderer{});
    sf::Sprite playerSprite = playerRenderer.getRenderer();

    if (keyPressed) {
        std::string inputType = inputTypeToString(key);
        if (m_updateClock.getElapsedTime().asSeconds() >= 0.0003f) {
            sendInputUpdate(commandsToServer, registry, inputType, ipAdress);
            m_updateClock.restart();
        }
        if (((deltaX != 0 && pairPos.first >= 0 && pairPos.first <= windowLimit - spriteLimit) ||
             (deltaY != 0 && pairPos.second >= 0 && pairPos.second <= windowLimit - spriteLimit)) &&
            (pairPos.first != playerSprite.getPosition().x || pairPos.second != playerSprite.getPosition().y)) {
            updateSpritePositionAndPath(playerSprite, pairPos.first, pairPos.second, path);
        }
    }
}

void Game::sendInputUpdate(CommandsToServer& commandsToServer, Registry& registry, const std::string& inputType, IpAdress& ipAdress)
{
    std::ostringstream oss;
    Entity player;
    try {
        player = registry.getEntity(setPlayer(-1));
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return;
    }
    ID playerId = registry.getComponent(player, ID{});
    oss << inputType << " " << playerId.getID();
    std::string inputString = oss.str();
    commandsToServer.sendToServerAsync(inputString, ipAdress);
}

void Game::shooting(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress)
{
    Entity player = registry.getEntity(setPlayer(-1));
    Position playerPos = registry.getComponent(player, Position{});
    std::pair<float, float> pairPos = playerPos.getPosition();
    std::ostringstream shooting;
    auto blueProjectile = registry.getComponent(player, PowerUp{}).getBlueProjectile();

    if (blueProjectile) {
        shooting << "BLUE_PROJECILE " << pairPos.first + 100 << " " << pairPos.second + 10;
    } else {
        shooting << "SHOOT " << pairPos.first + 100 << " " << pairPos.second + 10;
    }
    commandsToServer.sendToServerAsync(shooting.str(), ipAdress);
}

void Game::checkGetPowerUp(Registry& registry)
{
    Entity player = registry.getEntity(setPlayer(-1));
    Position playerPos = registry.getComponent(player, Position{});
    std::pair<float, float> pairPos = playerPos.getPosition();

    try {
        Entity blueProjectile = registry.getFirstEntityOfType(EntityType::Power_Up);
        Position blueProjectilePos = registry.getComponent(blueProjectile, Position{});
        std::pair<float, float> bluePairPos = blueProjectilePos.getPosition();

        if (registry.getComponent(player, Position{}).getPosition().first >= bluePairPos.first &&
            registry.getComponent(player, Position{}).getPosition().first <= bluePairPos.first + 1000 &&
            registry.getComponent(player, Position{}).getPosition().second >= bluePairPos.second &&
            registry.getComponent(player, Position{}).getPosition().second <= bluePairPos.second + 1000) {
            registry.getComponent(player, PowerUp{}).setBlueProjectile(true);
            registry.setEntity(player, registry.getComponent(player, ID{}).getID());
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

///// For Test
void Game::damageToPlayer(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress)
{
    Entity player = registry.getEntity(setPlayer(-1));
    ID playerId = registry.getComponent(player, ID{});
    int id = playerId.getID();
    std::ostringstream damage;

    damage << "DAMAGE_TO_PLAYER " << 1 << " " << id;
    commandsToServer.sendToServerAsync(damage.str(), ipAdress);
}
