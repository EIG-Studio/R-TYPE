#include <SFML/Graphics.hpp>
#include "../include/include.hpp"

int main()
{
    auto window = sf::RenderWindow{{800, 600}, "R-TYPE"};
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
