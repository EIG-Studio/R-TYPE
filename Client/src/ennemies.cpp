/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ennemies
*/

#include "ennemies.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

const float SPRITE_HEIGHT = 60.0f;

Ennemies::Ennemies()
{
    this->m_moveSpeed = 0.2;
};

void Ennemies::setPath()
{
    this->m_ennemyTexture.loadFromFile("../Client/assets/Cars/cars/190.png");
    this->m_ennemySprite.setTexture(this->m_ennemyTexture);

    m_ennemySprite.setScale(104.25 / m_ennemySprite.getLocalBounds().width, 38.5 / m_ennemySprite.getLocalBounds().height);
    m_ennemySprite.setPosition(300, 300);
}

float Ennemies::getPosEnnemyY()
{
    return this->m_ennemySprite.getPosition().y;
}

float Ennemies::getPosEnnemyX()
{
    return this->m_ennemySprite.getPosition().x;
}

void Ennemies::destroyEnnemy(float playerPosY, float ennemyPosY)
{
    std::cout << "PLAYER POS: " << playerPosY << std::endl;
    std::cout << "ENNEMY POS: " << ennemyPosY << std::endl;
    if (playerPosY <= ennemyPosY + 40 && playerPosY >= ennemyPosY - 15) {
        std::cout << "BOOM !!!!" << std::endl;
    }

    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(10, ennemyPosY + 20)), sf::Vertex(sf::Vector2f(10, ennemyPosY - 30))};
}

void Ennemies::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = &m_ennemyTexture;
    target.draw(m_ennemySprite, states);
}


void Ennemies::moveEnnemy(float movementSpeed, float winX, float winY, CommandsToServer& commandsToServer)
{
    this->HandleMovement(commandsToServer, movementSpeed, winX, movementSpeed, winY, SPRITE_HEIGHT);
}

void updateSpritePosition(sf::Sprite& sprite, float newX, float newY)
{
    sprite.setPosition(newX, newY);
}

void Ennemies::HandleMovement(
    CommandsToServer& commandsToServer,
    float movementSpeed,
    float deltaX,
    float deltaY,
    float windowLimit,
    float spriteLimit)
{

    if (this->m_ennemySprite.getPosition().y >= windowLimit - spriteLimit) {
        this->m_moveSpeed = -0.2;
    } else if (this->m_ennemySprite.getPosition().y == 0) {
        this->m_moveSpeed = 0.2;
    }

    float newX = this->m_ennemySprite.getPosition().x + (0 * movementSpeed);
    float newY = this->m_ennemySprite.getPosition().y + (this->m_moveSpeed * movementSpeed);

    // Boundary check and ensure there's an actual movement
    if (((deltaX != 0 && newX >= 0 && newX <= windowLimit - spriteLimit) ||
         (deltaY != 0 && newY >= 0 && newY <= windowLimit - spriteLimit)) &&
        (newX != this->m_ennemySprite.getPosition().x || newY != this->m_ennemySprite.getPosition().y)) {
        SendPositionUpdate(commandsToServer, newX, newY, movementSpeed);
        updateSpritePosition(this->m_ennemySprite, newX, newY);
    }
    std::cout << "test" << std::endl;
}

void Ennemies::SendPositionUpdate(CommandsToServer& commandsToServer, float x, float y, float speed)
{
    std::ostringstream oss;
    oss << "POS " << x << " " << y << " " << speed << " 1";
    std::string positionString = oss.str();
    commandsToServer.sendToServerAsync(positionString);
}
