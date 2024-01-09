/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** button
*/

//#include "window.hpp"
//
//#include <SFML/Graphics.hpp>
//
//#include <iostream>
//
//class Button
//{
//public:
//    Button();
//    Button(
//        sf::RenderWindow& window,
//        const sf::Vector2f& size,
//        const sf::Vector2f& position,
//        const sf::Color& fillColor,
//        const sf::Color& outlineColor,
//        float outlineThickness,
//        const std::string& textString,
//        const sf::Font& font,
//        unsigned int characterSize) :
//    m_window(window),
//    m_text(textString, font, characterSize)
//    {
//        m_button.setSize(size);
//        m_button.setPosition(position);
//        m_button.setFillColor(fillColor);
//
//        m_button.setOutlineColor(outlineColor);
//        m_button.setOutlineThickness(outlineThickness);
//
//        sf::FloatRect textBounds = m_text.getLocalBounds();
//        m_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
//        m_text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
//    }
//
//    bool checkClick(float cursorX, float cursorY)
//    {
//        bool clicked = m_button.getGlobalBounds().contains(cursorX, cursorY) &&
//                       (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Joystick::isButtonPressed(0, 0));
//
//
//        if (clicked && !m_isClicked) {
//            m_isClicked = true;
//            return true;
//        } else if (!clicked) {
//            m_isClicked = false;
//        }
//
//        return false;
//    }
//
//    bool checkHover(float cursorX, float cursorY)
//    {
//        bool hover = m_button.getGlobalBounds().contains(cursorX, cursorY);
//
//        if (hover) {
//            m_button.setOutlineColor(sf::Color::Red);
//        } else if (!hover) {
//            m_button.setOutlineColor(sf::Color::White);
//        }
//        return false;
//    }
//
//    void draw()
//    {
//        m_window.draw(m_button);
//        m_window.draw(m_text);
//    }
//
//    void initButton(WindowManager& windowManager);
//    Button getPlayButton() const;
//    Button getSettingsButton() const;
//    Button getExitButton() const;
//    Button getRetourButton() const;
//
//
//private:
//    sf::RectangleShape m_button;
//    sf::RenderWindow& m_window;
//    sf::Text m_text;
//    bool m_isClicked{false};
//    bool m_isHover{};
//};


#include <SFML/Graphics.hpp>

#include <string>

class Button
{
public:
    Button() = default;
    Button(
        sf::RenderWindow& window,
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

    bool checkClick(float cursorX, float cursorY)
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

    bool checkHover(float cursorX, float cursorY)
    {
        bool hover = m_shape.getGlobalBounds().contains(cursorX, cursorY);

        if (hover) {
            m_shape.setOutlineColor(sf::Color::Red);
        } else if (!hover) {
            m_shape.setOutlineColor(sf::Color::White);
        }
        return false;
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(m_shape);
        window.draw(m_label);
    }

    // Ajoutez d'autres méthodes ou membres au besoin

private:
    sf::RectangleShape m_shape;
    sf::Text m_label;
    sf::Font m_font;
    bool m_isClicked{false};
};

class ButtonManager
{
public:
    ButtonManager(sf::RenderWindow& window, const sf::Font& mFont) :
    m_window(window),
    m_font(mFont),
    m_playButton(
        window,
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 - 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Play",
        m_font,
        20),
    m_settingsButton(
        window,
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Settings",
        m_font,
        20),
    m_retourButton(
        window,
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 + 150, window.getSize().y / 2 + 200),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Retour",
        m_font,
        20),
    m_exitButton(
        window,
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Exit",
        m_font,
        20)
    {
        // ... Autres initialisations si nécessaire
    }

    Button& getPlayButton()
    {
        return m_playButton;
    }
    Button& getSettingsButton()
    {
        return m_settingsButton;
    }
    Button& getRetourButton()
    {
        return m_retourButton;
    }
    Button& getExitButton()
    {
        return m_exitButton;
    }

    // Ajoutez d'autres méthodes ou membres au besoin

private:
    void createButtons()
    {
        m_playButton = Button(
            m_window,
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 - 60),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Play",
            m_font,
            20);

        m_settingsButton = Button(
            m_window,
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Settings",
            m_font,
            20);

        m_retourButton = Button(
            m_window,
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 + 150, m_window.getSize().y / 2 + 200),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Retour",
            m_font,
            20);

        m_exitButton = Button(
            m_window,
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 + 60),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Exit",
            m_font,
            20);
    }

    sf::RenderWindow& m_window;
    sf::Font m_font;
    Button m_playButton;
    Button m_settingsButton;
    Button m_retourButton;
    Button m_exitButton;
};