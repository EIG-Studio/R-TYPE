/*
** EPITECH PROJECT, 2023
** Client
** File description:
** movements
*/

#include "menu/inGame.hpp"

#include <sstream>

const float JOYSTICK_THRESHOLD = 20.0f;
const float SPRITE_WIDTH = 103.0f;
const float SPRITE_HEIGHT = 37.75f;


void UpdateSpriteTexture(sf::Sprite& sprite, const std::string& texturePath) {
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

void UpdateSpritePositionAndPath(sf::Sprite& sprite, float newX, float newY, const std::string& texturePath) {
    sprite.setPosition(newX, newY);

    UpdateSpriteTexture(sprite, texturePath);
}

void Game::movePlayer(float movementSpeed, float winX, float winY, CommandsToServer& commandsToServer, Sprite mSprite) {
    float initialPosX = this->m_playerSprite.getPosition().x;
    float initialPosY = this->m_playerSprite.getPosition().y;

    // Handle all movement directions
    HandleMovement(sf::Keyboard::Up, sf::Joystick::Y, commandsToServer, movementSpeed, -JOYSTICK_THRESHOLD, 0, -movementSpeed, "../Client/assets/Cars/189_toUp.png", winY, SPRITE_HEIGHT);
    HandleMovement(sf::Keyboard::Right, sf::Joystick::X, commandsToServer, movementSpeed, JOYSTICK_THRESHOLD, movementSpeed, 0, "../Client/assets/Cars/189_toRight.png", winX, SPRITE_WIDTH);
    HandleMovement(sf::Keyboard::Down, sf::Joystick::Y, commandsToServer, movementSpeed, JOYSTICK_THRESHOLD, 0, movementSpeed, "../Client/assets/Cars/189_toDown.png", winY, SPRITE_HEIGHT);
    HandleMovement(sf::Keyboard::Left, sf::Joystick::X, commandsToServer, movementSpeed, -JOYSTICK_THRESHOLD, -movementSpeed, 0, "../Client/assets/Cars/189_toLeft.png", winX, SPRITE_WIDTH);

    // Check for no input
    if (initialPosX == this->m_playerSprite.getPosition().x && initialPosY == this->m_playerSprite.getPosition().y) {
        // Reset to neutral state
        UpdateSpriteTexture(this->m_playerSprite, "../Client/assets/Cars/189_neutral.png");
    }
}


void Game::HandleMovement(sf::Keyboard::Key key, sf::Joystick::Axis axis, CommandsToServer& commandsToServer, float movementSpeed,
                          float joystickThreshold, float deltaX, float deltaY, const std::string& path, float windowLimit, float spriteLimit) {
    bool keyPressed = sf::Keyboard::isKeyPressed(key);
    float axisPosition = sf::Joystick::getAxisPosition(0, axis);
    bool joystickMoved = (deltaX != 0 && (axis == sf::Joystick::X && std::abs(axisPosition) > joystickThreshold)) ||
                         (deltaY != 0 && (axis == sf::Joystick::Y && std::abs(axisPosition) > joystickThreshold));

    if (keyPressed || joystickMoved) {
        float newX = this->m_playerSprite.getPosition().x + (keyPressed ? deltaX : (axisPosition / 100) * movementSpeed);
        float newY = this->m_playerSprite.getPosition().y + (keyPressed ? deltaY : (axisPosition / 100) * movementSpeed);

        // Boundary check and ensure there's an actual movement
        if (((deltaX != 0 && newX >= 0 && newX <= windowLimit - spriteLimit) || 
            (deltaY != 0 && newY >= 0 && newY <= windowLimit - spriteLimit)) &&
            (newX != this->m_playerSprite.getPosition().x || newY != this->m_playerSprite.getPosition().y)) {
            SendPositionUpdate(commandsToServer, newX, newY, movementSpeed);
            UpdateSpritePositionAndPath(this->m_playerSprite, newX, newY, path);
        }
    }
}



void Game::SendPositionUpdate(CommandsToServer& commandsToServer, float x, float y, float speed) {
    std::ostringstream oss;
    oss << "POS " << x << " " << y << " " << speed << " 1";
    std::string positionString = oss.str();
    commandsToServer.sendToServerAsync(positionString);
}
