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
        bool load(const std::string& sprite, sf::Vector2u tileSize, unsigned int width, unsigned int height, int rect_width, int rect_heigth);
        void set_rect(int top, int left);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Texture m_texture;
        sf::Sprite m_sprite;
};
