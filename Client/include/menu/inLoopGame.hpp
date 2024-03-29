/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopGame
*/

#pragma once

#include "entities.hpp"
#include "ipAdress.hpp"
#include "menu/inGame.hpp"
#include "menu/menus.hpp"
#include "window.hpp"

class InLoopGame
{

public:
    void gameInLoop(
        sf::Event& event,
        WindowManager& windowManager,
        Game& game,
        Music& music,
        CommandsToServer& commandsToServer,
        Sprite& sprite,
        sf::Clock& onGameClock,
        Registry& registry,
        ButtonManager& buttonManager,
        ChoiceMenu& choiceMenu,
        YouWinMenu& youWinMenu,
        YouLooseMenu& youLooseMenu,
        IpAdress& ipAdress);
    void updateScore(WindowManager& windowManager, Registry& registry);

    sf::Text scoreText;

private:
    void refreshRegistry(Registry& registry, CommandsToServer& commandsToServer, IpAdress& ipAdress);
    void pingServer(CommandsToServer& commandsToServer, IpAdress& ipAdress);
    sf::Clock m_clock;
    sf::Clock m_clock2;
};
