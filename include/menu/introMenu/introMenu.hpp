/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** GUI
*/

#pragma once

#include "sfml.hpp"
#include "sprite/sprite.hpp"

class Menu : public sf::Drawable, public sf::Transformable
{
public:
    Menu();
    ~Menu() override = default;
    sf::Clock blinkingText(sf::Clock  mClock, sf::Time mElapsed);
    void setPath(Sprite mSprite);
    bool onMenu;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_menuLogoTexture;
    sf::Texture m_menuTitleTexture;
    sf::Sprite  m_menuLogoSprite;
    sf::Sprite  m_menuTitleSprite;
    sf::Font m_burnCityFont;
    sf::Text m_burnCityText;
};

class ChoiceMenu : public sf::Drawable, public sf::Transformable
{
public:
    ChoiceMenu();
    ~ChoiceMenu() override = default;
    void setPath(Sprite mSprite);
    bool onChoice;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_logoSamuraiTexture;
    sf::Sprite  m_logoSamuraiSprite;
};
