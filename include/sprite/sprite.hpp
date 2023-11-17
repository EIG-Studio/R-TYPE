/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#pragma once

#include "sfml.hpp"
#include <string>

class Sprite : public sf::Transformable
{
public:
    Sprite();
    ~Sprite() override = default;
    bool easterEgg;

    void setLogoPath(std::string mString);
    void setTitlePath(std::string mString);
    void setMainSongPath(std::string mString);

    std::string getLogoPath();
    std::string getTitlePath();
    std::string getFontPath();
    std::string getMainSongPath();

private:
    std::string m_pathLogo;
    std::string m_pathTitle;
    std::string m_pathFont;
    std::string m_pathMainSong;

};
