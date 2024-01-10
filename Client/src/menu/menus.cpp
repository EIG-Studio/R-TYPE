#include "menu/menus.hpp"

#include "button.hpp"

#include <utility>

//----------Basic Menu----------//
Menu::Menu()
{
    this->onMenu = true;
}

void Menu::setPath(Sprite mSprite)
{
    this->m_menuLogoTexture.loadFromFile(mSprite.getLogoPath());
    this->m_menuLogoSprite.setTexture(this->m_menuLogoTexture);
    this->m_menuTitleTexture.loadFromFile(mSprite.getTitlePath());
    this->m_menuTitleSprite.setTexture(this->m_menuTitleTexture);
    this->m_burnCityFont.loadFromFile(mSprite.getFontPath());

    //// Trouver un moyen pour rendre ça plus beau
    m_menuLogoSprite.setScale(260 / m_menuLogoSprite.getLocalBounds().width, 299 / m_menuLogoSprite.getLocalBounds().height);
    m_menuLogoSprite.setPosition(800 / 2 - 260 / 2, 50);

    m_menuTitleSprite.setScale(395 / m_menuTitleSprite.getLocalBounds().width, 53 / m_menuTitleSprite.getLocalBounds().height);
    m_menuTitleSprite.setPosition(800 / 2 - 395 / 2, 600 / 1.5 - 53 / 2);

    this->m_burnCityText.setString("Press ENTER to burn the city");
    this->m_burnCityText.setFont(this->m_burnCityFont);
    this->m_burnCityText.setCharacterSize(30);
    this->m_burnCityText.setFillColor(sf::Color::White);
    this->m_burnCityText.setPosition(
        800 / 2 - this->m_burnCityText.getGlobalBounds().width / 2,
        600 / 1.2 - this->m_burnCityText.getGlobalBounds().height / 2);
}

sf::Clock Menu::blinkingText(sf::Clock mClock, sf::Time mElapsed)
{
    if (mElapsed.asMilliseconds() > 500) {
        this->m_burnCityText.setFillColor(
            this->m_burnCityText.getFillColor() == sf::Color::Transparent ? sf::Color::White : sf::Color::Transparent);
        mClock.restart();
    }
    return mClock;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_menuLogoTexture;
    states.texture = &m_menuTitleTexture;
    target.draw(m_menuLogoSprite, states);
    target.draw(m_menuTitleSprite, states);
    target.draw(m_burnCityText, states);
}

//----------Choise Menu----------//
ChoiceMenu::ChoiceMenu()
{
    this->onChoice = false;
    m_tempMouseX = 0;
    m_tempMouseY = 0;
}

void ChoiceMenu::setPath(Sprite mSprite)
{
    this->m_logoSamuraiTexture.loadFromFile(mSprite.getLogoPath());
    this->m_logoSamuraiSprite.setTexture(this->m_logoSamuraiTexture);
    this->m_cursorTexture.loadFromFile(mSprite.getCursorPath());
    this->m_cursorSprite.setTexture(this->m_cursorTexture);

    this->m_mainMenuFont.loadFromFile(mSprite.getFontPath());

    //// Trouver un moyen pour rendre ça plus beau
    m_logoSamuraiSprite
        .setScale(87 / m_logoSamuraiSprite.getLocalBounds().width, 100 / m_logoSamuraiSprite.getLocalBounds().height);
    m_cursorSprite.setScale(32 / m_cursorSprite.getLocalBounds().width, 32 / m_cursorSprite.getLocalBounds().height);
    m_logoSamuraiSprite.setPosition(20, 20);
    m_cursorSprite.setPosition(0, 0);

    this->m_mainMenuText.setString("MAIN MENU");
    this->m_mainMenuText.setFont(this->m_mainMenuFont);
    this->m_mainMenuText.setCharacterSize(30);
    this->m_mainMenuText.setFillColor(sf::Color::White);
    this->m_mainMenuText.setPosition(
        800 / 2 - this->m_mainMenuText.getGlobalBounds().width / 2,
        600 / 4 - this->m_mainMenuText.getGlobalBounds().height / 2);
}

void ChoiceMenu::setCursorPosition(sf::RenderWindow& window)
{
    if (sf::Mouse::getPosition(window).x != this->m_tempMouseX && sf::Mouse::getPosition(window).y != this->m_tempMouseY) {
        this->m_cursorSprite.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        this->m_tempMouseX = sf::Mouse::getPosition(window).x;
        this->m_tempMouseY = sf::Mouse::getPosition(window).y;
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -20) {
        if (this->m_cursorSprite.getPosition().y > 0) {
            this->m_cursorSprite.move(0, -5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 20) {
        if (this->m_cursorSprite.getPosition().x < 800 - 32) {
            this->m_cursorSprite.move(5, 0);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 20) {
        if (this->m_cursorSprite.getPosition().y < 600 - 32) {
            this->m_cursorSprite.move(0, 5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -20) {
        if (this->m_cursorSprite.getPosition().x > 0) {
            this->m_cursorSprite.move(-5, 0);
        }
    }
}

float ChoiceMenu::getCursorPosX()
{
    return this->m_cursorSprite.getPosition().x;
}

float ChoiceMenu::getCursorPosY()
{
    return this->m_cursorSprite.getPosition().y;
}


void ChoiceMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_logoSamuraiTexture;
    states.texture = &m_cursorTexture;
    target.draw(m_logoSamuraiSprite, states);
    target.draw(m_mainMenuText, states);
    target.draw(m_cursorSprite, states);
}

//----------Setting Menu----------//
SettingMenu::SettingMenu()
{
    onSetting = false;
    m_tempMouseX = 0;
    m_tempMouseY = 0;
}

void SettingMenu::setPath(Sprite mSprite)
{
    this->m_logoSamuraiTexture.loadFromFile(mSprite.getLogoPath());
    this->m_logoSamuraiSprite.setTexture(this->m_logoSamuraiTexture);
    this->m_cursorTexture.loadFromFile(mSprite.getCursorPath());
    this->m_cursorSprite.setTexture(this->m_cursorTexture);

    //// Trouver un moyen pour rendre ça plus beau
    m_logoSamuraiSprite
        .setScale(87 / m_logoSamuraiSprite.getLocalBounds().width, 100 / m_logoSamuraiSprite.getLocalBounds().height);
    m_cursorSprite.setScale(32 / m_cursorSprite.getLocalBounds().width, 32 / m_cursorSprite.getLocalBounds().height);
    m_logoSamuraiSprite.setPosition(20, 20);
    m_cursorSprite.setPosition(0, 0);
}

void SettingMenu::setCursorPosition(sf::RenderWindow& window)
{
    if (sf::Mouse::getPosition(window).x != this->m_tempMouseX && sf::Mouse::getPosition(window).y != this->m_tempMouseY) {
        this->m_cursorSprite.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        this->m_tempMouseX = sf::Mouse::getPosition(window).x;
        this->m_tempMouseY = sf::Mouse::getPosition(window).y;
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -20) {
        if (this->m_cursorSprite.getPosition().y > 0) {
            this->m_cursorSprite.move(0, -5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 20) {
        if (this->m_cursorSprite.getPosition().x < 800 - 32) {
            this->m_cursorSprite.move(5, 0);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 20) {
        if (this->m_cursorSprite.getPosition().y < 600 - 32) {
            this->m_cursorSprite.move(0, 5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -20) {
        if (this->m_cursorSprite.getPosition().x > 0) {
            this->m_cursorSprite.move(-5, 0);
        }
    }
}

float SettingMenu::getCursorPosX()
{
    return this->m_cursorSprite.getPosition().x;
}

float SettingMenu::getCursorPosY()
{
    return this->m_cursorSprite.getPosition().y;
}

void SettingMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_logoSamuraiTexture;
    states.texture = &m_cursorTexture;
    target.draw(m_logoSamuraiSprite, states);
    target.draw(m_cursorSprite, states);
}

//----------Host Or Join Menu----------//
HostOrJoinMenu::HostOrJoinMenu()
{
    onHostOrJoin = false;
    m_tempMouseX = 0;
    m_tempMouseY = 0;
}

void HostOrJoinMenu::setPath(Sprite mSprite)
{
    this->m_logoSamuraiTexture.loadFromFile(mSprite.getLogoPath());
    this->m_logoSamuraiSprite.setTexture(this->m_logoSamuraiTexture);
    this->m_cursorTexture.loadFromFile(mSprite.getCursorPath());
    this->m_cursorSprite.setTexture(this->m_cursorTexture);

    //// Trouver un moyen pour rendre ça plus beau
    m_logoSamuraiSprite
        .setScale(87 / m_logoSamuraiSprite.getLocalBounds().width, 100 / m_logoSamuraiSprite.getLocalBounds().height);
    m_cursorSprite.setScale(32 / m_cursorSprite.getLocalBounds().width, 32 / m_cursorSprite.getLocalBounds().height);
    m_logoSamuraiSprite.setPosition(20, 20);
    m_cursorSprite.setPosition(0, 0);
}

void HostOrJoinMenu::setCursorPosition(sf::RenderWindow& window)
{
    if (sf::Mouse::getPosition(window).x != this->m_tempMouseX && sf::Mouse::getPosition(window).y != this->m_tempMouseY) {
        this->m_cursorSprite.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        this->m_tempMouseX = sf::Mouse::getPosition(window).x;
        this->m_tempMouseY = sf::Mouse::getPosition(window).y;
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -20) {
        if (this->m_cursorSprite.getPosition().y > 0) {
            this->m_cursorSprite.move(0, -5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 20) {
        if (this->m_cursorSprite.getPosition().x < 800 - 32) {
            this->m_cursorSprite.move(5, 0);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 20) {
        if (this->m_cursorSprite.getPosition().y < 600 - 32) {
            this->m_cursorSprite.move(0, 5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -20) {
        if (this->m_cursorSprite.getPosition().x > 0) {
            this->m_cursorSprite.move(-5, 0);
        }
    }
}

#include <iostream>
void HostOrJoinMenu::inputText(sf::Event& event, IpAdress& ipAdress)
{
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 48 && event.text.unicode <= 57 || event.text.unicode == 46 || event.text.unicode == 8) {
            if (this->m_userInput.length() < 15 || event.text.unicode == 8) {
                if (event.text.unicode < 128 && event.text.unicode != 8 && this->m_userInput.length() < 15) {
                    this->m_userInput += static_cast<char>(event.text.unicode);
                    this->m_inputText.setString(this->m_userInput);
                } else if (event.text.unicode == 8 && !this->m_userInput.empty()) {
                    this->m_userInput.pop_back();
                    this->m_inputText.setString(this->m_userInput);
                }
                ipAdress.setUserInput(this->m_userInput);
            }
        }
    }
}


void HostOrJoinMenu::setInputText(sf::Text text)
{
    this->m_inputText = std::move(text);
}

sf::Text HostOrJoinMenu::getInputText()
{
    return this->m_inputText;
}

std::string HostOrJoinMenu::getUserInput()
{
    return this->m_userInput;
}

float HostOrJoinMenu::getCursorPosX()
{
    return this->m_cursorSprite.getPosition().x;
}

float HostOrJoinMenu::getCursorPosY()
{
    return this->m_cursorSprite.getPosition().y;
}

void HostOrJoinMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_logoSamuraiTexture;
    states.texture = &m_cursorTexture;
    target.draw(m_logoSamuraiSprite, states);
    target.draw(m_cursorSprite, states);
}

//----------Lobby Menu----------//
LobbyMenu::LobbyMenu()
{
    onLobby = false;
    m_tempMouseX = 0;
    m_tempMouseY = 0;
}

void LobbyMenu::setPath(Sprite mSprite)
{
    this->m_logoSamuraiTexture.loadFromFile(mSprite.getLogoPath());
    this->m_logoSamuraiSprite.setTexture(this->m_logoSamuraiTexture);
    this->m_cursorTexture.loadFromFile(mSprite.getCursorPath());
    this->m_cursorSprite.setTexture(this->m_cursorTexture);

    m_logoSamuraiSprite
        .setScale(87 / m_logoSamuraiSprite.getLocalBounds().width, 100 / m_logoSamuraiSprite.getLocalBounds().height);
    m_cursorSprite.setScale(32 / m_cursorSprite.getLocalBounds().width, 32 / m_cursorSprite.getLocalBounds().height);
    m_logoSamuraiSprite.setPosition(20, 20);
    m_cursorSprite.setPosition(0, 0);
}

void LobbyMenu::setCursorPosition(sf::RenderWindow& window)
{
    if (sf::Mouse::getPosition(window).x != this->m_tempMouseX && sf::Mouse::getPosition(window).y != this->m_tempMouseY) {
        this->m_cursorSprite.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        this->m_tempMouseX = sf::Mouse::getPosition(window).x;
        this->m_tempMouseY = sf::Mouse::getPosition(window).y;
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -20) {
        if (this->m_cursorSprite.getPosition().y > 0) {
            this->m_cursorSprite.move(0, -5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 20) {
        if (this->m_cursorSprite.getPosition().x < 800 - 32) {
            this->m_cursorSprite.move(5, 0);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 20) {
        if (this->m_cursorSprite.getPosition().y < 600 - 32) {
            this->m_cursorSprite.move(0, 5);
        }
    }
    if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -20) {
        if (this->m_cursorSprite.getPosition().x > 0) {
            this->m_cursorSprite.move(-5, 0);
        }
    }
}

float LobbyMenu::getCursorPosX()
{
    return this->m_cursorSprite.getPosition().x;
}

float LobbyMenu::getCursorPosY()
{
    return this->m_cursorSprite.getPosition().y;
}

void LobbyMenu::setIpAdress(sf::Text mIpAdress)
{
    this->m_ipAddressText = std::move(mIpAdress);
}

sf::Text LobbyMenu::getIpAdress()
{
    return this->m_ipAddressText;
}

void LobbyMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_logoSamuraiTexture;
    states.texture = &m_cursorTexture;
    target.draw(m_logoSamuraiSprite, states);
    target.draw(m_cursorSprite, states);
}
