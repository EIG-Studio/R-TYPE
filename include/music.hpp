/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_
#include <SFML/Audio.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

class Music {
    public:
        Music();
        sf::Music music_menu;
        sf::Music music_secret;
        bool play_menu_music;
        //void HandleMusicKey(sf::Event &event);

    protected:

    private:
};

#endif /* !MUSIC_HPP_ */