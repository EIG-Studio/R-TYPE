/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ennemies
*/

#include "ennemies.hpp"

#include <SFML/Graphics.hpp>


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
