/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** button
*/

#include "button.hpp"

void Button::initButton(WindowManager& windowManager)
{
    Button playButton(
        windowManager.getWindow(),
        sf::Vector2f(200, 50),
        sf::Vector2f(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 2 - 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Play",
        windowManager.getFont(),
        20);

    Button settingsButton(
        windowManager.getWindow(),
        sf::Vector2f(200, 50),
        sf::Vector2f(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 2),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Settings",
        windowManager.getFont(),
        20);

    Button retourButton(
        windowManager.getWindow(),
        sf::Vector2f(200, 50),
        sf::Vector2f(windowManager.getWindow().getSize().x / 2 + 150, windowManager.getWindow().getSize().y / 2 + 200),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Retour",
        windowManager.getFont(),
        20);

    Button exitButton(
        windowManager.getWindow(),
        sf::Vector2f(200, 50),
        sf::Vector2f(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 2 + 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Exit",
        windowManager.getFont(),
        20);
}
