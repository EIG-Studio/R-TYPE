/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#pragma once

#include "SFML.hpp"

class Sprite : public sf::Drawable, public sf::Transformable {
    public:
        bool load(const std::string& sprite, sf::Vector2u tileSize, unsigned int width, unsigned int height, int rectWidth, int rectHeigth);
        void setRect(int top, int left);
    private:
         void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Texture m_texture;
        sf::Sprite m_sprite;
};
