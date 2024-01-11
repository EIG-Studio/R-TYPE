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
        ButtonManager& buttonManager,
        HostOrJoinMenu& hostOrJoinMenu,
        SettingMenu& settingMenu);
    void settingsMenuInLoop(SettingMenu& settingMenu, WindowManager& windowManager, ChoiceMenu& choiceMenu, Button& retourButton);
    void hostOrJoinMenuInLoop(
        HostOrJoinMenu& hostOrJoinMenu,
        WindowManager& windowManager,
        ChoiceMenu& choiceMenu,
        LobbyMenu& lobbyMenu,
        Game& game,
        CommandsToServer& commandsToServer,
        ButtonManager &buttonManager,
        sf::Event& event,
        IpAdress& ipAdress);
    void lobbyMenuInLoop(
        LobbyMenu& lobbyMenu,
        WindowManager& windowManager,
        HostOrJoinMenu& hostOrJoinMenu,
        Game& game,
        CommandsToServer& commandsToServer,
        Button& retourButton,
        Button& startButton,
        IpAdress& ipAdress);

private:
};
