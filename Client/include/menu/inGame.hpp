/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** inGame
*/

#pragma once

#include "commandsToServer.hpp"
#include "entities.hpp"
#include "ipAdress.hpp"
#include "menu/menus.hpp"
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
    float setNewPositionX(const sf::Sprite& mSprite, CommandsToServer& mCommandsToServer);
    float setNewPositionY(const sf::Sprite& mSprite, CommandsToServer& mCommandsToServer);
    void sendMessage(CommandsToServer& commandsToServer);
    void movePlayer(
        Registry& registry,
        float movementSpeed,
        float winX,
        float winY,
        CommandsToServer& commandsToServer,
        const Sprite& mSprite,
        IpAdress& ipAdress);
    void moveBullets(Registry& registry);
    void moveEnemies(Registry& registry) const;
    void movePlayerProjectile(CommandsToServer& commandsToServer, Registry& registry, const std::vector<Entity>& bullets);
    void handleMovement(
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
    void sendPositionUpdate(CommandsToServer& commandsToServer, Registry& registry, std::pair<float, float> newPos, float speed);
    void sendInputUpdate(CommandsToServer& commandsToServer, Registry& registry, const std::string& inputType, IpAdress& ipAdress);
    std::string inputTypeToString(sf::Keyboard::Key key);
    void colidePlayer();
    void shooting(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress);
    void checkGetPowerUp(Registry& registry);
    void damageToPlayer(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress);
    void isPaused();
    void setCursorPosition(sf::RenderWindow& window);
    float getCursorPosX();
    float getCursorPosY();
    void displayHealth(Registry& registry, Music& music, WindowManager& windowManager, YouLooseMenu& youLooseMenu);

    void setHealthPointText(sf::Text mHealthPoint);
    sf::Text getHealthPointText();

    bool onGame;
    bool onPause;
    bool healthPointFirst{false};
    bool hasFocus{false};
    int currentLevel = 1;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Entity m_player;

    sf::Clock m_updateClock;

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

    sf::Text m_healthPointText;
    int m_healthPointTemp;
};
