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
        //// Gestion de l'erreur si le chargement de l'icône échoue
        return -1;
    }
     window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //// main menu putain
    Menu menu;
    Music music;
    //// fin des sprite du main menu bordel (on peut pas mettre de svg mdr)

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (menu.onMenu) {
            if (music.play_menu_music == true) {
                music.music_menu.play();
                music.play_menu_music = false;
            }
            window.clear();
            window.draw(menu);
            window.display();
        }
    }
}
