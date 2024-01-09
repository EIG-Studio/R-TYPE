/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** window
*/

#include "window.hpp"

int WindowManager::initWindow()
{
    this->m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "SAMURAI");
    m_window->setMouseCursorVisible(false);
    m_window->setFramerateLimit(144);
    m_window->setVerticalSyncEnabled(true);

    if (!this->m_icon.loadFromFile("../Client/assets/MainMenu/samuraiLogo.png")) {
        return -1;
    }
    m_window->setIcon(this->m_icon.getSize().x, this->m_icon.getSize().y, this->m_icon.getPixelsPtr());

    if (!this->m_font.loadFromFile("../Client/assets/Fonts/retro.ttf")) {
        return -1;
    }
    return 0;
}

sf::Font& WindowManager::getFont()
{
    return this->m_font;
}

sf::Image& WindowManager::getIcon()
{
    return this->m_icon;
}

sf::RenderWindow& WindowManager::getWindow()
{
    return *this->m_window;
}

float WindowManager::getMovementSpeed() const
{
    return this->m_movementSpeed;
}

// float WindowManager::getMillisecondsPerSecond() const
// {
// return this->m_millisecondsPerSecond;
// }

// float WindowManager::getMillisecondsPerFrame() const
// {
// return this->m_millisecondsPerFrame;
// }
