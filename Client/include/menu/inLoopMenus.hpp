/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopMenus
*/

#pragma once

#include "commandsToServer.hpp"
#include "inGame.hpp"
#include "inLoopGame.hpp"
#include "menus.hpp"
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
        SettingMenu& settingMenu,
        Music& music);
    void settingsMenuInLoop(SettingMenu& settingMenu, WindowManager& windowManager, ChoiceMenu& choiceMenu, ButtonManager& buttonManager);
    void hostOrJoinMenuInLoop(
        HostOrJoinMenu& hostOrJoinMenu,
        WindowManager& windowManager,
        ChoiceMenu& choiceMenu,
        LobbyMenu& lobbyMenu,
        Game& game,
        CommandsToServer& commandsToServer,
        ButtonManager& buttonManager,
        sf::Event& event,
        IpAdress& ipAdress);
    void lobbyMenuInLoop(
        LobbyMenu& lobbyMenu,
        WindowManager& windowManager,
        HostOrJoinMenu& hostOrJoinMenu,
        Game& game,
        Sprite& sprite,
        CommandsToServer& commandsToServer,
        ButtonManager& buttonManager,
        IpAdress& ipAdress);
    void youWinMenuInLoop(YouWinMenu& youWin, WindowManager& windowManager, ChoiceMenu& choiceMenu, ButtonManager& buttonManager);
    void youLooseMenuInLoop(YouLooseMenu& youLoose, WindowManager& windowManager, ChoiceMenu& choiceMenu, ButtonManager& buttonManager);

private:
};

void menuChoice(
    Menu& menu,
    InLoopMenus& introMenu,
    WindowManager& windowManager,
    Music& music,
    sf::Clock& clock,
    ChoiceMenu& choiceMenu,
    HostOrJoinMenu& hostOrJoinMenu,
    LobbyMenu& lobbyMenu,
    ButtonManager& buttonManager,
    Game& game,
    CommandsToServer& commandsToServer,
    SettingMenu& settingMenu,
    InLoopGame& inLoopGame,
    YouWinMenu& youWinMenu,
    YouLooseMenu& youLooseMenu,
    sf::Event& event,
    Sprite& sprite,
    sf::Clock& onGameClock,
    Registry& registry,
    IpAdress& ipAdress);
