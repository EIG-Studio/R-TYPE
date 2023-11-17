/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** inGame
*/

#pragma once

#include "sfml.hpp"
#include "sprite/sprite.hpp"

class Game : public sf::Drawable, public sf::Transformable
{
public:
    Game();
    ~Game() override = default;
    void setPath(Sprite mSprite);
    bool onGame;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_testTexture;
    sf::Sprite  m_testSprite;

};
