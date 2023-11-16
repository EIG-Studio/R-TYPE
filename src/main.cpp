/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "button.hpp"
#include "menu/introMenu/introMenu.hpp"
#include "music/music.hpp"


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

    //// Faut ranger ça <
    sf::Font font;
    if (!font.loadFromFile("../assets/Fonts/retro.ttf"))
    {
        return -1;
    }
    sf::Text blinkingText("Press ENTER to burn the city", font, 30);
    blinkingText.setFillColor(sf::Color::White);
    blinkingText.setPosition(800 / 2 - blinkingText.getGlobalBounds().width / 2,
                             600 / 1.2 - blinkingText.getGlobalBounds().height / 2);
    //// > jusqu'ici

    sf::Clock  clock;
    Menu       menu;
    ChoiceMenu choiceMenu;
    Music      music;

    Button playButton(window,
                      sf::Vector2f(200, 50),
                      sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2),
                      sf::Color::Black,
                      sf::Color::White,
                      2.0f,
                      "Play",
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
            if (elapsed.asMilliseconds() > 500)
            {
                blinkingText.setFillColor(
                    blinkingText.getFillColor() == sf::Color::Transparent ? sf::Color::White : sf::Color::Transparent);
                clock.restart();
            }
            window.draw(menu);
            window.draw(blinkingText);
        }
        else if (choiceMenu.onChoice)
        {
            if (playButton.checkClick())
            {
                std::cout << "Play button" << std::endl;
            }
            if (exitButton.checkClick())
            {
                std::cout << "Exit button" << std::endl;
                exit(0);
            }
            window.draw(choiceMenu);
            exitButton.draw();
            playButton.draw();
        }
        window.display();
    }
}
