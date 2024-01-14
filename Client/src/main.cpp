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
    LobbyMenu& lobbyMenu,
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (menu.onMenu || choiceMenu.onChoice) && !sprite.easterEgg) {
            music.musicMenu.stop();
            sprite.setLogoPath("../Client/assets/MainMenu/runnerLogo.png");
            sprite.setTitlePath("../Client/assets/MainMenu/runnerTitle.png");
            sprite.setMainSongPath("../Client/assets/Songs/runner.wav");
            sprite.setBackPath("../Client/assets/Background/city_2/1.png");
            sprite.setVeryBackBuildPath("../Client/assets/Background/city_2/2.png");
            sprite.setBackBuildPath("../Client/assets/Background/city_2/3.png");
            sprite.setMidBuildPath("../Client/assets/Background/city_2/4.png");
            sprite.setFrontBuildPath("../Client/assets/Background/city_2/5.png");
            menu.setPath(sprite);
            choiceMenu.setPath(sprite);
            hostOrJoinMenu.setPath(sprite);
            lobbyMenu.setPath(sprite);
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


void initText(
    WindowManager& windowManager,
    InLoopGame& inLoopGame,
    sf::Text& fpsText,
    sf::Text& ipAddressText,
    sf::Text& youWinText,
    sf::Text& youLooseText,
    LobbyMenu& lobbyMenu,
    YouWinMenu& youWinMenu,
    YouLooseMenu& youLooseMenu)
{
    fpsText.setFont(windowManager.getFont());
    fpsText.setCharacterSize(15);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setOutlineColor(sf::Color::Black);
    fpsText.setOutlineThickness(1);
    fpsText.setPosition(10.0f, 10.0f);

    inLoopGame.scoreText.setFont(windowManager.getFont());
    inLoopGame.scoreText.setCharacterSize(24);
    inLoopGame.scoreText.setFillColor(sf::Color::White);
    inLoopGame.scoreText.setOutlineColor(sf::Color::Black);
    inLoopGame.scoreText.setOutlineThickness(1);
    inLoopGame.scoreText.setPosition(windowManager.getWindow().getSize().x / 2 - 50, windowManager.getWindow().getSize().y / 50);

    ipAddressText.setFont(windowManager.getFont());
    ipAddressText.setCharacterSize(24);
    ipAddressText.setFillColor(sf::Color::White);
    ipAddressText.setPosition(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 8);

    std::string ipAddress = getLocalIpAddress();
    ipAddressText.setString(ipAddress);
    lobbyMenu.setIpAdress(ipAddressText);

    youWinText.setFont(windowManager.getFont());
    youWinText.setCharacterSize(24);
    youWinText.setFillColor(sf::Color::White);
    youWinText.setPosition(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 8);
    youWinText.setString("You Win !");
    youWinMenu.setYouWinText(youWinText);

    youLooseText.setFont(windowManager.getFont());
    youLooseText.setCharacterSize(24);
    youLooseText.setFillColor(sf::Color::White);
    youLooseText.setPosition(windowManager.getWindow().getSize().x / 2 - 100, windowManager.getWindow().getSize().y / 8);
    youLooseText.setString("You Lose !");
    youLooseMenu.setYouLooseText(youLooseText);
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
    YouWinMenu youWinMenu;
    youWinMenu.setPath(sprite);
    YouLooseMenu youLooseMenu;
    youLooseMenu.setPath(sprite);

    int frameCount = 0;
    sf::Text fpsText;
    sf::Text ipAddressText;
    sf::Text youWinText;
    sf::Text youLooseText;
    initText(windowManager, inLoopGame, fpsText, ipAddressText, youWinText, youLooseText, lobbyMenu, youWinMenu, youLooseMenu);

    ButtonManager buttonManager(windowManager.getWindow(), windowManager.getFont());

    Registry registry = Registry();
    commandsToServer.asyncReceive(std::ref(registry), music, game, youWinMenu, youLooseMenu);
    while (windowManager.getWindow().isOpen()) {
        sf::Event event{};
        handleWindowEvents(event, windowManager, menu, choiceMenu, hostOrJoinMenu, lobbyMenu, game, sprite, music);
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
            youWinMenu,
            youLooseMenu,
            event,
            sprite,
            onGameClock,
            registry,
            ipAdress);
        windowManager.getWindow().draw(fpsText);
        windowManager.getWindow().display();
    }
}
