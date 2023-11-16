/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "menu/mainMenu/mainMenu.hpp"
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

    sf::Font font;
    if (!font.loadFromFile("../assets/Fonts/retro.ttf"))
    {
        return -1;
    }
    sf::Text blinkingText("Press ENTER to burn the city", font, 30);
    blinkingText.setFillColor(sf::Color::White);
    sf::Clock clock;
    Menu      menu;
    Music     music;

    // Sprite samuraiLogo;
    // Sprite samuraiTitle;
    // Music  music;
    // if (!samuraiLogo
    //          .load("../assets/MainMenu/samuraiLogo.png", sf::Vector2u(260, 299), window.getSize().x / 2 - 260 / 2, 50, 128, 147))
    //     return -1;
    // if (!samuraiTitle.load("../assets/MainMenu/samuraiTitle.png",
    //                        sf::Vector2u(395, 53),
    //                        window.getSize().x / 2 - 395 / 2,
    //                        window.getSize().y / 1.5 - 53 / 2,
    //                        128,
    //                        18))
    //     return -1;
    //
    //
    // Button startButton(window,
    //                    sf::Vector2f(200, 50),
    //                    sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 160),
    //                    sf::Color::Black,
    //                    sf::Color::White,
    //                    2.0f,
    //                    "Play",
    //                    font,
    //                    20);
    //
    // Button exitButton(window,
    //                   sf::Vector2f(200, 50),
    //                   sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 230),
    //                   sf::Color::Black,
    //                   sf::Color::White,
    //                   2.0f,
    //                   "Exit",
    //                   font,
    //                   20);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //// main menu
        if (menu.onMenu)
        {
            if (music.playMenuMusic)
            {
                music.musicMenu.play();
                music.playMenuMusic = false;
            }
            // Récupérer le temps écoulé depuis le début de la boucle
            sf::Time elapsed = clock.getElapsedTime();
            // Changer la visibilité du texte toutes les 0.5 secondes (500 millisecondes)
            if (elapsed.asMilliseconds() > 500)
            {
                // Inverser la visibilité
                blinkingText.setFillColor(
                    blinkingText.getFillColor() == sf::Color::Transparent ? sf::Color::White : sf::Color::Transparent);
                // Réinitialiser le chrono
                clock.restart();
            }
            window.clear();
            window.draw(menu);
            window.draw(blinkingText);
            window.display();
        }
    }
}
