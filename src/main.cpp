/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "GUI.hpp"
#include "music.hpp"
#include "menu.hpp"

int main()
{
    auto window = sf::RenderWindow{{800, 600}, "SAMURAI"};
    window.setFramerateLimit(144);
    sf::Image icon;
    if (!icon.loadFromFile("assets/MainMenu/samuraiLogo.png"))
    {
        return -1;
    }
     window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Menu menu;
    Music music;

    //// Ranger ça <
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/retro.ttf"))
    {
        std::cerr << "Erreur lors du chargement de la police." << std::endl;
        return EXIT_FAILURE;
    }
    sf::Text blinkingText("Press ENTER to burn the city", font, 30);
    blinkingText.setFillColor(sf::Color::White);
    //// clock
    sf::Clock clock;
    //// > Jusqu'ici

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //// main menu
        if (menu.onMenu) {
            if (music.play_menu_music == true) {
                music.music_menu.play();
                music.play_menu_music = false;
            }
            // Récupérer le temps écoulé depuis le début de la boucle
            sf::Time elapsed = clock.getElapsedTime();
            // Changer la visibilité du texte toutes les 0.5 secondes (500 millisecondes)
            if (elapsed.asMilliseconds() > 500)
            {
                // Inverser la visibilité
                blinkingText.setFillColor(blinkingText.getFillColor() == sf::Color::Transparent ? sf::Color::White : sf::Color::Transparent);
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
