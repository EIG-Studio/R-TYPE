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

    if (m_shape.getGlobalBounds().contains(cursorX, cursorY) &&
        (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 0)))
        this->m_isClicked = true;

    if (!clicked && m_isClicked) {
        m_isClicked = false;
        return true;
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

void Button::setText(const std::string& text)
{
    m_label.setString(text);
}

void Button::setPosition(const sf::Vector2f& position)
{
    m_shape.setPosition(position);
    m_label.setPosition(
        m_shape.getPosition().x + (m_shape.getSize().x - m_label.getLocalBounds().width) / 2,
        m_shape.getPosition().y + (m_shape.getSize().y - m_label.getLocalBounds().height) / 2);
}

void Button::setSize(const sf::Vector2f& size)
{
    m_shape.setSize(size);
    m_label.setPosition(
        m_shape.getPosition().x + (m_shape.getSize().x - m_label.getLocalBounds().width) / 2,
        m_shape.getPosition().y + (m_shape.getSize().y - m_label.getLocalBounds().height) / 2);
}

void Button::setOutlineColor(const sf::Color& color)
{
    m_shape.setOutlineColor(color);
}

sf::Color Button::getOutlineColor()
{
    return m_shape.getOutlineColor();
}
