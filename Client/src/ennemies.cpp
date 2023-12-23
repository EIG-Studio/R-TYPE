/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ennemies
*/

#include "ennemies.hpp"

void Ennemies::destroyEnnemy(float playerPosY, float ennemyPosY)
{
    std::cout << "PLAYER POS: " << playerPosY << std::endl;
    std::cout << "ENNEMY POS: " << ennemyPosY << std::endl;
    if (playerPosY <= ennemyPosY + 20 && playerPosY >= ennemyPosY - 30) {
        std::cout << "BOOM !!!!" << std::endl;
    }
}
