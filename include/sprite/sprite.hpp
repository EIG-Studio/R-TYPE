/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include <string>
#define PATH_TEXTURE_MENU_LOGO  "../assets/MainMenu/samuraiLogo.png"
#define PATH_TEXTURE_MENU_TITLE "../assets/MainMenu/samuraiTitle.png"
#define PATH_FONT_MENU          "../assets/Fonts/retro.ttf"
#define MOUSECLICKED            event.type == sf::Event::MouseButtonPressed

class Sprite : public sf::Drawable, public sf::Transformable
{
public:
    Sprite();
    ~Sprite() override = default;

private:
    std::string m_pathLogo;
    std::string m_pathTitle;
    std::string m_pathFont;
};
