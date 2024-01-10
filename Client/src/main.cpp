/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "commandsToServer.hpp"
#include "entities.hpp"
#include "menu/inGame.hpp"
#include "menu/inLoopGame.hpp"
#include "menu/inLoopMenus.hpp"
#include "menu/menus.hpp"
#include "music/sounds.hpp"
#include "sprite/sprite.hpp"
#include "window.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <SFML/System.hpp>

#include <boost/asio.hpp>

#include <cstdlib>

std::string getLocalIpAddress()
{
    boost::asio::io_service ioService;
    boost::asio::ip::udp::resolver resolver(ioService);

    boost::asio::ip::udp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::udp::resolver::iterator iter = resolver.resolve(query);

    while (iter != boost::asio::ip::udp::resolver::iterator()) {
        boost::asio::ip::udp::endpoint endpoint = *iter++;
        if (endpoint.address().is_v4()) {
            return endpoint.address().to_string();
        }
    }

    return "Failed to retrieve IP address";
}


void handleWindowEvents(
    sf::Event& event,
    WindowManager& windowManager,
    Menu& menu,
    ChoiceMenu& choiceMenu,
    HostOrJoinMenu& hostOrJoinMenu,
    Game& game,
    Sprite& sprite,
    Music& music)
{
    while (windowManager.getWindow().pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            windowManager.getWindow().close();
            exit(0);
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Joystick::isButtonPressed(0, 7)) && menu.onMenu) {
            menu.onMenu = false;
            choiceMenu.onChoice = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && menu.onMenu && !sprite.easterEgg) {
            music.musicMenu.stop();
            sprite.setLogoPath("../Client/assets/MainMenu/runnerLogo.png");
            sprite.setTitlePath("../Client/assets/MainMenu/runnerTitle.png");
            sprite.setMainSongPath("../Client/assets/Songs/runner.wav");
            menu.setPath(sprite);
            choiceMenu.setPath(sprite);
            hostOrJoinMenu.setPath(sprite);
            music.setPath(sprite);
            game.setPath(sprite);
            music.musicMenu.play();
            sprite.easterEgg = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && choiceMenu.onChoice && !sprite.easterEgg) {
            music.musicMenu.stop();
            sprite.setLogoPath("../Client/assets/MainMenu/runnerLogo.png");
            sprite.setTitlePath("../Client/assets/MainMenu/runnerTitle.png");
            sprite.setMainSongPath("../Client/assets/Songs/runner.wav");
            menu.setPath(sprite);
            choiceMenu.setPath(sprite);
            hostOrJoinMenu.setPath(sprite);
            music.setPath(sprite);
            game.setPath(sprite);
            music.musicMenu.play();
            sprite.easterEgg = true;
        }
    }
}

void updateFpsText(WindowManager& windowManager, sf::Text& fpsText, sf::Clock& clock, int& frameCount)
{
    windowManager.getWindow().clear();
    frameCount++;
    sf::Time elapsed = clock.getElapsedTime();
    if (elapsed.asMilliseconds() >= 1000) {
        float fps = static_cast<float>(frameCount) / elapsed.asSeconds();
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));

        frameCount = 0;
        clock.restart();
    }
}

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
    sf::Event& event,
    Sprite& sprite,
    sf::Clock& onGameClock,
    Registry& registry,
    IpAdress& ipAdress)
{
    if (menu.onMenu) {
        introMenu.introMenuInLoop(menu, windowManager, music, clock);
    } else if (choiceMenu.onChoice) {
        introMenu.choiceMenuInLoop(
            windowManager,
            choiceMenu,
            buttonManager.getPlayButton(),
            buttonManager.getSettingsButton(),
            buttonManager.getExitButton(),
            hostOrJoinMenu,
            settingMenu);
    } else if (hostOrJoinMenu.onHostOrJoin) {
        introMenu.hostOrJoinMenuInLoop(
            hostOrJoinMenu,
            windowManager,
            choiceMenu,
            lobbyMenu,
            game,
            commandsToServer,
            buttonManager.getRetourButton(),
            buttonManager.getHostButton(),
            buttonManager.getJoinButton(),
            event,
            ipAdress);
    } else if (lobbyMenu.onLobby) {
        introMenu.lobbyMenuInLoop(
            lobbyMenu,
            windowManager,
            hostOrJoinMenu,
            game,
            commandsToServer,
            buttonManager.getRetourButton(),
            buttonManager.getStartButton(),
            ipAdress);
    } else if (settingMenu.onSetting) {
        introMenu.settingsMenuInLoop(settingMenu, windowManager, choiceMenu, buttonManager.getRetourButton());
    } else if (game.onGame) {
        inLoopGame.gameInLoop(
            event,
            windowManager,
            game,
            music,
            commandsToServer,
            sprite,
            onGameClock,
            registry,
            buttonManager.getResumeButton(),
            buttonManager.getToMenuButton(),
            choiceMenu,
            ipAdress);
    }
}


void myLog(const std::string& message)
{
    std::cout << "[LOG] " << message << std::endl;
}

int main()
{
    WindowManager windowManager;
    windowManager.initWindow();
    InLoopMenus introMenu;
    InLoopGame inLoopGame;

    sf::Clock clock;
    sf::Clock onGameClock;
    CommandsToServer commandsToServer;
    IpAdress ipAdress;
    Sprite sprite;
    Menu menu;
    menu.setPath(sprite);
    ChoiceMenu choiceMenu;
    choiceMenu.setPath(sprite);
    HostOrJoinMenu hostOrJoinMenu;
    hostOrJoinMenu.setPath(sprite);
    LobbyMenu lobbyMenu;
    lobbyMenu.setPath(sprite);
    SettingMenu settingMenu;
    settingMenu.setPath(sprite);
    Game game;
    game.setPath(sprite);
    Music music;
    music.setPath(sprite);

    int frameCount = 0;
    sf::Text fpsText;
    fpsText.setFont(windowManager.getFont());
    fpsText.setCharacterSize(15);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.0f, 10.0f);

    sf::Text ipAddressText;
    ipAddressText.setFont(windowManager.getFont());
    ipAddressText.setCharacterSize(24);
    ipAddressText.setFillColor(sf::Color::White);
    ipAddressText.setPosition(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 8);

    std::string ipAddress = getLocalIpAddress();
    ipAddressText.setString(ipAddress);
    lobbyMenu.setIpAdress(ipAddressText);

    sf::Text text;
    text.setFont(windowManager.getFont());
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 2);
    hostOrJoinMenu.setInputText(text);

    ButtonManager buttonManager(windowManager.getWindow(), windowManager.getFont());

    Registry registry = Registry();
    commandsToServer.asyncReceiveSecondSocket(std::ref(registry), music);
    while (windowManager.getWindow().isOpen()) {
        sf::Event event{};
        handleWindowEvents(event, windowManager, menu, choiceMenu, hostOrJoinMenu, game, sprite, music);
        updateFpsText(windowManager, fpsText, clock, frameCount);
        menuChoice(
            menu,
            introMenu,
            windowManager,
            music,
            clock,
            choiceMenu,
            hostOrJoinMenu,
            lobbyMenu,
            buttonManager,
            game,
            commandsToServer,
            settingMenu,
            inLoopGame,
            event,
            sprite,
            onGameClock,
            registry,
            ipAdress);
        windowManager.getWindow().draw(fpsText);
        windowManager.getWindow().display();
    }
}
