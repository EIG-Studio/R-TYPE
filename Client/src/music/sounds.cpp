/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** music
*/

#include "music/sounds.hpp"

#include <iostream>

Music::Music()
{
    this->playMenuMusic = true;
}

void Music::setPath(Sprite mSprite)
{
    if (!this->musicMenu.openFromFile(mSprite.getMainSongPath())) {
        std::cout << "Music not found" << std::endl;
    }
    if (!this->shootSound.openFromFile(mSprite.getShootSoundPath())) {
        std::cout << "Shoot sound not found" << std::endl;
    }
    if (!this->boomEnemies.openFromFile(mSprite.getBoomEnemiesPath())) {
        std::cout << "Boom sound not found" << std::endl;
    }
    if (!this->killPlayer.openFromFile(mSprite.getKillPlayerPath())) {
        std::cout << "Boom sound not found" << std::endl;
    }
}