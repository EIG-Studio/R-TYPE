/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "GUI.hpp"
#include "music.hpp"

int main()
{
    auto window = sf::RenderWindow{{800, 600}, "SAMURAI"};
    window.setFramerateLimit(144);
    sf::Image icon;
    if (!icon.loadFromFile("assets/MainMenu/samuraiLogo.png"))
    {
        // Gestion de l'erreur si le chargement de l'icône échoue
        return -1;
    }
     window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // main menu putain
    Sprite sprite;
    Sprite sprite2;
    Music music;
    if (!sprite.load(
            "assets/MainMenu/samuraiLogo.png", sf::Vector2u(260, 299), window.getSize().x / 2 - 260 / 2, 50, 128, 147))
        return -1;
    if (!sprite2.load(
            "assets/MainMenu/SamuraiTitle.png", sf::Vector2u(395, 53), window.getSize().x / 2 - 395 / 2, window.getSize().y / 1.5 -  53 / 2,  128, 18))
        return -1;
    // fin des sprite du main menu bordel (on peut pas mettre de svg mdr)

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (music.play_menu_music == true) {
            music.music_menu.play();
            music.play_menu_music = false;
        }
        window.clear();
        window.draw(sprite);
        window.draw(sprite2);
        window.display();
    }
}
