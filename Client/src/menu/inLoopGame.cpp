/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopGame
*/

#include "menu/inLoopGame.hpp"

#include "menu/inGame.hpp"

#include <iostream>

void InLoopGame::updateScore(WindowManager& windowManager, Registry& registry)
{
    if (registry.hasEntityType(HUD)) {
        windowManager.getWindow().clear();
        Entity score = registry.getScore();
        ScorePoint scorePoints = registry.getComponent(score, ScorePoint{});

        scoreText.setString("Score: " + std::to_string(static_cast<int>(scorePoints.getScorePoint())));
    }
}

void InLoopGame::refreshRegistry(Registry& registry, CommandsToServer& commandsToServer, IpAdress& ipAdress)
{
    if (m_clock.getElapsedTime().asMilliseconds() < 1000)
        return;
    m_clock.restart();
    for (auto& entity : registry.getListEntities()) {
        if (!registry.hasComponent(entity, Type()))
            continue;
        EntityType type = registry.getComponent(entity, Type()).getEntityType();
        if (type == EntityType::Player || type == EntityType::Player_Projectile || type == EntityType::Enemy) {
            commandsToServer.sendToServerAsync("REFRESH " + std::to_string(registry.getComponent(entity, ID()).getID()), ipAdress);
            continue;
        }
    }
}

void InLoopGame::pingServer(CommandsToServer& commandsToServer, IpAdress& ipAdress)
{
    if (m_clock2.getElapsedTime().asMilliseconds() < 1000)
        return;
    m_clock2.restart();
    commandsToServer.sendToServerAsync("ALIVE", ipAdress);
}

void boosIsAlive(Registry& registry, Game& game, YouWinMenu& youWinMenu)
{
    if (registry.hasEntityType(Boss)) {
        Entity boss = registry.getBoss();
        if (registry.hasComponent(boss, HealthPoint{})) {
            HealthPoint& bossHealth = registry.getComponent(boss, HealthPoint{});
            if (bossHealth.getHealthPoint() <= 0) {
                game.onGame = false;
                youWinMenu.onWin = true;
            }
        }
    }
}

void InLoopGame::gameInLoop(
    sf::Event& event,
    WindowManager& windowManager,
    Game& game,
    Music& music,
    CommandsToServer& commandsToServer,
    Sprite& sprite,
    sf::Clock& onGameClock,
    Registry& registry,
    ButtonManager& buttonManager,
    ChoiceMenu& choiceMenu,
    YouWinMenu& youWinMenu,
    YouLooseMenu& youLooseMenu,
    IpAdress& ipAdress)
{
    game.setCursorPosition(windowManager.getWindow());
    buttonManager.getResumeButton().checkHover(game.getCursorPosX(), game.getCursorPosY());
    buttonManager.getToMenuButton().checkHover(game.getCursorPosX(), game.getCursorPosY());
    if (buttonManager.getResumeButton().checkClick(game.getCursorPosX(), game.getCursorPosY())) {
        game.onPause = false;
    }
    if (buttonManager.getToMenuButton().checkClick(game.getCursorPosX(), game.getCursorPosY())) {
        game.onGame = false;
        choiceMenu.onChoice = true;
    }
    sf::Time renderElapsed = onGameClock.getElapsedTime();
    game.hasFocus = windowManager.getWindow().hasFocus();
    commandsToServer.mutex.lock();
    refreshRegistry(registry, commandsToServer, ipAdress);
    pingServer(commandsToServer, ipAdress);
    try {
        game.displayHealth(std::ref(registry), music, windowManager, youLooseMenu);
        updateScore(windowManager, registry);
        boosIsAlive(registry, game, youWinMenu);
        game.movePlayer(
            std::ref(registry),
            windowManager.getMovementSpeed(),
            windowManager.getWindow().getSize().x,
            windowManager.getWindow().getSize().y,
            commandsToServer,
            sprite,
            ipAdress);
        game.moveEnemies(registry);
        game.moveBullets(registry);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::F) {
            game.shooting(commandsToServer, registry, ipAdress);
            music.shootSound.play();
        }
        if (event.key.code == sf::Keyboard::P) {
            std::ostringstream pUp;
            pUp << "POWER_UP " << 200 << " " << 200;
            commandsToServer.sendToServerAsync(pUp.str(), ipAdress);
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Escape) {
            game.isPaused();
        }
    }
    if (event.type == sf::Event::JoystickButtonReleased && game.onGame) {
        if (event.joystickButton.button == sf::Joystick::Y) {
            game.shooting(commandsToServer, registry, ipAdress);
        }
    }
    commandsToServer.mutex.unlock();
    if (renderElapsed.asMilliseconds() > windowManager.getMillisecondsPerFrame()) {
        game.moveParallax();
        game.repeatParallax();
        onGameClock.restart();
    }
    windowManager.getWindow().draw(game);
    commandsToServer.mutex.lock();
    try {
        registry.systemsManager(windowManager.getWindow());
        windowManager.getWindow().draw(scoreText);
        windowManager.getWindow().draw(game.getHealthPointText());
        if (game.onPause) {
            buttonManager.getResumeButton().draw(windowManager.getWindow());
            buttonManager.getToMenuButton().draw(windowManager.getWindow());
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    commandsToServer.mutex.unlock();
}
