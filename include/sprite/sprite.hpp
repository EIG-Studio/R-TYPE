/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#pragma once

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
    std::string m_path_logo;
    std::string m_path_title;
    std::string m_path_font;
};
