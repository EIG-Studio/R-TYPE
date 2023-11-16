/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** menu
*/

#pragma once

#include "SFML.hpp"

#define PATH_TEXTURE_MENU_LOGO "assets/MainMenu/samuraiLogo.png"
#define PATH_TEXTURE_MENU_TITLE "assets/MainMenu/SamuraiTitle.png"
#define PATH_FONT_MENU "nothing"
#define MOUSECLICKED event.type == sf::Event::MouseButtonPressed

class Menu : public sf::Drawable, public sf::Transformable
{
public:
    Menu();
    ~Menu() = default;
    //sf::FloatRect getSettings();
    //sf::FloatRect getExit();
    bool onMenu;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Texture menuLogoTexture;
    sf::Texture menuTitleTexture;
    sf::Sprite  menuLogoSprite;
    sf::Sprite  menuTitleSprite;
};
