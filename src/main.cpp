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


int main()
{
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
    Sprite     sprite;
    Menu       menu;
    menu.setPath(sprite);
    ChoiceMenu choiceMenu;
    choiceMenu.setPath(sprite);
    Game       game;
    game.setPath(sprite);
    Music      music;

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && menu.onMenu)
            {
                sprite.setLogoPath("../assets/MainMenu/MostlyCatsMostly.jpg");
                menu.setPath(sprite);
                choiceMenu.setPath(sprite);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && choiceMenu.onChoice)
            {
                sprite.setLogoPath("../assets/MainMenu/MostlyCatsMostly.jpg");
                menu.setPath(sprite);
                choiceMenu.setPath(sprite);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && game.onGame)
            {
                game.onGame         = false;
                choiceMenu.onChoice = true;
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
            window.draw(game);
        }
        window.display();
    }
}
