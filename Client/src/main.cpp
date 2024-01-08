/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "ECS.hpp"
#include "Systems.hpp"
#include "commandsToServer.hpp"
#include "components.hpp"
#include "entities.hpp"
#include "menu/inGame.hpp"
#include "menu/inLoopGame.hpp"
#include "menu/inLoopMenus.hpp"
#include "menu/menus.hpp"
#include "music/sounds.hpp"
#include "sprite/sprite.hpp"
#include "window.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <SFML/System.hpp>

int main()
{
    WindowManager windowManager;
    windowManager.initWindow();
    InLoopMenus introMenu;
    InLoopGame inLoopGame;

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

    // count fps
    int frameCount = 0;
    sf::Text fpsText;
    fpsText.setFont(windowManager.getFont());
    fpsText.setCharacterSize(15);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.0f, 10.0f);

    Button playButton(
        windowManager.getWindow(),
        sf::Vector2f(200, 50),
        sf::Vector2f(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 2 - 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Play",
        windowManager.getFont(),
        20);

    Button settingsButton(
        windowManager.getWindow(),
        sf::Vector2f(200, 50),
        sf::Vector2f(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 2),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Settings",
        windowManager.getFont(),
        20);

    Button retourButton(
        windowManager.getWindow(),
        sf::Vector2f(200, 50),
        sf::Vector2f(windowManager.getWindow().getSize().x / 2 + 150, windowManager.getWindow().getSize().y / 2 + 200),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Retour",
        windowManager.getFont(),
        20);

    Button exitButton(
        windowManager.getWindow(),
        sf::Vector2f(200, 50),
        sf::Vector2f(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 2 + 60),
        sf::Color::Black,
        sf::Color::White,
        2.0f,
        "Exit",
        windowManager.getFont(),
        20);

    Registry registry = Registry();
    commandsToServer.asyncReceiveSecondSocket(std::ref(registry));
    while (windowManager.getWindow().isOpen()) {
        sf::Event event{};
        while (windowManager.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowManager.getWindow().close();
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
        // count fps
        windowManager.getWindow().clear();
        frameCount++;
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() >= 1000) {
            float fps = static_cast<float>(frameCount) / elapsed.asSeconds();
            fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

            // Reset the frame count and clock
            frameCount = 0;
            clock.restart();
        }
        if (menu.onMenu) {
            introMenu.introMenuInLoop(menu, windowManager, music, clock);
        } else if (choiceMenu.onChoice) {
            introMenu.choiceMenuInLoop(windowManager, choiceMenu, playButton, settingsButton, exitButton, game, commandsToServer, settingMenu);
        } else if (settingMenu.onSetting) {
            introMenu.settingsMenuInLoop(settingMenu, windowManager, choiceMenu, retourButton);
        } else if (game.onGame) {
            inLoopGame.gameInLoop(event, windowManager, game, commandsToServer, sprite, onGameClock, registry);
        }
        windowManager.getWindow().draw(fpsText);
        windowManager.getWindow().display();
    }
}
