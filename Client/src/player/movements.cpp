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

void Game::movePlayer(Registry& registry, float movementSpeed, float winX, float winY, CommandsToServer& commandsToServer, Sprite mSprite, IpAdress& ipAdress)
{
    Entity player;
    try {
        player = registry.getPlayer();
        if (!this->hasFocus) {
            return;
        }
    } catch (std::exception& e) {
        std::cout << e.what();
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
        HandleMovement(
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

std::string Game::InputTypeToString(sf::Keyboard::Key key)
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

void Game::HandleMovement(
    Registry& registry,
    sf::Keyboard::Key key,
    CommandsToServer& commandsToServer,
    float movementSpeed,
    float deltaX,
    float deltaY,
    const std::string& path,
    float windowLimit,
    float spriteLimit,
    IpAdress& ipAdress)
{
    bool keyPressed = sf::Keyboard::isKeyPressed(key);

    Entity player = registry.getPlayer();
    Position playerPos = registry.getComponent(player, Position{});
    std::pair<float, float> pairPos = playerPos.getPosition();
    Renderer playerRenderer = registry.getComponent(player, Renderer{});
    sf::Sprite playerSprite = playerRenderer.getRenderer();

    if (keyPressed) {
        std::string inputType = InputTypeToString(key);
        if (updateClock.getElapsedTime().asSeconds() >= 0.0003f) {
            SendInputUpdate(commandsToServer, registry, inputType, ipAdress);
            updateClock.restart();
        }
        if (((deltaX != 0 && pairPos.first >= 0 && pairPos.first <= windowLimit - spriteLimit) ||
             (deltaY != 0 && pairPos.second >= 0 && pairPos.second <= windowLimit - spriteLimit)) &&
            (pairPos.first != playerSprite.getPosition().x || pairPos.second != playerSprite.getPosition().y)) {
            updateSpritePositionAndPath(playerSprite, pairPos.first, pairPos.second, path);
        }
    }
}

void Game::SendInputUpdate(CommandsToServer& commandsToServer, Registry& registry, const std::string& inputType, IpAdress& ipAdress)
{
    std::ostringstream oss;
    Entity player;
    try {
        player = registry.getPlayer();
    } catch (std::exception& e) {
        std::cout << e.what();
        return;
    }
    ID playerId = registry.getComponent(player, ID{});
    oss << inputType << " " << playerId.getID();
    std::string inputString = oss.str();
    commandsToServer.sendToServerAsync(inputString, ipAdress);
}

void Game::shooting(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress)
{
    Entity player = registry.getPlayer();
    Position playerPos = registry.getComponent(player, Position{});
    std::pair<float, float> pairPos = playerPos.getPosition();
    std::ostringstream shooting;
    shooting << "SHOOT " << pairPos.first << " " << pairPos.second;
    commandsToServer.sendToServerAsync(shooting.str(), ipAdress);
}

void Game::displayArrow(Registry& registry, WindowManager& windowManager)
{
    Entity player = registry.getPlayer();
    Position playerPos = registry.getComponent(player, Position{});
    std::pair<float, float> pairPos = playerPos.getPosition();
    sf::Texture texture;
    sf::Sprite sprite;
    if (!texture.loadFromFile("../Client/assets/arrow.png")) {
        std::cerr << "Failed to load arrow texture" << std::endl;
        return;
    }
    sprite.setTexture(texture);
    sprite.setPosition(pairPos.first + 46, pairPos.second - 30);
    sprite.setScale(0.04, 0.04);
    windowManager.getWindow().draw(sprite);
}
