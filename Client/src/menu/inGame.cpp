/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** inGame
*/

#include "menu/inGame.hpp"

#include <sstream>

Game::Game()
{
    this->onGame = false;
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

    this->m_playerTexture.loadFromFile(mSprite.getPlayerPath());
    this->m_playerSprite.setTexture(this->m_playerTexture);

    //// Trouver un moyen pour rendre ça plus beau
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

    m_playerSprite.setScale(103 / m_playerSprite.getLocalBounds().width, 56.25 / m_playerSprite.getLocalBounds().height);
    m_playerSprite.setPosition(100, 100);
}

void Game::setPlayerPath(Sprite mSprite)
{
    this->m_playerTexture.loadFromFile(mSprite.getPlayerPath());
    this->m_playerSprite.setTexture(this->m_playerTexture);
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

float Game::setNewPositionX(sf::Sprite mSprite, CommandsToServer& mCommandsToServer)
{
    std::istringstream iss(mCommandsToServer.getNewPos());
    std::vector<std::string> tokens;
    std::ostringstream newPos;

    // Reception et séparation pour plus de facilité de modification
    std::string token;
    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    float newPosX = std::stof(tokens[1]);
    return newPosX;
}

float Game::setNewPositionY(sf::Sprite mSprite, CommandsToServer& mCommandsToServer)
{
    std::istringstream iss(mCommandsToServer.getNewPos());
    std::vector<std::string> tokens;
    std::ostringstream newPos;

    // Reception et séparation pour plus de facilité de modification
    std::string token;
    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    float newPosY = std::stof(tokens[2]);
    return newPosY;
}

void Game::moveSprite(float movementSpeed, float winX, float winY, CommandsToServer& commandsToServer, Sprite mSprite)
{
    float tempPosX = this->m_playerSprite.getPosition().x;
    float tempPosY = this->m_playerSprite.getPosition().y;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -20) {
        if (this->m_playerSprite.getPosition().y > 0) {
            // Il faut bouger de movementSpeed à chaque fois
            std::ostringstream oss;
            oss << "POS " << this->m_playerSprite.getPosition().x << " " << this->m_playerSprite.getPosition().y << " "
                << movementSpeed << " 1";
            std::string positionString = oss.str();
            commandsToServer.sendToServerAsync(positionString);
            //
            // ecs.callMoveUp();
            std::cout << "UP" << std::endl;

            this->m_playerSprite
                .setPosition(this->setNewPositionX(this->m_playerSprite, commandsToServer), this->setNewPositionY(this->m_playerSprite, commandsToServer));
            //
            mSprite.setPlayerPath("../Client/assets/Cars/189_toUp.png");
            this->setPlayerPath(mSprite);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 20) {
        if (this->m_playerSprite.getPosition().x < winX - 103) {
            // Il faut bouger de movementSpeed à chaque fois
            std::ostringstream oss;
            oss << "POS " << this->m_playerSprite.getPosition().x << " " << this->m_playerSprite.getPosition().y << " "
                << movementSpeed << " 2";
            std::string positionString = oss.str();
            commandsToServer.sendToServerAsync(positionString);
            //
            // ecs.callMoveRight();
            std::cout << "RIGHT" << std::endl;
            this->m_playerSprite
                .setPosition(this->setNewPositionX(this->m_playerSprite, commandsToServer), this->setNewPositionY(this->m_playerSprite, commandsToServer));
            //
            mSprite.setPlayerPath("../Client/assets/Cars/189_toRight.png");
            this->setPlayerPath(mSprite);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 20) {
        if (this->m_playerSprite.getPosition().y < winY - 37.75) {
            // Il faut bouger de movementSpeed à chaque fois
            std::ostringstream oss;
            oss << "POS " << this->m_playerSprite.getPosition().x << " " << this->m_playerSprite.getPosition().y << " "
                << movementSpeed << " 3";
            std::string positionString = oss.str();
            commandsToServer.sendToServerAsync(positionString);
            //
            // ecs.callMoveDown();
            std::cout << "DOWN" << std::endl;
            this->m_playerSprite
                .setPosition(this->setNewPositionX(this->m_playerSprite, commandsToServer), this->setNewPositionY(this->m_playerSprite, commandsToServer));
            //
            mSprite.setPlayerPath("../Client/assets/Cars/189_toDown.png");
            this->setPlayerPath(mSprite);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -20) {
        if (this->m_playerSprite.getPosition().x > 0) {
            // Il faut bouger de movementSpeed à chaque fois
            std::ostringstream oss;
            oss << "POS " << this->m_playerSprite.getPosition().x << " " << this->m_playerSprite.getPosition().y << " "
                << movementSpeed << " 4";
            std::string positionString = oss.str();
            commandsToServer.sendToServerAsync(positionString);
            //
            // ecs.callMoveLeft();
            std::cout << "LEFT" << std::endl;
            this->m_playerSprite
                .setPosition(this->setNewPositionX(this->m_playerSprite, commandsToServer), this->setNewPositionY(this->m_playerSprite, commandsToServer));
            //
            mSprite.setPlayerPath("../Client/assets/Cars/189_toLeft.png");
            this->setPlayerPath(mSprite);
        }
    }
    if (tempPosX == this->m_playerSprite.getPosition().x && tempPosY == this->m_playerSprite.getPosition().y) {
        mSprite.setPlayerPath("../Client/assets/Cars/189_neutral.png");
        this->setPlayerPath(mSprite);
    }
}

void Game::colidePlayer()
{
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
    states.texture = &m_playerTexture;
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
    target.draw(m_playerSprite, states);
}
