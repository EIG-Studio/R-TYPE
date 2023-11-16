/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#include "sprite.hpp"
#include "iostream"

bool Sprite::load(const std::string &sprite, sf::Vector2u tileSize,
    unsigned int width, unsigned int height, int rectWidth, int rectHeigth)
{
    if (!m_texture.loadFromFile(sprite))
        return false;
    sf::IntRect rectSprite(0, 0, rectWidth, rectHeigth);
    sf::Sprite mmSprite(m_texture, rectSprite);
    m_sprite = mmSprite;
    m_sprite.setScale(tileSize.x / m_sprite.getLocalBounds().width, tileSize.y / m_sprite.getLocalBounds().height);
    m_sprite.setPosition(width, height);

    return true;
}

void Sprite::setRect(int top, int left)
{
    sf::IntRect result(top, left, 25, 29);
    m_sprite.setTextureRect(result);
}

void Sprite::draw(
    sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_sprite, states);
}
