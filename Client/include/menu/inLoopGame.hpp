/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopGame
*/

#pragma once

#include "Systems.hpp"
#include "entities.hpp"
#include "menu/inGame.hpp"
#include "menu/inLoopMenus.hpp"
#include "window.hpp"
#include "ipAdress.hpp"

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
        Button& resumeButton,
        Button& toMenuButton,
        ChoiceMenu& choiceMenu,
        IpAdress& ipAdress);

private:
    void refreshRegistry(Registry &registry, CommandsToServer &commandsToServer, IpAdress& ipAdress);
    sf::Clock m_clock;
};
