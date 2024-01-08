/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopMenus
*/

#pragma once

#include "button.hpp"
#include "commandsToServer.hpp"
#include "menu/inGame.hpp"
#include "menu/menus.hpp"
#include "music/sounds.hpp"
#include "window.hpp"

#include <SFML/System/Clock.hpp>
class InLoopMenus
{

public:
    void introMenuInLoop(Menu& menu, WindowManager& windowManager, Music& music, sf::Clock& clock);
    void settingsMenuInLoop(SettingMenu& settingMenu, WindowManager& windowManager, ChoiceMenu& choiceMenu, Button& retourButton);
    void choiceMenuInLoop(
        WindowManager& windowManager,
        ChoiceMenu& choiceMenu,
        Button& playButton,
        Button& settingsButton,
        Button& exitButton,
        Game& game,
        CommandsToServer& commandsToServer,
        SettingMenu& settingMenu);

private:
};
