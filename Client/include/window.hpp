/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** window
*/


#pragma once

#include "SFML/Graphics/Image.hpp"
#include "button.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

class WindowManager
{
public:
    WindowManager() = default;
    ~WindowManager() = default;
    int initWindow();

    sf::Font& getFont();
    sf::Image& getIcon();
    sf::RenderWindow& getWindow();
    float getMovementSpeed() const;
    float getMillisecondsPerSecond() const;
    // float getMaxFPS() const;
    float getMillisecondsPerFrame() const;


private:
    float m_movementSpeed;
    float m_millisecondsPerSecond;
    float m_maxFPS;
    float m_millisecondsPerFrame;
    std::unique_ptr<sf::RenderWindow> m_window;
    ;
    sf::Font m_font;
    sf::Image m_icon;
};
