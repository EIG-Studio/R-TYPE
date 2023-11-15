#include <SFML/Graphics.hpp>

int main() {
  auto window = sf::RenderWindow{{1920, 1080}, "CMake SFML Project"};
  window.setFramerateLimit(144);

  while (window.isOpen()) {
    for (auto event = sf::Event{}; window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear();
    window.display();
  }
}
