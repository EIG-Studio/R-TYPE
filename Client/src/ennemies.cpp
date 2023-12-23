/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ennemies
*/

#include "ennemies.hpp"

#include <SFML/Graphics.hpp>

void Ennemies::destroyEnnemy(float playerPosY, float ennemyPosY)
{
    std::cout << "PLAYER POS: " << playerPosY << std::endl;
    std::cout << "ENNEMY POS: " << ennemyPosY << std::endl;
    if (playerPosY <= ennemyPosY + 40 && playerPosY >= ennemyPosY - 15) {
        std::cout << "BOOM !!!!" << std::endl;
    }

    sf::Vertex line[] = {sf::Vertex(sf::Vector2f(10, ennemyPosY + 20)), sf::Vertex(sf::Vector2f(10, ennemyPosY - 30))};
}
