/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** settingMenu
*/

#include "menu/settingMenu.hpp"

SettingMenu::SettingMenu()
{
    onSetting = false;
}

void SettingMenu::setPath(Sprite mSprite)
{
    this->m_logoSamuraiTexture.loadFromFile(mSprite.getLogoPath());
    this->m_logoSamuraiSprite.setTexture(this->m_logoSamuraiTexture);
    this->m_cursorTexture.loadFromFile(mSprite.getCursorPath());
    this->m_cursorSprite.setTexture(this->m_cursorTexture);

    //// Trouver un moyen pour rendre ça plus beau
    m_logoSamuraiSprite.setScale(87 / m_logoSamuraiSprite.getLocalBounds().width,
                                 100 / m_logoSamuraiSprite.getLocalBounds().height);
    m_cursorSprite.setScale(32 / m_cursorSprite.getLocalBounds().width, 32 / m_cursorSprite.getLocalBounds().height);
    m_logoSamuraiSprite.setPosition(20, 20);
    m_cursorSprite.setPosition(0, 0);
}

void SettingMenu::setCursorPosition(sf::RenderWindow& window)
{
    if (sf::Mouse::getPosition(window).x != this->m_tempMouseX && sf::Mouse::getPosition(window).y != this->m_tempMouseY)
    {
        this->m_cursorSprite.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        this->m_tempMouseX = sf::Mouse::getPosition(window).x;
        this->m_tempMouseY = sf::Mouse::getPosition(window).y;
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -20)
    {
        if (this->m_cursorSprite.getPosition().y > 0)
        {
            this->m_cursorSprite.move(0, -5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 20)
    {
        if (this->m_cursorSprite.getPosition().x < 800 - 32)
        {
            this->m_cursorSprite.move(5, 0);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 20)
    {
        if (this->m_cursorSprite.getPosition().y < 600 - 32)
        {
            this->m_cursorSprite.move(0, 5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -20)
    {
        if (this->m_cursorSprite.getPosition().x > 0)
        {
            this->m_cursorSprite.move(-5, 0);
        }
    }
}

void SettingMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_logoSamuraiTexture;
    states.texture = &m_cursorTexture;
    target.draw(m_logoSamuraiSprite, states);
    target.draw(m_cursorSprite, states);
}
