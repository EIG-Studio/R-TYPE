/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** settingMenu
*/

#pragma once

#include "sprite/sprite.hpp"

class SettingMenu : public sf::Drawable, public sf::Transformable
{
public:
    SettingMenu();
    ~SettingMenu() override = default;
    void setPath(Sprite mSprite);
    void setCursorPosition(sf::RenderWindow& window);
    bool onSetting;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_logoSamuraiTexture;
    sf::Sprite  m_logoSamuraiSprite;
    sf::Texture m_cursorTexture;
    sf::Sprite  m_cursorSprite;
    int         m_tempMouseX;
    int         m_tempMouseY;
};
