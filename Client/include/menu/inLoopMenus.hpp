/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopMenus
*/

#pragma once

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
    void choiceMenuInLoop(
        WindowManager& windowManager,
        ChoiceMenu& choiceMenu,
        Button& playButton,
        Button& settingsButton,
        Button& exitButton,
        HostOrJoinMenu& hostOrJoinMenu,
        CommandsToServer& commandsToServer,
        SettingMenu& settingMenu);
    void settingsMenuInLoop(SettingMenu& settingMenu, WindowManager& windowManager, ChoiceMenu& choiceMenu, Button& retourButton);
    void hostOrJoinMenuInLoop(
        HostOrJoinMenu& hostOrJoinMenu,
        WindowManager& windowManager,
        ChoiceMenu& choiceMenu,
        Button& retourButton,
        Button& hostButton,
        Button& joinButton);
    void lobbyMenuInLoop(LobbyMenu& lobbyMenu, WindowManager& windowManager, ChoiceMenu& choiceMenu, Button& retourButton);

private:
};
