/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** button
*/

#include <SFML/Graphics.hpp>

#include <string>

class Button
{
public:
    Button() = default;
    Button(
        sf::RenderWindow& /*window*/,
        const sf::Vector2f& size,
        const sf::Vector2f& position,
        const sf::Color& fillColor,
        const sf::Color& outlineColor,
        float outlineThickness,
        const std::string& text,
        const sf::Font& font,
        unsigned characterSize);

    bool checkClick(float cursorX, float cursorY);
    bool checkHover(float cursorX, float cursorY);
    void draw(sf::RenderWindow& window) const;

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
