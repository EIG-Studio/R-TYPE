/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopGame
*/

#include "menu/inLoopGame.hpp"


void InLoopGame::gameInLoop(
    sf::Event& event,
    WindowManager& windowManager,
    Game& game,
    CommandsToServer& commandsToServer,
    Sprite& sprite,
    sf::Clock& onGameClock,
    Registry& registry,
    Button& resumeButton,
    Button& toMenuButton)
{
    game.setCursorPosition(windowManager.getWindow());
    resumeButton.checkHover(game.getCursorPosX(), game.getCursorPosY());
    toMenuButton.checkHover(game.getCursorPosX(), game.getCursorPosY());
    if (resumeButton.checkClick(game.getCursorPosX(), game.getCursorPosY())) {
        game.onPause = false;
    }
    if (toMenuButton.checkClick(game.getCursorPosX(), game.getCursorPosY())) {
        game.onGame = false;
    }
    std::vector<Entity> players = registry.getListPlayers();
    std::vector<Entity> ennemies = registry.getListEnemies();
    std::vector<Entity> playersProjectiles = registry.getListPlayersProjectile();
    sf::Time renderElapsed = onGameClock.getElapsedTime();
    game.hasFocus = windowManager.getWindow().hasFocus();
    commandsToServer.mutex.lock();
    game.movePlayer(
        std::ref(registry),
        windowManager.getMovementSpeed(),
        windowManager.getWindow().getSize().x,
        windowManager.getWindow().getSize().y,
        commandsToServer,
        sprite);
    commandsToServer.mutex.unlock();
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::F) {
            game.shooting(commandsToServer, registry);
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Escape) {
            game.isPaused();
        }
    }
    if (event.type == sf::Event::JoystickButtonReleased && game.onGame) {
        if (event.joystickButton.button == sf::Joystick::Y) {
            game.shooting(commandsToServer, registry);
        }
    }
    if (renderElapsed.asMilliseconds() > windowManager.getMillisecondsPerFrame()) {
        game.moveEnnemies(commandsToServer, registry, ennemies);
        std::vector<Entity> ennemies = registry.getListEnemies();
        game.movePlayerProjectile(commandsToServer, registry, playersProjectiles);
        std::vector<Entity> playersProjectiles = registry.getListPlayersProjectile();
        game.moveParallax();
        game.repeatParallax();
        onGameClock.restart();
    }
    windowManager.getWindow().draw(game);
    for (auto& player : players) {
        renderSystem(player, registry, windowManager.getWindow());
    }
    for (auto& ennemy : ennemies) {
        renderSystem(ennemy, registry, windowManager.getWindow());
    }
    for (auto& playerProjectile : playersProjectiles) {
        renderSystem(playerProjectile, registry, windowManager.getWindow());
    }
    if (game.onPause) {
        resumeButton.draw(windowManager.getWindow());
        toMenuButton.draw(windowManager.getWindow());
    }
}
