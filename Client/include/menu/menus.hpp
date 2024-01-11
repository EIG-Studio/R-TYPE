/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** menus
*/

#pragma once

#include "sprite/sprite.hpp"
#include "ipAdress.hpp"

class Menu : public sf::Drawable, public sf::Transformable
{
public:
    Menu();
    ~Menu() override = default;
    sf::Clock blinkingText(sf::Clock mClock, sf::Time mElapsed);
    void setPath(Sprite mSprite);
    bool onMenu;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_menuLogoTexture;
    sf::Texture m_menuTitleTexture;
    sf::Sprite m_menuLogoSprite;
    sf::Sprite m_menuTitleSprite;
    sf::Font m_burnCityFont;
    sf::Text m_burnCityText;
};

class ChoiceMenu : public sf::Drawable, public sf::Transformable
{
public:
    ChoiceMenu();
    ~ChoiceMenu() override = default;
    void setPath(Sprite mSprite);
    void setCursorPosition(sf::RenderWindow& window);
    float getCursorPosX();
    float getCursorPosY();
    bool onChoice;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_logoSamuraiTexture;
    sf::Sprite m_logoSamuraiSprite;
    sf::Texture m_cursorTexture;
    sf::Sprite m_cursorSprite;
    sf::Font m_mainMenuFont;
    sf::Text m_mainMenuText;
    int m_tempMouseX;
    int m_tempMouseY;
};

class SettingMenu : public sf::Drawable, public sf::Transformable
{
public:
    SettingMenu();
    ~SettingMenu() override = default;
    void setPath(Sprite mSprite);
    void setCursorPosition(sf::RenderWindow& window);
    float getCursorPosX();
    float getCursorPosY();
    bool onSetting;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_logoSamuraiTexture;
    sf::Sprite m_logoSamuraiSprite;
    sf::Texture m_cursorTexture;
    sf::Sprite m_cursorSprite;
    int m_tempMouseX;
    int m_tempMouseY;
};

class HostOrJoinMenu : public sf::Drawable, public sf::Transformable
{
public:
    HostOrJoinMenu();
    ~HostOrJoinMenu() override = default;
    void setPath(Sprite mSprite);
    void setCursorPosition(sf::RenderWindow& window);
    float getCursorPosX();
    float getCursorPosY();
    void setInputText(sf::Text text);
    sf::Text getInputText();
    void inputText(sf::Event& event, IpAdress& ipAdress);
<<<<<<< HEAD
    void setInputTextFromString(std::string text);
    std::string getUserInput();
    void setUserInput(std::string userInput);
=======
    std::string getUserInput();
>>>>>>> refs/remotes/origin/Client
    bool onHostOrJoin;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_logoSamuraiTexture;
    sf::Sprite m_logoSamuraiSprite;
    sf::Texture m_cursorTexture;
    sf::Sprite m_cursorSprite;
    sf::Text m_inputText;
    std::string m_userInput;
    int m_tempMouseX;
    int m_tempMouseY;
};

class LobbyMenu : public sf::Drawable, public sf::Transformable
{
public:
    LobbyMenu();
    ~LobbyMenu() override = default;
    void setPath(Sprite mSprite);
    void setCursorPosition(sf::RenderWindow& window);
    float getCursorPosX();
    float getCursorPosY();
    void setIpAdress(sf::Text mIpAdress);
    sf::Text getIpAdress();
    bool onLobby;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_logoSamuraiTexture;
    sf::Sprite m_logoSamuraiSprite;
    sf::Texture m_cursorTexture;
    sf::Sprite m_cursorSprite;
    int m_tempMouseX;
    int m_tempMouseY;

    sf::Text m_ipAddressText;
};
