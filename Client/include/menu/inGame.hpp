/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** inGame
*/

#pragma once

#include "commandsToServer.hpp"
#include "sprite/sprite.hpp"

class Game : public sf::Drawable, public sf::Transformable
{
public:
    Game();
    ~Game() override = default;
    void  setPath(Sprite mSprite);
    void  setPlayerPath(Sprite mSprite);
    void  moveParallax();
    void  repeatParallax();
    float setNewPositionX(sf::Sprite mSprite, CommandsToServer mCommandsToServer);
    float setNewPositionY(sf::Sprite mSprite, CommandsToServer mCommandsToServer);
    void  moveSprite(float movementSpeed, float winX, float winY, CommandsToServer mCommandsToServer, Sprite mSprite);
    void  colidePlayer();
    bool  onGame;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_backTexture;
    sf::Sprite  m_backSprite;
    sf::Texture m_backTexture2;
    sf::Sprite  m_backSprite2;

    sf::Texture m_veryBackBuildTexture;
    sf::Sprite  m_veryBackBuildSprite;
    sf::Texture m_veryBackBuildTexture2;
    sf::Sprite  m_veryBackBuildSprite2;

    sf::Texture m_backBuildTexture;
    sf::Sprite  m_backBuildSprite;
    sf::Texture m_backBuildTexture2;
    sf::Sprite  m_backBuildSprite2;

    sf::Texture m_midBuildTexture;
    sf::Sprite  m_midBuildSprite;
    sf::Texture m_midBuildTexture2;
    sf::Sprite  m_midBuildSprite2;

    sf::Texture m_frontBuildTexture;
    sf::Sprite  m_frontBuildSprite;
    sf::Texture m_frontBuildTexture2;
    sf::Sprite  m_frontBuildSprite2;

    sf::Texture m_playerTexture;
    sf::Sprite  m_playerSprite;
};
