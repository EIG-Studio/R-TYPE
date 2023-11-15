#include "GUI.hpp"

int main()
{
    auto window = sf::RenderWindow{{800, 600}, "R-TYPE"};
    window.setFramerateLimit(144);

    // main menu putain
    Sprite sprite;
    Sprite sprite2;
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
        window.clear();
        window.draw(sprite);
        window.draw(sprite2);
        window.display();
    }
}
