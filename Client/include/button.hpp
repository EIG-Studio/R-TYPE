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
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 - 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Play",
        m_font,
        20),
    m_settingsButton(
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Settings",
        m_font,
        20),
    m_retourButton(
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 + 150, window.getSize().y / 2 + 200),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Retour",
        m_font,
        20),
    m_exitButton(
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Exit",
        m_font,
        20),
    m_resumeButton(
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 - 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Resume",
        m_font,
        20),
    m_toMenuButton(
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "To Menu",
        m_font,
        20),
    m_hostButton(
        sf::Vector2f(200, 50),
        sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 - 100),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Host",
        m_font,
        20),
    m_joinButton(
        sf::Vector2f(200, 50),
        sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 + 200),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Join",
        m_font,
        20),
    m_startButton(
        sf::Vector2f(200, 50),
        sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 + 200),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Start",
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
    Button& getResumeButton()
    {
        return m_resumeButton;
    }
    Button& getToMenuButton()
    {
        return m_toMenuButton;
    }
    Button& getHostButton()
    {
        return m_hostButton;
    }
    Button& getJoinButton()
    {
        return m_joinButton;
    }
    Button& getStartButton()
    {
        return m_startButton;
    }

private:
    void createButtons()
    {
        m_playButton = Button(
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 - 60),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Play",
            m_font,
            20);

        m_settingsButton = Button(
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Settings",
            m_font,
            20);

        m_retourButton = Button(
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 + 150, m_window.getSize().y / 2 + 200),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Retour",
            m_font,
            20);

        m_exitButton = Button(
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 + 60),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Exit",
            m_font,
            20);

        m_resumeButton = Button(
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 - 60),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Play",
            m_font,
            20);

        m_toMenuButton = Button(
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Settings",
            m_font,
            20);
        m_hostButton = Button(
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 - 100),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Host",
            m_font,
            20);
        m_joinButton = Button(
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Join",
            m_font,
            20);
        m_startButton = Button(
            sf::Vector2f(200, 50),
            sf::Vector2f(m_window.getSize().x / 2 - 100, m_window.getSize().y / 2 + 200),
            sf::Color::Black,
            sf::Color::White,
            2.0f,
            "Start",
            m_font,
            20);
    }

    sf::RenderWindow& m_window;
    sf::Font m_font;
    Button m_playButton;
    Button m_settingsButton;
    Button m_retourButton;
    Button m_exitButton;
    Button m_resumeButton;
    Button m_toMenuButton;
    Button m_hostButton;
    Button m_joinButton;
    Button m_startButton;
};
