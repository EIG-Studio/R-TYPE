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
#include "window.hpp"

class InLoopGame
{

public:
    void gameInLoop(
        sf::Event& event,
        WindowManager& windowManager,
        Game& game,
        CommandsToServer& commandsToServer,
        Sprite& sprite,
        sf::Clock& onGameClock,
        Registry& registry,
        Button& resumeButton,
        Button& toMenuButton);

private:
};
