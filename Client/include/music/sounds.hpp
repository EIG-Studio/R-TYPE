/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** music
*/

#pragma once

#include "sprite/sprite.hpp"

#include <SFML/Audio.hpp>

#include <SFML/Window/Event.hpp>

class Music
{
public:
    Music();
    sf::Music musicMenu;
    sf::Music musicSecret;
    sf::Music shootSound;
    sf::Music boomEnemies;
    sf::Music killPlayer;
    bool playMenuMusic;
    void setPath(Sprite mSprite);
};
