/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#include "sprite.hpp"
#include "iostream"

bool Sprite::load(const std::string &sprite, sf::Vector2u tileSize,
    unsigned int width, unsigned int height, int rect_width, int rect_heigth)
{
    if (!m_texture.loadFromFile(sprite))
        return false;
    sf::IntRect rectSprite(0, 0, rect_width, rect_heigth);
    sf::Sprite mm_sprite(m_texture, rectSprite);
    m_sprite = mm_sprite;
    m_sprite.setScale(tileSize.x / m_sprite.getLocalBounds().width, tileSize.y / m_sprite.getLocalBounds().height);
    m_sprite.setPosition(width, height);

    return true;
}

void Sprite::set_rect(int top, int left)
{
    sf::IntRect result(top, left, 25, 29);
    m_sprite.setTextureRect(result);
    return;
}

void Sprite::draw(
    sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_sprite, states);
}