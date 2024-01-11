/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_
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
<<<<<<< HEAD
    sf::Music boomEnemies;
    sf::Music killPlayer;
    bool playMenuMusic;
    void setPath(Sprite mSprite);
=======
    bool      playMenuMusic;
    void      setPath(Sprite mSprite);
>>>>>>> refs/remotes/origin/Client

protected:

private:
};

#endif /* !MUSIC_HPP_ */
