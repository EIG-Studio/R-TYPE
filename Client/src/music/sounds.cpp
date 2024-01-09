/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** music
*/

#include "music/sounds.hpp"

Music::Music()
{
    this->playMenuMusic = true;
}

void Music::setPath(Sprite mSprite)
{
    if (!this->musicMenu.openFromFile(mSprite.getMainSongPath()))
    {
        std::cout << "Music not found" << std::endl;
    }
}
