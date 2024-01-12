/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** inGame
*/

#include "menu/inGame.hpp"

#include <iostream>
#include <sstream>
#include <utility>

Game::Game()
{
    this->onGame = false;
    this->onPause = false;
    this->m_tempMouseX = 0;
    this->m_tempMouseY = 0;
    this->m_healthPointTemp = 0;
}

void Game::setPath(Sprite mSprite)
{
    this->m_backTexture.loadFromFile(mSprite.getBackPath());
    this->m_backSprite.setTexture(this->m_backTexture);
    this->m_backTexture2.loadFromFile(mSprite.getBackPath());
    this->m_backSprite2.setTexture(this->m_backTexture2);

    this->m_veryBackBuildTexture.loadFromFile(mSprite.getVeryBackBuildPath());
    this->m_veryBackBuildSprite.setTexture(this->m_veryBackBuildTexture);
    this->m_veryBackBuildTexture2.loadFromFile(mSprite.getVeryBackBuildPath());
    this->m_veryBackBuildSprite2.setTexture(this->m_veryBackBuildTexture2);

    this->m_backBuildTexture.loadFromFile(mSprite.getBackBuildPath());
    this->m_backBuildSprite.setTexture(this->m_backBuildTexture);
    this->m_backBuildTexture2.loadFromFile(mSprite.getBackBuildPath());
    this->m_backBuildSprite2.setTexture(this->m_backBuildTexture2);

    this->m_midBuildTexture.loadFromFile(mSprite.getMidBuildPath());
    this->m_midBuildSprite.setTexture(this->m_midBuildTexture);
    this->m_midBuildTexture2.loadFromFile(mSprite.getMidBuildPath());
    this->m_midBuildSprite2.setTexture(this->m_midBuildTexture2);

    this->m_frontBuildTexture.loadFromFile(mSprite.getFrontBuildPath());
    this->m_frontBuildSprite.setTexture(this->m_frontBuildTexture);
    this->m_frontBuildTexture2.loadFromFile(mSprite.getFrontBuildPath());
    this->m_frontBuildSprite2.setTexture(this->m_frontBuildTexture2);

    this->m_cursorTexture.loadFromFile(mSprite.getCursorPath());
    this->m_cursorSprite.setTexture(this->m_cursorTexture);

    m_backSprite.setScale(1152 / m_backSprite.getLocalBounds().width, 648 / m_backSprite.getLocalBounds().height);
    m_backSprite.setPosition(0, 0);
    m_backSprite2.setScale(1152 / m_backSprite2.getLocalBounds().width, 648 / m_backSprite2.getLocalBounds().height);
    m_backSprite2.setPosition(m_backSprite2.getLocalBounds().width * 2, 0);

    m_veryBackBuildSprite
        .setScale(1152 / m_veryBackBuildSprite.getLocalBounds().width, 648 / m_veryBackBuildSprite.getLocalBounds().height);
    m_veryBackBuildSprite.setPosition(0, 0);
    m_veryBackBuildSprite2
        .setScale(1152 / m_veryBackBuildSprite2.getLocalBounds().width, 648 / m_veryBackBuildSprite2.getLocalBounds().height);
    m_veryBackBuildSprite2.setPosition(m_veryBackBuildSprite2.getLocalBounds().width * 2, 0);

    m_backBuildSprite.setScale(1152 / m_backBuildSprite.getLocalBounds().width, 648 / m_backBuildSprite.getLocalBounds().height);
    m_backBuildSprite.setPosition(0, 0);
    m_backBuildSprite2
        .setScale(1152 / m_backBuildSprite2.getLocalBounds().width, 648 / m_backBuildSprite2.getLocalBounds().height);
    m_backBuildSprite2.setPosition(m_backBuildSprite2.getLocalBounds().width * 2, 0);

    m_midBuildSprite.setScale(1152 / m_midBuildSprite.getLocalBounds().width, 648 / m_midBuildSprite.getLocalBounds().height);
    m_midBuildSprite.setPosition(0, 0);
    m_midBuildSprite2.setScale(1152 / m_midBuildSprite2.getLocalBounds().width, 648 / m_midBuildSprite2.getLocalBounds().height);
    m_midBuildSprite2.setPosition(m_midBuildSprite2.getLocalBounds().width * 2, 0);

    m_frontBuildSprite
        .setScale(1152 / m_frontBuildSprite.getLocalBounds().width, 648 / m_frontBuildSprite.getLocalBounds().height);
    m_frontBuildSprite.setPosition(0, 0);
    m_frontBuildSprite2
        .setScale(1152 / m_frontBuildSprite2.getLocalBounds().width, 648 / m_frontBuildSprite2.getLocalBounds().height);
    m_frontBuildSprite2.setPosition(m_frontBuildSprite2.getLocalBounds().width * 2, 0);

    m_cursorSprite.setScale(32 / m_cursorSprite.getLocalBounds().width, 32 / m_cursorSprite.getLocalBounds().height);
    m_cursorSprite.setPosition(0, 0);
}

void Game::moveParallax()
{
    this->m_backSprite.move(-0.4, 0);
    this->m_backSprite2.move(-0.4, 0);

    this->m_veryBackBuildSprite.move(-0.7, 0);
    this->m_veryBackBuildSprite2.move(-0.7, 0);

    this->m_backBuildSprite.move(-1.5, 0);
    this->m_backBuildSprite2.move(-1.5, 0);

    this->m_midBuildSprite.move(-2, 0);
    this->m_midBuildSprite2.move(-2, 0);

    this->m_frontBuildSprite.move(-4, 0);
    this->m_frontBuildSprite2.move(-4, 0);
}

void Game::repeatParallax()
{
    if (this->m_backSprite.getPosition().x <= -m_backSprite.getLocalBounds().width * 2)
        m_backSprite.setPosition(m_backSprite.getLocalBounds().width * 2, 0);
    if (this->m_backSprite2.getPosition().x <= -m_backSprite2.getLocalBounds().width * 2)
        m_backSprite2.setPosition(m_backSprite2.getLocalBounds().width * 2, 0);

    if (this->m_veryBackBuildSprite.getPosition().x <= -m_veryBackBuildSprite.getLocalBounds().width * 2)
        m_veryBackBuildSprite.setPosition(m_veryBackBuildSprite.getLocalBounds().width * 2, 0);
    if (this->m_veryBackBuildSprite2.getPosition().x <= -m_veryBackBuildSprite2.getLocalBounds().width * 2)
        m_veryBackBuildSprite2.setPosition(m_veryBackBuildSprite2.getLocalBounds().width * 2, 0);

    if (this->m_backBuildSprite.getPosition().x <= -m_backBuildSprite.getLocalBounds().width * 2)
        m_backBuildSprite.setPosition(m_backBuildSprite.getLocalBounds().width * 2, 0);
    if (this->m_backBuildSprite2.getPosition().x <= -m_backBuildSprite2.getLocalBounds().width * 2)
        m_backBuildSprite2.setPosition(m_backBuildSprite2.getLocalBounds().width * 2, 0);

    if (this->m_midBuildSprite.getPosition().x <= -m_midBuildSprite.getLocalBounds().width * 2)
        m_midBuildSprite.setPosition(m_midBuildSprite.getLocalBounds().width * 2, 0);
    if (this->m_midBuildSprite2.getPosition().x <= -m_midBuildSprite2.getLocalBounds().width * 2)
        m_midBuildSprite2.setPosition(m_midBuildSprite2.getLocalBounds().width * 2, 0);

    if (this->m_frontBuildSprite.getPosition().x <= -m_frontBuildSprite.getLocalBounds().width * 2)
        m_frontBuildSprite.setPosition(m_frontBuildSprite.getLocalBounds().width * 2, 0);
    if (this->m_frontBuildSprite2.getPosition().x <= -m_frontBuildSprite2.getLocalBounds().width * 2)
        m_frontBuildSprite2.setPosition(m_frontBuildSprite2.getLocalBounds().width * 2, 0);
}

float Game::getPosPlayerY(Registry& registry)
{
    Entity player = registry.getPlayer();
    Position playerPos = registry.getComponent(player, Position{});
    std::pair<float, float> pairPos = playerPos.getPosition();
    Renderer playerRenderer = registry.getComponent(player, Renderer{});
    sf::Sprite playerSprite = playerRenderer.getRenderer();
    return pairPos.second + (playerSprite.getGlobalBounds().height / 2);
}

float Game::getPosPlayerX(Registry& registry)
{
    Entity player = registry.getPlayer();
    Renderer playerRenderer = registry.getComponent(player, Renderer{});
    sf::Sprite playerSprite = playerRenderer.getRenderer();
    return playerSprite.getPosition().x;
}

float Game::setNewPositionX(const sf::Sprite& /*mSprite*/, CommandsToServer& mCommandsToServer)
{
    std::istringstream iss(mCommandsToServer.getNewPos());
    std::vector<std::string> tokens;
    std::ostringstream newPos;

    std::string token;
    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    float newPosX = std::stof(tokens[1]);
    return newPosX;
}

float Game::setNewPositionY(const sf::Sprite& /*mSprite*/, CommandsToServer& mCommandsToServer)
{
    std::istringstream iss(mCommandsToServer.getNewPos());
    std::vector<std::string> tokens;
    std::ostringstream newPos;

    std::string token;
    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    float newPosY = std::stof(tokens[2]);
    return newPosY;
}

void Game::colidePlayer()
{
}

void Game::isPaused()
{
    if (!this->onPause) {
        this->onPause = true;
        return;
    } else if (this->onPause) {
        this->onPause = false;
        return;
    }
}

void Game::setCursorPosition(sf::RenderWindow& window)
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

float Game::getCursorPosX()
{
    return this->m_cursorSprite.getPosition().x;
}

float Game::getCursorPosY()
{
    return this->m_cursorSprite.getPosition().y;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_backTexture;
    states.texture = &m_backTexture2;
    states.texture = &m_veryBackBuildTexture;
    states.texture = &m_veryBackBuildTexture2;
    states.texture = &m_backBuildTexture;
    states.texture = &m_backBuildTexture2;
    states.texture = &m_midBuildTexture;
    states.texture = &m_midBuildTexture2;
    states.texture = &m_frontBuildTexture;
    states.texture = &m_frontBuildTexture2;
    target.draw(m_backSprite, states);
    target.draw(m_backSprite2, states);
    target.draw(m_veryBackBuildSprite, states);
    target.draw(m_veryBackBuildSprite2, states);
    target.draw(m_backBuildSprite, states);
    target.draw(m_backBuildSprite2, states);
    target.draw(m_midBuildSprite, states);
    target.draw(m_midBuildSprite2, states);
    target.draw(m_frontBuildSprite, states);
    target.draw(m_frontBuildSprite2, states);
    if (this->onPause) {
        states.texture = &m_cursorTexture;
        target.draw(m_cursorSprite, states);
    }
}

void Game::moveEnemies(Registry& registry)
{
    const std::vector<Entity>& ennemies = registry.getListEnemies();

    for (auto& ennemy : ennemies) {
        Entity curr_ennemy = ennemy;
        Position& positionComponent = registry.getComponent(curr_ennemy, Position{});
        if (current_level == 1)
            positionComponent.setPosition(
                std::make_pair(positionComponent.getPosition().first - 4, positionComponent.getPosition().second));
        else
            positionComponent.setPosition(
                std::make_pair(positionComponent.getPosition().first - 1, positionComponent.getPosition().second));
        registry.setEntity(curr_ennemy, registry.getComponent(curr_ennemy, ID{}).getID());
    }
    std::cout << "ENNEMIES\n";
}

void Game::displayHealth(Registry& registry, Music& music, WindowManager& windowManager)
{
    Entity player;
    try {
        player = registry.getPlayer();
    } catch (std::exception& e) {
        std::cout << e.what();
        return;
    }
    int healthPoint = registry.getComponent(player, HealthPoint{}).getHealthPoint();

    if (!this->healthPointFirst || m_healthPointTemp != healthPoint) {
        this->m_healthPointTemp = healthPoint;
        sf::Text healthPointText;
        healthPointText.setFont(windowManager.getFont());
        healthPointText.setCharacterSize(24);
        healthPointText.setFillColor(sf::Color::White);
        healthPointText.setPosition(24, windowManager.getWindow().getSize().y - 48);

        std::string healthP = std::to_string(healthPoint);
        healthPointText.setString("HP: " + healthP);
        this->setHealthPointText(healthPointText);
    }

    if (healthPoint <= 0) {
        registry.deleteById(registry.getComponent(player, ID{}).getID());
        music.musicMenu.stop();
        music.killPlayer.play();
        this->onGame = false;
    }
}

void Game::setHealthPointText(sf::Text mHealthPoint)
{
    this->m_healthPointText = std::move(mHealthPoint);
}

sf::Text Game::getHealthPointText()
{
    return m_healthPointText;
}
