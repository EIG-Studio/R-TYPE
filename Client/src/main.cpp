/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "button.hpp"
#include "menu/inGame.hpp"
#include "menu/introMenu/introMenu.hpp"
#include "music/music.hpp"
#include "sprite/sprite.hpp"
#include "commandsToServer.hpp"
#include <SFML/System.hpp>

int main()
{
    float movementSpeed = 3.0f;
    //Calculating the milliseconds per frame for 144 FPS
    float milliseconds_per_second = 1000;
    float fps = 144;

    float milliseconds_per_frame = milliseconds_per_second / fps;

    auto window = sf::RenderWindow{{800, 600}, "SAMURAI"};
    window.setFramerateLimit(144);
    sf::Image icon;
    if (!icon.loadFromFile("../assets/MainMenu/samuraiLogo.png"))
    {
        return -1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    sf::Font font;
    if (!font.loadFromFile("../assets/Fonts/retro.ttf"))
    {
        return -1;
    }

    sf::Clock  clock;
    sf::Clock  onGame_clock;
    CommandsToServer commandsToServer;
    Sprite     sprite;
    Menu       menu;
    menu.setPath(sprite);
    ChoiceMenu choiceMenu;
    choiceMenu.setPath(sprite);
    Game       game;
    game.setPath(sprite);
    Music      music;
    music.setPath(sprite);

    Button playButton(window,
                      sf::Vector2f(200, 50),
                      sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 - 60),
                      sf::Color::Black,
                      sf::Color::White,
                      2.0f,
                      "Play",
                      font,
                      20);

    Button settingsButton(window,
                          sf::Vector2f(200, 50),
                          sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2),
                          sf::Color::Black,
                          sf::Color::White,
                          2.0f,
                          "Settings",
                          font,
                          20);

    Button exitButton(window,
                      sf::Vector2f(200, 50),
                      sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 60),
                      sf::Color::Black,
                      sf::Color::White,
                      2.0f,
                      "Exit",
                      font,
                      20);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menu.onMenu)
            {
                menu.onMenu         = false;
                choiceMenu.onChoice = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && menu.onMenu && !sprite.easterEgg)
            {
                music.musicMenu.stop();
                sprite.setLogoPath("../assets/MainMenu/runnerLogo.png");
                sprite.setTitlePath("../assets/MainMenu/runnerTitle.png");
                sprite.setMainSongPath("../assets/Songs/runner.wav");
                menu.setPath(sprite);
                choiceMenu.setPath(sprite);
                music.setPath(sprite);
                game.setPath(sprite);
                music.musicMenu.play();
                sprite.easterEgg = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && choiceMenu.onChoice && !sprite.easterEgg)
            {
                music.musicMenu.stop();
                sprite.setLogoPath("../assets/MainMenu/runnerLogo.png");
                sprite.setTitlePath("../assets/MainMenu/runnerTitle.png");
                sprite.setMainSongPath("../assets/Songs/runner.wav");
                menu.setPath(sprite);
                choiceMenu.setPath(sprite);
                music.setPath(sprite);
                game.setPath(sprite);
                music.musicMenu.play();
                sprite.easterEgg = true;
            }
            if (game.onGame)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    game.onGame         = false;
                    choiceMenu.onChoice = true;
                }
            }
        }
        window.clear();
        if (menu.onMenu)
        {
            if (music.playMenuMusic)
            {
                music.musicMenu.play();
                music.playMenuMusic = false;
            }
            sf::Time elapsed = clock.getElapsedTime();
            clock            = menu.blinkingText(clock, elapsed);
            window.draw(menu);
        }
        else if (choiceMenu.onChoice)
        {
            if (playButton.checkClick())
            {
                game.onGame         = true;
                choiceMenu.onChoice = false;
            }
            if (settingsButton.checkClick())
            {
                std::cout << "Setting button" << std::endl;
            }
            if (exitButton.checkClick())
            {
                exit(0);
            }
            window.draw(choiceMenu);
            playButton.draw();
            settingsButton.draw();
            exitButton.draw();
        }
        else if (game.onGame)
        {
            sf::Time render_elapsed = onGame_clock.getElapsedTime();
            game.moveSprite(movementSpeed, window.getSize().x, window.getSize().y, commandsToServer);
            if (render_elapsed.asMilliseconds() > milliseconds_per_frame)
            {
                game.moveParallax();
                game.repeatParallax();
                onGame_clock.restart();
            }
            window.draw(game);
        }
        window.display();
    }
}
