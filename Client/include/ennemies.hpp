/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ennemies
*/

#pragma once

#include "sprite/sprite.hpp"

#include <iostream>

class Ennemies : public sf::Drawable, public sf::Transformable
{
public:
    Ennemies() = default;
    ~Ennemies() override = default;

    void setPath();
    float getPosEnnemyY();
    float getPosEnnemyX();
    void destroyEnnemy(float playerPosX, float ennemyPosX);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_ennemyTexture;
    sf::Sprite m_ennemySprite;
};
