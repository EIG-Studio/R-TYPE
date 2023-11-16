/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** GUI
*/

#pragma once

#include "sfml.hpp"
#include "sprite/sprite.hpp"

#define PATH_TEXTURE_MENU_LOGO  "../assets/MainMenu/samuraiLogo.png"
#define PATH_TEXTURE_MENU_TITLE "../assets/MainMenu/samuraiTitle.png"
#define PATH_FONT_MENU          "nothing"
#define MOUSECLICKED            event.type == sf::Event::MouseButtonPressed

class Menu : public sf::Drawable, public sf::Transformable
{
public:
    Menu();
    ~Menu() override = default;
    //sf::FloatRect getSettings();
    //sf::FloatRect getExit();
    bool onMenu;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_menuLogoTexture;
    sf::Texture m_menuTitleTexture;
    sf::Sprite  m_menuLogoSprite;
    sf::Sprite  m_menuTitleSprite;
};

class ChoiceMenu : public sf::Drawable, public sf::Transformable
{
public:
    ChoiceMenu();
    ~ChoiceMenu() = default;
    bool onChoice;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture logoSamuraiTexture;
    sf::Sprite  logoSamuraiSprite;
};
