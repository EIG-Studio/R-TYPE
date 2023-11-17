/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** inGame
*/

#pragma once

#include "sfml.hpp"
#include "sprite/sprite.hpp"
#include "define.hpp"

class Game : public sf::Drawable, public sf::Transformable
{
public:
    Game();
    ~Game() override = default;
    bool onGame;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
