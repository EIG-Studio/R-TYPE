/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** music
*/

#include "music.hpp"

Music::Music()
{
    this->play_menu_music = true;
    if (!this->music_menu.openFromFile("assets/Songs/SAMURAI_Never-Fade-Away_instru.wav")) {
        std::cout << "Music not found" << std::endl;
    }
}