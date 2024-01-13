/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** sprite
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>

#include <SFML/Window.hpp>

#include <SFML/System.hpp>

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
    void setPlayerPath(std::string mString);
    void setEnemyPath(std::string mString);
    void setBackPath(std::string mString);
    void setVeryBackBuildPath(std::string mString);
    void setBackBuildPath(std::string mString);
    void setMidBuildPath(std::string mString);
    void setFrontBuildPath(std::string mString);

    std::string getLogoPath();
    std::string getTitlePath();
    std::string getFontPath();
    std::string getBackPath();
    std::string getVeryBackBuildPath();
    std::string getBackBuildPath();
    std::string getMidBuildPath();
    std::string getFrontBuildPath();
    std::string getPlayerPath();
    std::string getEnemyPath();
    std::string getCursorPath();
    std::string getKillPlayerPath();

    std::string getMainSongPath();
    std::string getShootSoundPath();
    std::string getBoomEnemiesPath();

private:
    std::string m_pathLogo;
    std::string m_pathTitle;
    std::string m_pathFont;
    std::string m_pathCursor;
    std::string m_pathBack;
    std::string m_pathVeryBackBuild;
    std::string m_pathBackBuild;
    std::string m_pathMidBuild;
    std::string m_pathFrontBuild;

    std::string m_pathPlayer;
    std::string m_pathEnemy;

    std::string m_pathMainSong;
    std::string m_pathShootSound;
    std::string m_pathBoomEnemies;
    std::string m_pathKillPlayer;
};
