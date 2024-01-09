/*
** EPITECH PROJECT, 2023
** Client
** File description:
** movements
*/

#include "../../GameEngine/include/components.hpp"
#include "../../GameEngine/include/entities.hpp"
#include "entities.hpp"
#include "menu/inGame.hpp"

#include <sstream>

#include <cstddef>

const float JOYSTICK_THRESHOLD = 20.0f;
const float SPRITE_WIDTH = 103.0f;
const float SPRITE_HEIGHT = 37.75f;

static void myLog(const std::string& message)
{
    std::cout << "[LOG] " << message << std::endl;
}

struct MovementConfig
{
    sf::Keyboard::Key key;
    float deltaX;
    float deltaY;
    std::string spritePath;
    float windowLimit;
    float spriteLimit;
};

void UpdateSpriteTexture(sf::Sprite& sprite, const std::string& texturePath)
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

void UpdateSpritePositionAndPath(sf::Sprite& sprite, float newX, float newY, const std::string& texturePath)
{
    sprite.setPosition(newX, newY);

    UpdateSpriteTexture(sprite, texturePath);
}

void Game::movePlayer(Registry& registry, float movementSpeed, float winX, float winY, CommandsToServer& commandsToServer, Sprite mSprite)
{
    Entity player;
    try {
        player = registry.getPlayer();
        if (this->hasFocus == false) {
            return;
        }
    } catch (std::exception &e) {
        std::cout << e.what();
        return;
    }
    std::vector<Entity> list = registry.getListEntities();
    Position player_pos = registry.getComponent(player, Position{});
    std::pair<float, float> pair_pos = player_pos.getPosition();
    Renderer player_renderer = registry.getComponent(player, Renderer{});
    float initialPosX = pair_pos.first;
    float initialPosY = pair_pos.second;

    ID id_p = registry.getComponent(player, ID{});
    std::vector<MovementConfig> movements =
        {{sf::Keyboard::Up, 0, -movementSpeed, "../Client/assets/Cars/189_toUp.png", winY, SPRITE_HEIGHT},
         {sf::Keyboard::Z, 0, -movementSpeed, "../Client/assets/Cars/189_toUp.png", winY, SPRITE_HEIGHT},
         {sf::Keyboard::Right, 0, -movementSpeed, "../Client/assets/Cars/189_toRight.png", winY, SPRITE_HEIGHT},
         {sf::Keyboard::D, 0, -movementSpeed, "../Client/assets/Cars/189_toRight.png", winY, SPRITE_HEIGHT},
         {sf::Keyboard::Down, 0, -movementSpeed, "../Client/assets/Cars/189_toDown.png", winY, SPRITE_HEIGHT},
         {sf::Keyboard::S, 0, -movementSpeed, "../Client/assets/Cars/189_toDown.png", winY, SPRITE_HEIGHT},
         {sf::Keyboard::Left, 0, -movementSpeed, "../Client/assets/Cars/189_toLeft.png", winY, SPRITE_HEIGHT},
         {sf::Keyboard::Q, 0, -movementSpeed, "../Client/assets/Cars/189_toLeft.png", winY, SPRITE_HEIGHT}};

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
            config.spriteLimit);
    }
    if (initialPosX == pair_pos.first && initialPosY == pair_pos.second) {
        player_renderer.setRenderer("../Client/assets/Cars/189_neutral.png");
    }
}

void Game::moveEnnemies(CommandsToServer& commandsToServer, Registry& registry, const std::vector<Entity>& ennemies)
{
    // for (auto ennemy : ennemies) {
    //     std::ostringstream oss;
    //     size_t id = registry.getComponent(ennemy, ID{}).getID();

    //     oss << "MOVE_ENNEMIES" << " " << id;
    //     commandsToServer.sendToServerAsync(oss.str());
    // }
}

void Game::movePlayerProjectile(CommandsToServer& commandsToServer, Registry& registry, const std::vector<Entity>& bullets)
{
    // for (auto bullet : bullets) {
    //     std::ostringstream oss;
    //     size_t id = registry.getComponent(bullet, ID{}).getID();

    //     oss << "MOVE_PROJECTILE" << " " << id;
    //     commandsToServer.sendToServerAsync(oss.str());
    // }
}

std::string Game::InputTypeToString(sf::Keyboard::Key key)
{
    //std::cout << "Key pressed " << key << " (int value: " << static_cast<int>(key) << ")\n";
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
    float spriteLimit)
{
    bool keyPressed = sf::Keyboard::isKeyPressed(key);

    Entity player = registry.getPlayer();
    Position player_pos = registry.getComponent(player, Position{});
    std::pair<float, float> pair_pos = player_pos.getPosition();
    Renderer player_renderer = registry.getComponent(player, Renderer{});
    sf::Sprite player_sprite = player_renderer.getRenderer();

    if (keyPressed) {
        std::string inputType = InputTypeToString(key);
        if (updateClock.getElapsedTime().asSeconds() >= 0.01f) {
            std::string inputType = InputTypeToString(key);
            SendInputUpdate(commandsToServer, registry, inputType);

            // Reset the clock after sending the update
            updateClock.restart();
        }
        //std::cout << "DEBUG: player pos: " << pair_pos.first << " " << pair_pos.second << '\n';
        if (((deltaX != 0 && pair_pos.first >= 0 && pair_pos.first <= windowLimit - spriteLimit) ||
             (deltaY != 0 && pair_pos.second >= 0 && pair_pos.second <= windowLimit - spriteLimit)) &&
            (pair_pos.first != player_sprite.getPosition().x || pair_pos.second != player_sprite.getPosition().y)) {
            UpdateSpritePositionAndPath(player_sprite, pair_pos.first, pair_pos.second, path);
        }
    }
}

void Game::SendInputUpdate(CommandsToServer& commandsToServer, Registry& registry, const std::string& inputType)
{
    std::ostringstream oss;
    Entity player;
    try {
        player = registry.getPlayer();
    } catch (std::exception &e) {
        std::cout << e.what();
        return;
    }
    ID player_id = registry.getComponent(player, ID{});
    oss << inputType << " " << player_id.getID();
    std::string inputString = oss.str();
    commandsToServer.sendToServerAsync(inputString);
}

void Game::shooting(CommandsToServer& commandsToServer, Registry& registry)
{
    Entity player = registry.getPlayer();
    Position playerPos = registry.getComponent(player, Position{});
    std::pair<float, float> pairPos = playerPos.getPosition();
    std::ostringstream shooting;
    shooting << "SHOOT " << pairPos.first << " " << pairPos.second;
    commandsToServer.sendToServerAsync(shooting.str());
}
