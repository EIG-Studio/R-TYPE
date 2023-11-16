#include "menu/mainMenu/mainMenu.hpp"

#include "button.hpp"
#include "music/music.hpp"

#include <iostream>

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

    sf::Font font;
    if (!font.loadFromFile("../assets/Fonts/Roboto-Medium.ttf"))
    {
        return -1;
    }

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


    Button startButton(window,
                       sf::Vector2f(200, 50),
                       sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 160),
                       sf::Color::Black,
                       sf::Color::White,
                       2.0f,
                       "Play",
                       font,
                       20);

    Button exitButton(window,
                      sf::Vector2f(200, 50),
                      sf::Vector2f(window.getSize().x / 2 - 100, window.getSize().y / 2 + 230),
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
        }

        if (music.playMenuMusic)
        {
            music.musicMenu.play();
            music.playMenuMusic = false;
        }

        window.clear();
        window.draw(samuraiLogo);
        window.draw(samuraiTitle);
        startButton.draw();
        exitButton.draw();

        if (startButton.checkClick())
        {
            std::cout << "Button Play clicked" << std::endl;
        }
        if (exitButton.checkClick())
        {
            std::cout << "Button Exit clicked" << std::endl;
            exit(0);
        }

        window.display();
    }

    return 0;
}
