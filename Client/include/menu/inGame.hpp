/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** inGame
*/

#pragma once

#include "../../GameEngine/include/components.hpp"
#include "../../GameEngine/include/entities.hpp"
#include "commandsToServer.hpp"
#include "ipAdress.hpp"
#include "sprite/sprite.hpp"
#include "window.hpp"

class Game : public sf::Drawable, public sf::Transformable
{
public:
    Game();
    ~Game() override = default;
    void setPath(Sprite mSprite);
    void setPlayerPath(Sprite mSprite);
    float getPosPlayerY(Registry& registry);
    float getPosPlayerX(Registry& registry);
    void moveParallax();
    void repeatParallax();
    float setNewPositionX(sf::Sprite mSprite, CommandsToServer& mCommandsToServer);
    float setNewPositionY(sf::Sprite mSprite, CommandsToServer& mCommandsToServer);
    void SendMessage(CommandsToServer& commandsToServer);
    void movePlayer(
        Registry& registry,
        float movementSpeed,
        float winX,
        float winY,
        CommandsToServer& commandsToServer,
        Sprite mSprite,
        IpAdress& ipAdress);
    void moveEnemies(CommandsToServer& commandsToServer, Registry& registry, const std::vector<Entity>& enemies);
    void movePlayerProjectile(CommandsToServer& commandsToServer, Registry& registry, const std::vector<Entity>& bullets);
    void HandleMovement(
        Registry& registry,
        sf::Keyboard::Key key,
        CommandsToServer& commandsToServer,
        float movementSpeed,
        float deltaX,
        float deltaY,
        const std::string& path,
        float windowLimit,
        float spriteLimit,
        IpAdress& ipAdress);
    void SendPositionUpdate(CommandsToServer& commandsToServer, Registry& registry, std::pair<float, float> newPos, float speed);
    void SendInputUpdate(CommandsToServer& commandsToServer, Registry& registry, const std::string& inputType, IpAdress& ipAdress);
    std::string InputTypeToString(sf::Keyboard::Key key);
    void colidePlayer();
    void shooting(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress);
    void isPaused();
    void setCursorPosition(sf::RenderWindow& window);
    float getCursorPosX();
    float getCursorPosY();
    void displayArrow(Registry& registry, WindowManager& windowManager);

    bool onGame;
    bool onPause;
    bool hasFocus{false};

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Entity player;

    sf::Clock updateClock;

    sf::Texture m_backTexture;
    sf::Sprite m_backSprite;
    sf::Texture m_backTexture2;
    sf::Sprite m_backSprite2;

    sf::Texture m_veryBackBuildTexture;
    sf::Sprite m_veryBackBuildSprite;
    sf::Texture m_veryBackBuildTexture2;
    sf::Sprite m_veryBackBuildSprite2;

    sf::Texture m_backBuildTexture;
    sf::Sprite m_backBuildSprite;
    sf::Texture m_backBuildTexture2;
    sf::Sprite m_backBuildSprite2;

    sf::Texture m_midBuildTexture;
    sf::Sprite m_midBuildSprite;
    sf::Texture m_midBuildTexture2;
    sf::Sprite m_midBuildSprite2;

    sf::Texture m_frontBuildTexture;
    sf::Sprite m_frontBuildSprite;
    sf::Texture m_frontBuildTexture2;
    sf::Sprite m_frontBuildSprite2;

    sf::Texture m_playerTexture;
    sf::Sprite m_playerSprite;

    sf::Texture m_cursorTexture;
    sf::Sprite m_cursorSprite;
    int m_tempMouseX;
    int m_tempMouseY;
};
