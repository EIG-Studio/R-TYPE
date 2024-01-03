/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "../../GameEngine/include/Systems.hpp"
#include "../../GameEngine/include/components.hpp"
#include "../../GameEngine/include/entities.hpp"
#include "ECS.hpp"
#include "button.hpp"
#include "commandsToServer.hpp"
#include "menu/inGame.hpp"
#include "menu/introMenu/introMenu.hpp"
#include "menu/settingMenu.hpp"
#include "music/music.hpp"
#include "sprite/sprite.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <SFML/System.hpp>

#include <dlfcn.h>

int main()
{
    float movementSpeed = 5.0f;
    // Calculating the milliseconds per frame for 144 FPS
    float millisecondsPerSecond = 1000;
    float fps = 144;

    float millisecondsPerFrame = millisecondsPerSecond / fps;

    auto window = sf::RenderWindow{{800, 600}, "SAMURAI"};
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);
    sf::Image icon;
    if (!icon.loadFromFile("../Client/assets/MainMenu/samuraiLogo.png")) {
        return -1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf::Font font;
    if (!font.loadFromFile("../Client/assets/Fonts/retro.ttf")) {
        return -1;
    }

    sf::Clock clock;
    sf::Clock onGameClock;
    CommandsToServer commandsToServer;
    Sprite sprite;
    Menu menu;
    menu.setPath(sprite);
    ChoiceMenu choiceMenu;
    choiceMenu.setPath(sprite);
    SettingMenu settingMenu;
    settingMenu.setPath(sprite);
    Game game;
    game.setPath(sprite);
    Music music;
    music.setPath(sprite);

    Button playButton(
        window,
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 - 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Play",
        font,
        20);

    Button settingsButton(
        window,
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Settings",
        font,
        20);

    Button retourButton(
        window,
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 + 150, window.getSize().y / 2 + 200),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Retour",
        font,
        20);

    Button exitButton(
        window,
        sf::Vector2f(200, 50),
        sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Exit",
        font,
        20);

    Registry registry = Registry();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Joystick::isButtonPressed(0, 7)) && menu.onMenu) {
                menu.onMenu = false;
                choiceMenu.onChoice = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && menu.onMenu && !sprite.easterEgg) {
                music.musicMenu.stop();
                sprite.setLogoPath("../Client/assets/MainMenu/runnerLogo.png");
                sprite.setTitlePath("../Client/assets/MainMenu/runnerTitle.png");
                sprite.setMainSongPath("../Client/assets/Songs/runner.wav");
                menu.setPath(sprite);
                choiceMenu.setPath(sprite);
                music.setPath(sprite);
                game.setPath(sprite);
                music.musicMenu.play();
                sprite.easterEgg = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && choiceMenu.onChoice && !sprite.easterEgg) {
                music.musicMenu.stop();
                sprite.setLogoPath("../Client/assets/MainMenu/runnerLogo.png");
                sprite.setTitlePath("../Client/assets/MainMenu/runnerTitle.png");
                sprite.setMainSongPath("../Client/assets/Songs/runner.wav");
                menu.setPath(sprite);
                choiceMenu.setPath(sprite);
                music.setPath(sprite);
                game.setPath(sprite);
                music.musicMenu.play();
                sprite.easterEgg = true;
            }
            if (game.onGame) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 7)) {
                    game.onGame = false;
                    choiceMenu.onChoice = true;
                }
            }
        }
        window.clear();
        if (menu.onMenu) {
            if (music.playMenuMusic) {
                music.musicMenu.play();
                music.playMenuMusic = false;
            }
            sf::Time elapsed = clock.getElapsedTime();
            clock = menu.blinkingText(clock, elapsed);
            window.draw(menu);
        } else if (choiceMenu.onChoice) {
            choiceMenu.setCursorPosition(window);
            playButton.checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
            settingsButton.checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
            exitButton.checkHover(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY());
            if (playButton.checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY()) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                game.onGame = true;
                choiceMenu.onChoice = false;
                commandsToServer.sendToServerAsync("LOGIN", registry);
                commandsToServer.sendToServerAsync("UPDATE", registry);
            }
            if (settingsButton.checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY())) {
                settingMenu.onSetting = true;
                choiceMenu.onChoice = false;
            }
            if (exitButton.checkClick(choiceMenu.getCursorPosX(), choiceMenu.getCursorPosY())) {
                exit(0);
            }
            playButton.draw();
            settingsButton.draw();
            exitButton.draw();
            window.draw(choiceMenu);
        } else if (settingMenu.onSetting) {
            retourButton.checkHover(settingMenu.getCursorPosX(), settingMenu.getCursorPosY());
            settingMenu.setCursorPosition(window);
            if (retourButton.checkClick(settingMenu.getCursorPosX(), settingMenu.getCursorPosY())) {
                settingMenu.onSetting = false;
                choiceMenu.onChoice = true;
            }
            retourButton.draw();
            window.draw(settingMenu);

        } else if (game.onGame) {
            std::vector<Entity> players = registry.getListPlayers();
            std::vector<Entity> ennemies = registry.getListEnemies();
            std::vector<Entity> playersProjectiles = registry.getListPlayersProjectile();
            sf::Time renderElapsed = onGameClock.getElapsedTime();
            game.hasFocus = window.hasFocus();
            game.movePlayer(registry, movementSpeed, window.getSize().x, window.getSize().y, commandsToServer, sprite);
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::F) {
                    game.shooting(commandsToServer, registry);
                }
            }
            if (event.type == sf::Event::JoystickButtonReleased && game.onGame) {
                if (event.joystickButton.button == sf::Joystick::Y) {
                    commandsToServer.sendToServerAsync("SHOOT", registry);
                }
            }
            if (renderElapsed.asMilliseconds() > millisecondsPerFrame) {
                game.moveEnnemies(commandsToServer, registry, ennemies);
                game.movePlayerProjectile(commandsToServer, registry, playersProjectiles);
                game.moveParallax();
                game.repeatParallax();
                onGameClock.restart();
            }
            window.draw(game);
            for (auto& player : players) {
                renderSystem(player, registry, window);
            }
            for (auto& ennemy : ennemies) {
                renderSystem(ennemy, registry, window);
            }
            for (auto& playerProjectile : playersProjectiles) {
                renderSystem(playerProjectile, registry, window);
            }
        }
        window.display();
    }
}
