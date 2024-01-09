/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** button
*/

#include "button.hpp"

Button::Button(
    const sf::Vector2f& size,
    const sf::Vector2f& position,
    const sf::Color& fillColor,
    const sf::Color& outlineColor,
    float outlineThickness,
    const std::string& text,
    const sf::Font& font,
    unsigned characterSize) :
m_shape(size),
m_font(font)
{
    m_shape.setPosition(position);
    m_shape.setFillColor(fillColor);
    m_shape.setOutlineColor(outlineColor);
    m_shape.setOutlineThickness(outlineThickness);

    m_label.setFont(font);
    m_label.setString(text);
    m_label.setCharacterSize(characterSize);
    m_label.setFillColor(outlineColor);
    m_label.setPosition(
        position.x + (size.x - m_label.getLocalBounds().width) / 2,
        position.y + (size.y - m_label.getLocalBounds().height) / 2);
}


bool Button::checkClick(float cursorX, float cursorY)
{
    bool clicked = m_shape.getGlobalBounds().contains(cursorX, cursorY) &&
                   (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 0));


    if (clicked && !m_isClicked) {
        m_isClicked = true;
        return true;
    } else if (!clicked) {
        m_isClicked = false;
    }

    return false;
}

bool Button::checkHover(float cursorX, float cursorY)
{
    bool hover = m_shape.getGlobalBounds().contains(cursorX, cursorY);

    if (hover) {
        m_shape.setOutlineColor(sf::Color::Red);
    } else if (!hover) {
        m_shape.setOutlineColor(sf::Color::White);
    }
    return false;
}

void Button::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
    window.draw(m_label);
}
