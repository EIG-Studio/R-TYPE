/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** music
*/

#include "menu/mainMenu/mainMenuMusic.hpp"

Music::Music()
{
    this->playMenuMusic = true;
    if (!this->musicMenu.openFromFile("../assets/Songs/SAMURAI_Never-Fade-Away_instru.wav"))
    {
        std::cout << "Music not found" << std::endl;
    }
}
