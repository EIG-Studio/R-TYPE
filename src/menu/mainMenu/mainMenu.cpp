#include "menu/mainMenu/mainMenu.hpp"

#include "menu/mainMenu/mainMenuMusic.hpp"

int mainMenu()
{
    auto window = sf::RenderWindow{{800, 600}, "SAMURAI"};
    window.setFramerateLimit(144);
    sf::Image icon;
    if (!icon.loadFromFile("../assets/MainMenu/samuraiLogo.png"))
    {
        return -1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Sprite samuraiLogo;
    Sprite samuraiTitle;
    Music  music;
    if (!samuraiLogo
             .load("../assets/MainMenu/samuraiLogo.png", sf::Vector2u(260, 299), window.getSize().x / 2 - 260 / 2, 50, 128, 147))
        return -1;
    if (!samuraiTitle.load("../assets/MainMenu/samuraiTitle.png",
                           sf::Vector2u(395, 53),
                           window.getSize().x / 2 - 395 / 2,
                           window.getSize().y / 1.5 - 53 / 2,
                           128,
                           18))
        return -1;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (music.playMenuMusic)
        {
            music.musicMenu.play();
            music.playMenuMusic = false;
        }
        window.clear();
        window.draw(samuraiLogo);
        window.draw(samuraiTitle);
        window.display();
    }
    return 0;
}
