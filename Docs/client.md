# Client

### This is a technique documentation for explain the differents tools offered by the Client

# Link to other documentation

* **You can find more information about the project [here](https://github.com/EpitechPromo2026/B-CPP-500-BDX-5-2-rtype-jules.trolle/wiki).**
* **You can find more technical information about the GameEngine [here](gameEngine.md).**
* **You can find more technical information about the Server [here](server.md).**

# Tables of Contents

- [Function `main`](#function-main)
  - [Main loop](#main-loop)
  - [End of Application](#end-of-application)
- [Function `getLocalIpAddress`](#function-getlocalipaddress)
- [Function `handleWindowEvents`](#function-handlewindowevents)
- [Function `updateFpsText`](#function-updatefpstext)
- [Function `menuChoice`](#function-menutoice)
- [Class `WindowManager`](#class-windowmanager)
  - [Method `initWindow`](#method-initwindow)
  - [Method `getFont`](#method-getfont)
  - [Method `getIcon`](#method-geticon)
  - [Method `getWindow`](#method-getwindow)
  - [Method `getMovementSpeed`](#method-getmovementspeed)
  - [Method `getMillisecondsPerSecond`](#method-getmillisecondspersecond)
  - [Method `getMillisecondsPerFrame`](#method-getmillisecondsperframe)
- [Function `split(const std::string& s, char delim)`](#function-split)
- [Function `handleReceive`](#function-handlereceive)
- [Function `sendToServer`](#function-sendtoserver)
- [Function `asyncReceiveSecondSocket`](#function-asyncreceivesecondsocket)
- [Function `getNewPos`](#function-getnewpos)
- [Class `Button`](#class-button)
  - [Constructor](#constructor)
  - [Method `checkClick`](#method-checkclick)
  - [Method `checkHover`](#method-checkhover)
  - [Method `draw`](#method-draw)
  - [Method `setText`](#method-settext)
  - [Method `setPosition`](#method-setposition)
  - [Method `setSize`](#method-setsize)
- [Function `updateSpriteTexture`](#function-updatespritetexture)
- [Function `updateSpritePositionAndPath`](#function-updatespritepositionandpath)
- [Function `movePlayer`](#function-moveplayer)
- [Function `InputTypeToString`](#function-inputtypetostring)
- [Function `HandleMovement`](#function-handlemovement)
- [Function `SendInputUpdate`](#function-sendinputupdate)
- [Function `shooting`](#function-shooting)
- [Function `damageToPlayer`](#function-damagetoplayer)
- [Function `displayArrow`](#function-displayarrow)
- [Function `setPath`](#function-setpath)
- [Function `Menu::setPath`](#function-menusetpath)
- [Function `Menu::blinkingText`](#function-menublinkingtext)
- [Function `Menu::draw`](#function-menudraw)
- [Function `ChoiceMenu::setPath`](#function-choicemenusetpath)
- [Function `ChoiceMenu::setCursorPosition`](#function-choicemenusetcursorposition)
- [Function `ChoiceMenu::draw`](#function-choicemenudraw)
- [Function `SettingMenu::setPath`](#function-settingmenusetpath)
- [Function `SettingMenu::setCursorPosition`](#function-settingmenusetcursorposition)
- [Function `SettingMenu::draw`](#function-settingmenudraw)
- [Function `HostOrJoinMenu::setPath`](#function-hostorjoinmenusetpath)
- [Function `HostOrJoinMenu::setCursorPosition`](#function-hostorjoinmenusetcursorposition)
- [Function `HostOrJoinMenu::inputText`](#function-hostorjoinmenuinputtext)
- [Function `HostOrJoinMenu::draw`](#function-hostorjoinmenudraw)
- [Function `LobbyMenu::setPath`](#function-lobbymenusetpath)
- [Function `LobbyMenu::setCursorPosition`](#function-lobbymenusetcursorposition)
- [Function `LobbyMenu::draw`](#function-lobbymenudraw)
- [Function `introMenuInLoop`](#function-intromenuinloop)
- [Function `choiceMenuInLoop`](#function-choicemenuinloop)
- [Function `settingsMenuInLoop`](#function-settingsmenuinloop)
- [Function `hostOrJoinMenuInLoop`](#function-hostorjoinmenuinloop)
- [Function `lobbyMenuInLoop`](#function-lobbymenuinloop)
- [Function `menuChoice`](#function-menuchoice)
- [Function `updateScore`](#function-updatescore)
- [Function `refreshRegistry`](#function-refreshregistry)
- [Function `pingServer`](#function-pingserver)
- [Function `gameInLoop`](#function-gameinloop)
- [Function `Game::setPath`](#function-gamesetpath)
- [Function `moveParallax`](#function-moveparallax)
- [Function `repeatParallax`](#function-repeatparallax)
- [Function `isPaused`](#function-ispaused)
- [Function `setCursorPosition`](#function-setcursorposition)
- [Function `Game::draw`](#function-gamedraw)
- [Function `displayHealth`](#function-displayhealth)

## Function `main`

The main Function of the application which initializes the different components and manages the main loop of the game.

The Function begins by initializing several objects necessary for the operation of the application. This includes the window manager `WindowManager`, menus, Clocks, commands to the server, IP address, sprite, and other elements.

### Main loop
```cpp
int frameCount = 0;
sf::Text fpsText;
// ... (initializing text and other elements)

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
```
The main loop is responsible for keeping the application running. At each iteration, it handles window events, updates the FPS text, makes menu choices in Function of the current state, and draws the text on the SFML window.

### End of Application

Once the SFML window is closed, the application exits the main loop and terminates.

## Function `getLocalIpAddress`

This Function uses Boost.Asio to retrieve the local IP address of the machine.

### Example of use
```cpp
std::string ipAddress = getLocalIpAddress();
```

## Function `handleWindowEvents`

This Function handles SFML window events, such as window closing, keyboard hits, etc.

### Example of use :
```cpp
sf::Event event;
handleWindowEvents(event, windowManager, menu, choiceMenu, hostOrJoinMenu, game, sprite, music);
```

## Function `updateFpsText`

This Function updates the text displaying the number of frames per second (FPS) on the SFML window.

### Example of use :
```cpp
sf::Text fpsText;
sf::Clock clock;
int frameCount = 0;
updateFpsText(windowManager, fpsText, clock, frameCount);
```

## Function `menuChoice`

This Function manages the different menus of the application Depending on the current state.

### Example of use :
```cpp
menuChoice(menu, introMenu, windowManager, music, clock, choiceMenu, hostOrJoinMenu, lobbyMenu, buttonManager, game, commandsToServer, settingMenu, inLoopGame, event, sprite, onGameClock, registry, ipAdress);
```

## Class `WindowManager`

The `WindowManager` class is responsible for initializing the SFML window and provides methods for accessing elements such as the font, the icon, the window itself, and motion and time Settings.

### Method `initWindow`

This method initializes the SFML window with default Settings. It also configures the movement speed, the maximum FPS, and loads the window icon and the font used in the application.

#### Example of use
```cpp
int result = initWindow();
if (result == -1) {
    // Handle error during window initialization
}
```
### Method `getFont`

This method returns the `sf::Font` font used in the application.

#### Example of use :
```cpp
sf::Font& font = getFont();
```

### Method `getIcon`

This method returns the window's `sf::Image` icon.

#### Example of use :
```cpp
sf::Image& icon = getIcon();
```

### Method `getWindow`

This method returns the SFML window itself `sf::RenderWindow`.

#### Example of use :
```cpp
sf::RenderWindow& window = getWindow();
```

### Method `getMovementSpeed`

This method returns the current movement speed configured in the class.

#### Example of use :
```cpp
float speed = getMovementSpeed();
```

### Method `getMillisecondsPerSecond`

This method returns the number of milliseconds per second used in calculating time.

#### Example of use :
```cpp
float msPerSecond = getMillisecondsPerSecond();
```

### Method `getMillisecondsPerFrame`

This method returns the number of milliseconds per frame used in the time calculation.

#### Example of use :
```cpp
float msPerFrame = getMillisecondsPerFrame();
```

## Function `split(const std::string& s, char delim)`

This Function splits a string according to a delimiter and returns a vector of resulting substrings.

### Example of use :
```cpp
std::vector<std::string> result = split("Texte à diviser", '|');
```

## Function `handleReceive`

The `handleReceive` Function is responsible for processing data received from the network. It supports multiple command types and updates the `Registry` data structure accordingly.

### Constructor
```cpp
void handleReceive(
    Registry& registry,
    const boost::system::error_code& error,
    size_t len,
    unsigned char buffer[sizeof(TransferData)],
    std::string& mNewPos,
    Music& music);
```

### Settings :

- `registry`: A reference to the data structure (Registry) that stores game entities.
- `error`: A boost::system::error_code object that indicates if there was an error receiving data.
- `len`: The size of the data received.
- `buffer`: The buffer containing the received data.
- `mNewPos`: A reference to a character string storing the last position received.
- `music`: An object of the Music class that manages the playback of audio files.

### operation :

The Function starts by checking if there was an error during data reception or if no data was received (non-blocking case). If so, it carries out appropriate management.

On successful reception and non-empty data, it uses a `TransferData` data structure to interpret the commands and associated arguments.

`NEW_POS` command
If the command is `NEW_POS`, the Function extracts the ID, position X and position Y of the entity from the data packet. It then updates the position of the corresponding entity in the `Registry` data structure.

`NEW_PLAYER` command
If the command is NEW_PLAYER`, the Function creates a new player entity with the provided ID and position. It also adds components such as position, rendering, type, and size to this entity.

`NEW_ENEMY` command
If the command is `NEW_ENEMY`, the Function creates a new enemy entity with the provided ID and position. It adds components similar to those of the player.

`PLAYER_PROJECTILE` command
If the command is `PLAYER_PROJECTILE`, the Function creates a new player projectile entity with the provided ID and position.

`DELETE` command
If the command is `DELETE`, the Function deletes a specified entity from the `Registry` data structure.

`PLAY_BOOM_ENEMIES` command
If the command is PLAY_BOOM_ENEMIES, the Function triggers the playback of a sound effect (boomEnemies) via the Music object.

### Errors :

If an error occurs during data reception or processing, the Function prints an appropriate error message to the console.

### Example of use :
```cpp
handleReceive(registry, error, len, buffer, mNewPos, music);
```

## Function `sendToServer`

This Function sends data to the server via a network socket. It converts a string into a `TransferData` data structure and sends this data to the server.

### Example of use :
```cpp
sendToServer(socket, "Commande à envoyer", ipAdress);
```

## Function `asyncReceiveSecondSocket`

This method uses asynchronicity to continually receive network data over a socket. It uses a mutex to ensure secure handling of shared data.

### Example of use :
```cpp
asyncReceiveSecondSocket(registry, music);
```

## Function `getNewPos`

This method returns the latest version of the position of each entity received.

### Example of use :
```cpp
std::string newPos = getNewPos();
```

## Class `Button`

The `Button` class represents a graphical button in an SFML user interface. It includes Features such as creation, positioning, click verification, and rendering.

#### Constructor :
```cpp
Button(
    const sf::Vector2f& size,
    const sf::Vector2f& position,
    const sf::Color& fillColor,
    const sf::Color& outlineColor,
    float outlineThickness,
    const std::string& text,
    const sf::Font& font,
    unsigned characterSize);
```

#### Settings :

- `size`: Taille du bouton.
- `position`: Position du coin supérieur gauche du bouton.
- `fillColor`: Couleur de remplissage du bouton.
- `outlineColor`: Couleur du contour du bouton.
- `outlineThickness`: Épaisseur du contour du bouton.
- `text`: Texte à afficher sur le bouton.
- `font`: Police utilisée pour le texte.
- `characterSize`: Taille du texte.

#### operation :

The constructor initializes the `m_shape` and the `m_label` of the button with the provided Settings. It also positions the text in the center of the button depending on size and position.

### Method `checkClick`

#### Constructor
```cpp
bool checkClick(float cursorX, float cursorY);
```

#### Settings :

- `cursorX`: X Position of the cursor.
- `cursorY`: Y position of the cursor.

#### operation :

This method checks whether the cursor is over the button and whether the mouse button (or a joystick button) is pressed. If these conditions are met and the button has not already been clicked recently, it returns `true` and marks the button as "clicked" to avoid repeated clicks.
### Method `checkHover`

#### Constructor :
```cpp
bool checkHover(float cursorX, float cursorY);
```

#### Settings :

- `cursorX`: X Position of the cursor.
- `cursorY`: Y position of the cursor.

#### operation :

This method checks whether the cursor is on the button. If so, it changes the color of the button's outline to indicate that it has been hovered over.

### Method `draw`

#### Constructor :
```cpp
void draw(sf::RenderWindow& window) const;
```

#### Settings :

- `window`: SFML window on which the button is to be drawn.

#### operation :

This method draws the `m_shape` and `m_label` of the button on the SFML window provided.

### Method `setText`

#### Constructor :
```cpp
void setText(const std::string& text);
```

#### Settings :

- text`: New text to be displayed on the button.

#### operation

This method updates the text displayed on the button.

### Method `setPosition`

#### Constructor
```cpp
void setPosition(const sf::Vector2f& position);
```

#### Settings :

- position`: New position for the upper left corner of the button.

#### operation :

This method updates the position of the button and repositions the text in the center of the button accordingly.

### Method `setSize`

#### Constructor :
```cpp
void setSize(const sf::Vector2f& size);
```

#### Settings :

- size`: New button size.

#### operation

This method updates the button size and repositions the text in the center of the button accordingly.

## Function `updateSpriteTexture`

###  Constructor :
```cpp
void updateSpriteTexture(sf::Sprite& sprite, const std::string& texturePath);
```

This function updates a sprite's texture using a cache memory to optimize texture loading performance.

### Settings :

- `sprite`: Reference to an `sf::Sprite` object whose texture is to be updated.
- `texturePath`: Path to texture file.

### Example of use :
```cpp
sf::Sprite mySprite;
updateSpriteTexture(mySprite, "chemin/vers/ma_texture.png");
```

## Function `updateSpritePositionAndPath`

### Constructor :
```cpp
void updateSpritePositionAndPath(sf::Sprite& sprite, float newX, float newY, const std::string& texturePath);
```

This function updates the position and texture of a sprite.

### Settings :

- `sprite`: Reference to an `sf::Sprite` object whose position and texture are to be updated.
- `newX`, `newY`: New X and Y coordinates of the sprite.
- `texturePath`: Path to texture file.

### Example of use :
```cpp
sf::Sprite mySprite;
updateSpritePositionAndPath(mySprite, 100.0f, 150.0f, "chemin/vers/ma_texture.png");
```

## Function `movePlayer`

### Constructor :
```cpp
void Game::movePlayer(Registry& registry, float movementSpeed, float winX, float winY, CommandsToServer& commandsToServer, Sprite mSprite, IpAdress& ipAdress);
```

This Function manages the player's movement according to the function of the keyboard keys and updates the necessary information.

### Settings :

- registry`: Reference to the `Registry` object containing game entities.
- `movementSpeed`: Player movement speed.
- `winX, winY`: Dimensions of the game window.
- `commandsToServer`: Reference to the `CommandsToServer` object for sending commands to the server.
- mSprite`: Player `sprite`.
- `ipAdress`: Server IP address.

### Example of use :
```cpp
Registry myRegistry;
float speed = 5.0f;
float windowWidth = 800.0f;
float windowHeight = 600.0f;
CommandsToServer serverCommands;
Sprite playerSprite;
IpAdress serverIp;

Game::movePlayer(myRegistry, speed, windowWidth, windowHeight, serverCommands, playerSprite, serverIp);
```

## Function `InputTypeToString`

### Constructor :
```cpp
std::string Game::InputTypeToString(sf::Keyboard::Key key);
```

This Function converts a key on the keyboard into a character string representing the type of input.

### Settings :

- key`: Keyboard key `sf::Keyboard::Key` to convert.

### Example of use :
```cpp
sf::Keyboard::Key myKey = sf::Keyboard::Up;
std::string inputString = InputTypeToString(myKey);
```

## Function `HandleMovement`

### Constructor :
```cpp
void Game::HandleMovement(
    Registry& registry,
    sf::Keyboard::Key key,
    CommandsToServer& commandsToServer,
    float movementSpeed,
    float deltaX,
    float deltaY,
    const std::string& path,
    float windowLimit,
    float spriteLimit,
    IpAdress& ipAdress);
```

This Function manages the player's movement according to keyboard keystrokes, sends updates to the server, and updates the player's sprite position.

### Settings :

- `registry`: Reference to the `Registry` object containing game entities.
- `key` : Keyboard key `sf::Keyboard::Key` that is pressed.
- `commandsToServer` : Reference to the `CommandsToServer` object for sending commands to the server.
- `movementSpeed` : Player movement speed.
- `deltaX`: Displacement in pixels along the X axis.
- `deltaY` : Displacement in pixels along the Y axis.
- `path`: `Path` to player sprite texture file.
- `windowLimit`: Limit of the game window, used to prevent overrun.
- `spriteLimit`: Limit of player sprite, used to avoid edge overrun.
- `ipAdress`: Reference to the `IpAdress` object representing the server's IP address.

### Example of use :
```cpp
Registry myRegistry;
CommandsToServer myCommands;
IpAdress serverIp;
sf::Keyboard::Key myKey = sf::Keyboard::Right;
float speed = 5.0f;
float delta = 1.0f;
std::string texturePath = "chemin/vers/ma_texture.png";
float windowWidth = 800.0f;
float windowHeight = 600.0f;

Game::HandleMovement(myRegistry, myKey, myCommands, speed, delta, delta, texturePath, windowWidth, windowHeight, serverIp);
```

## Function `SendInputUpdate`

### Constructor :
```cpp
void Game::SendInputUpdate(CommandsToServer& commandsToServer, Registry& registry, const std::string& inputType, IpAdress& ipAdress);
```

This Function sends an input update to the server.

### Settings :

- `CommandsToServer` : Reference to the `CommandsToServer` object for sending commands to the server.
- `registry` : Reference to the `Registry` object containing the game entities.
- `inputType` : String representing the input type (for example, "UP", "DOWN", "LEFT", "RIGHT").
- `ipAdress` : Reference to the `IpAdress` object representing the server's IP address.

### Example of use :
```cpp
CommandsToServer myCommands;
Registry myRegistry;
IpAdress serverIp;
std::string inputType = "UP";
Game::SendInputUpdate(myCommands, myRegistry, inputType, serverIp);
```

## Function `shooting`

### Constructor :
```cpp
void Game::shooting(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress);
```

This Function sends a firing command to the server.

### Settings :

- `commandsToServer` : Reference to the `CommandsToServer` object for sending commands to the server.
- `registry` : Reference to the `Registry` object containing the game entities.
- `ipAdress` : Reference to the `IpAdress` object representing the server's IP address.

### Example of use :
```cpp
CommandsToServer myCommands;
Registry myRegistry;
IpAdress serverIp;
Game::shooting(myCommands, myRegistry, serverIp);
```

## Function `damageToPlayer`

### Constructor :
```cpp
void Game::damageToPlayer(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress);
```

This Function sends a damage command to the server.

### Settings :

- `commandsToServer` : Reference to the `CommandsToServer` object for sending commands to the server.
- `registry` : Reference to the `Registry` object containing the game entities.
- `ipAdress` : Reference to the `IpAdress` object representing the server's IP address.

### Example of use :
```cpp
CommandsToServer myCommands;
Registry myRegistry;
IpAdress serverIp;
Game::damageToPlayer(myCommands, myRegistry, serverIp);
```

## Function `displayArrow`

### Constructor :
```cpp
void Game::displayArrow(Registry& registry, WindowManager& windowManager);
```

This Function displays an arrow above the player in the window.

### Settings :

- `registry` : Reference to the `Registry` object containing the game entities.
- `windowManager` : Reference to the `WindowManager` object representing game window management.


### Example of use :
```cpp
Registry myRegistry;
WindowManager myWindowManager;
Game::displayArrow(myRegistry, myWindowManager);
```

## Function `setPath`

### Constructor :
```cpp
void Music::setPath(Sprite mSprite);
```

This Function configures sound file paths for different game actions, using paths specified in a `Sprite` object.

### Settings :

- `mSprite`: Object of the `Sprite` class containing the paths to sound files.

### Example of use :
```cpp
Sprite mySprite;  // Make sure mySprite is correctly initialized with the sound file paths.
Music myMusic;
myMusic.setPath(mySprite);
```

## Function `Menu::setPath`

### Constructor :
```cpp
void Menu::setPath(Sprite mSprite);
```

This Function configures the textures, sprites and texts associated with the menu using the paths specified in a `Sprite` object.

### Settings :

- `mSprite` : Object of class `Sprite` containing paths for textures, sprites and fonts.

### Example of use :
```cpp
Sprite mySprite;  // Make sure mySprite is correctly initialized with texture and font paths.
Menu myMenu;
myMenu.setPath(mySprite);
```

## Function `Menu::blinkingText`

### Constructor :
```cpp
sf::Clock Menu::blinkingText(sf::Clock mClock, sf::Time mElapsed);
```

This function controls the flashing of the text "Press ENTER to burn the city".

### Settings :

- `mClock`: SFML clock used to measure the time between flashes.
- `mElapsed`: Time elapsed since the last flash.

### Example of use :
```cpp
sf::Clock myClock;
sf::Time elapsedTime = ...;  // Update with the time elapsed since the last frame.
myClock = myMenu.blinkingText(myClock, elapsedTime);
```

## Function `Menu::draw`

### Constructor :
```cpp
void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

This Function draws menu items on the rendering window.

### Settings :

- `target` : Reference to the `sf::RenderTarget` object on which to draw.
- `states` : SFML rendering state.

### Example of use :
```cpp
sf::RenderWindow window;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
Menu myMenu;
window.draw(myMenu);  // Appelle la Function draw de la classe Menu pour dessiner les éléments.
```

## Function `ChoiceMenu::setPath`

### Constructor :
```cpp
void ChoiceMenu::setPath(Sprite mSprite);
```

This Function configures the textures, sprites and texts associated with the menu choice using the paths specified in a `Sprite` object.

### Settings :

- `mSprite`: Object of the `Sprite` class containing paths for textures, sprites and fonts.

### Example of use :
```cpp
Sprite mySprite;  // Make sure mySprite is correctly initialized with texture and font paths.
ChoiceMenu myChoiceMenu;
myChoiceMenu.setPath(mySprite);
```

## Function `ChoiceMenu::setCursorPosition`

### Constructor :
```cpp
void ChoiceMenu::setCursorPosition(sf::RenderWindow& window);
```

This function controls the position of the cursor in the Function menu using the mouse and joystick.

### Settings :

- `window` : Reference to SFML window.

### Example of use :
```cpp
sf::RenderWindow myWindow;  // Make sure your SFML window is correctly initialized.
ChoiceMenu myChoiceMenu;
myChoiceMenu.setCursorPosition(myWindow);
```

## Function `ChoiceMenu::draw`

### Constructor :
```cpp
void ChoiceMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

This Function draws menu items on the rendering window.

### Settings :

- `target` : Reference to the `sf::RenderTarget` object on which to draw.
- `states` : SFML rendering state.

### Example of use :
```cpp
sf::RenderWindow window;  // Make sure your SFML window is correctly initialized.
ChoiceMenu myChoiceMenu;
window.draw(myChoiceMenu);  // Calls the draw function of the ChoiceMenu class to draw elements.
```

## Function `SettingMenu::setPath`

### Constructor :
```cpp
void SettingMenu::setPath(Sprite mSprite);
```

This Function configures the textures and sprites associated with the Settings menu using the paths specified in a `Sprite` object.

### Settings :

- `mSprite` : Sprite class object containing texture and sprite paths.

### Example of use :
```cpp
Sprite mySprite;  // Make sure mySprite is correctly initialized with texture paths.
SettingMenu mySettingMenu;
mySettingMenu.setPath(mySprite);
```

## Function `SettingMenu::setCursorPosition`

### Constructor :
```cpp
void SettingMenu::setCursorPosition(sf::RenderWindow& window);
```

This function controls the position of the cursor in the Function menu using the mouse and joystick.

### Settings :

- `window` : Reference to SFML window.

### Example of use :
```cpp
sf::RenderWindow myWindow;  // Make sure your SFML window is correctly initialized.
SettingMenu mySettingMenu;
mySettingMenu.setCursorPosition(myWindow);
```

## Function `SettingMenu::draw`

### Constructor :
```cpp
void SettingMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

This Function draws menu items on the rendering window.

### Settings :

- `target` : Reference to the `sf::RenderTarget` object on which to draw.
- `states` : SFML rendering state.

### Example of use :
```cpp
sf::RenderWindow window;  // Make sure your SFML window is correctly initialized.
SettingMenu mySettingMenu;
window.draw(mySettingMenu);  // Calls the draw function of the ChoiceMenu class to draw elements.
```

## Function `HostOrJoinMenu::setPath`

### Constructor :
```cpp
void HostOrJoinMenu::setPath(Sprite mSprite);
```

This Function configures the textures and sprites associated with the "Host or Join" menu using the paths specified in a `Sprite` object.

### Settings :

- `mSprite` : Sprite class object containing texture and sprite paths.

### Example of use :
```cpp
Sprite mySprite;  // Make sure mySprite is correctly initialized with texture paths.
HostOrJoinMenu myHostOrJoinMenu;
myHostOrJoinMenu.setPath(mySprite);
```

## Function `HostOrJoinMenu::setCursorPosition`

### Constructor :
```cpp
void HostOrJoinMenu::setCursorPosition(sf::RenderWindow& window);
```

This function controls the position of the cursor in the Function menu using the mouse and joystick.

### Settings :

- `window` : Reference to SFML window.

### Example of use :
```cpp
sf::RenderWindow myWindow;  // Make sure your SFML window is correctly initialized.
HostOrJoinMenu myHostOrJoinMenu;
myHostOrJoinMenu.setCursorPosition(myWindow);
```

## Function `HostOrJoinMenu::inputText`

### Constructor :
```cpp
void HostOrJoinMenu::inputText(sf::Event& event, IpAdress& ipAdress);
```

This Function supports text input for IP address entry.

### Settings :

- `event`: `sf::Event` object containing event information.
- `ipAdress` : `IpAdress` object to store the IP address entered.

### Example of use :
```cpp
sf::Event myEvent;  // Make sure myEvent is correctly initialized with the appropriate event.
IpAdress myIpAdress;  // Make sure myIpAdress is correctly initialized.
HostOrJoinMenu myHostOrJoinMenu;
myHostOrJoinMenu.inputText(myEvent, myIpAdress);
```

## Function `HostOrJoinMenu::draw`

### Constructor :
```cpp
void HostOrJoinMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

This Function draws menu items on the rendering window.

### Settings :

- `target` : Reference to the `sf::RenderTarget` object on which to draw.
- `states` : SFML rendering state.

### Example of use :
```cpp
sf::RenderWindow window;  // Make sure your SFML window is correctly initialized.
HostOrJoinMenu myHostOrJoinMenu;
window.draw(myHostOrJoinMenu);  // Calls the draw function of the ChoiceMenu class to draw elements.
```

## Function `LobbyMenu::setPath`

### Constructor :
```cpp
void LobbyMenu::setPath(Sprite mSprite);
```

This Function configures the textures and sprites associated with the "Lobby" menu using the paths specified in a `Sprite` object.

### Settings :

- `mSprite` : Object of class `Sprite` containing texture and sprite paths.

### Example of use :
```cpp
Sprite mySprite;  // Make sure mySprite is correctly initialized with texture paths.
LobbyMenu myLobbyMenu;
myLobbyMenu.setPath(mySprite);
```

## Function `LobbyMenu::setCursorPosition`

### Constructor :
```cpp
void LobbyMenu::setCursorPosition(sf::RenderWindow& window);
```

This function controls the position of the cursor in the lobby menu as a function of the mouse and joystick.

### Settings :

- `window` : Reference to SFML window.

### Example of use :
```cpp
sf::RenderWindow myWindow;  // Make sure your SFML window is correctly initialized.
LobbyMenu myLobbyMenu;
myLobbyMenu.setCursorPosition(myWindow);
```

## Function `LobbyMenu::draw`

### Constructor :
```cpp
void LobbyMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

This Function draws menu items on the rendering window.

### Settings :

- `target` : Reference to the `sf::RenderTarget` object on which to draw.
- `states` : SFML rendering state.

### Example of use :
```cpp
sf::RenderWindow window;  // Make sure your SFML window is correctly initialized.
LobbyMenu myLobbyMenu;
window.draw(myLobbyMenu);  // Calls the draw function of the ChoiceMenu class to draw elements.
```

## Function `introMenuInLoop`

### Constructor :
```cpp
void InLoopMenus::introMenuInLoop(Menu& menu, WindowManager& windowManager, Music& music, sf::Clock& clock);
```

This Function manages the logic of the introduction menu, including music playback and flashing text animation.

### Settings :

- `menu`: Reference to the `Menu` object representing the introductory menu.
- `windowManager`: Reference to the `WindowManager` object managing the SFML window.
- `music`: Reference to the `Music` object managing the menu music.
- `clock`: Reference to the `sf::Clock` object to measure time.

### Example of use :
```cpp
Menu myMenu; // Make sure myMenu is correctly initialized.
WindowManager myWindowManager; // Make sure myWindowManager is correctly initialized.
Music myMusic; // Make sure myMusic is correctly initialized.
sf::Clock myClock; // Make sure myClock is correctly initialized.
InLoopMenus::introMenuInLoop(myMenu, myWindowManager, myMusic, myClock);
```

## Function `choiceMenuInLoop`

### Constructor :
```cpp
void InLoopMenus::choiceMenuInLoop(
    WindowManager& windowManager,
    ChoiceMenu& choiceMenu,
    ButtonManager& buttonManager,
    HostOrJoinMenu& hostOrJoinMenu,
    SettingMenu& settingMenu);
```

This Function handles the logic of the choice menu, including hovering and clicking buttons.

### Settings :

- `windowManager`: Reference to the `WindowManager` object managing the SFML window.
- `choiceMenu`: Reference to the `ChoiceMenu` object representing the choice menu.
- `buttonManager`: Reference to the `ButtonManager` object managing the buttons.
- `hostOrJoinMenu`: Reference to the `HostOrJoinMenu` object representing the host or join menu.
- `settingMenu`: Reference to the `SettingMenu` object representing the Settings menu.

### Example of use :
```cpp
WindowManager myWindowManager; // Make sure myWindowManager is correctly initialized.
ChoiceMenu myChoiceMenu; // Make sure myChoiceMenu is properly initialized.
ButtonManager myButtonManager; // Make sure myButtonManager is correctly initialized.
HostOrJoinMenu myHostOrJoinMenu; // Make sure myHostOrJoinMenu is correctly initialized.
SettingMenu mySettingMenu; // Make sure mySettingMenu is correctly initialized.
InLoopMenus::choiceMenuInLoop(myWindowManager, myChoiceMenu, myButtonManager, myHostOrJoinMenu, mySettingMenu);
```

## Function `settingsMenuInLoop`

### Constructor :
```cpp
void InLoopMenus::settingsMenuInLoop(
    SettingMenu& settingMenu,
    WindowManager& windowManager,
    ChoiceMenu& choiceMenu,
    ButtonManager& buttonManager);
```

This function manages the Settings menu logic, including hovering and clicking the back button.

### Settings :

- `settingMenu`: Reference to the `SettingMenu` object representing the Settings menu.
- `windowManager`: Reference to the `WindowManager` object managing the SFML window.
- `choiceMenu`: Reference to the `ChoiceMenu` object representing the choice menu.
- `buttonManager`: Reference to the `ButtonManager` object managing the buttons.

## Function `hostOrJoinMenuInLoop`

### Constructor :
```cpp
void InLoopMenus::hostOrJoinMenuInLoop(
    HostOrJoinMenu& hostOrJoinMenu,
    WindowManager& windowManager,
    ChoiceMenu& choiceMenu,
    LobbyMenu& lobbyMenu,
    Game& game,
    CommandsToServer& commandsToServer,
    ButtonManager& buttonManager,
    sf::Event& event,
    IpAdress& ipAdress);
```

This Function manages the logic of the "Host or Join" menu, including cursor management, hovering and button clicking.

### Settings :

- `hostOrJoinMenu`: Reference to the `HostOrJoinMenu` object representing the “Host or Join” menu.
- `windowManager`: Reference to the `WindowManager` object managing the SFML window.
- `choiceMenu`: Reference to the `ChoiceMenu` object representing the choice menu.
- `lobbyMenu`: Reference to the `LobbyMenu` object representing the lobby menu.
- `game`: Reference to the `Game` object managing the game.
- `commandsToServer`: Reference to the `CommandsToServer` object for commands to the server.
- `buttonManager`: Reference to the `ButtonManager` object managing the buttons.
- `event`: Reference to the `sf::Event` object to manage events.
- `ipAdress`: Reference to the `IpAdress` object to manage the IP address.

### Example of use :
```cpp
HostOrJoinMenu myHostOrJoinMenu; // Make sure myHostOrJoinMenu is correctly initialized.
WindowManager myWindowManager; // Make sure myWindowManager is correctly initialized.
ChoiceMenu myChoiceMenu; // Make sure myChoiceMenu is properly initialized.
LobbyMenu myLobbyMenu; // Make sure myLobbyMenu is correctly initialized.
Game myGame; // Make sure myGame is correctly initialized.
CommandsToServer myCommandsToServer; // Make sure myCommandsToServer is correctly initialized.
ButtonManager myButtonManager; // Make sure myButtonManager is correctly initialized.
sf::Event myEvent; // Make sure myEvent is correctly initialized.
IpAddress myIpAddress; // Make sure myIpAddress is correctly initialized.
InLoopMenus::hostOrJoinMenuInLoop(myHostOrJoinMenu, myWindowManager, myChoiceMenu, myLobbyMenu, myGame, myCommandsToServer, myButtonManager, myEvent, myIpAdress);
```

## Function `lobbyMenuInLoop`

### Constructor :
```cpp
void InLoopMenus::lobbyMenuInLoop(
    LobbyMenu& lobbyMenu,
    WindowManager& windowManager,
    HostOrJoinMenu& hostOrJoinMenu,
    Game& game,
    Sprite& sprite,
    CommandsToServer& commandsToServer,
    ButtonManager& buttonManager,
    IpAdress& ipAdress);
```

This Function manages the logic of the lobby menu, including button hovers and clicks.

### Settings :

- `lobbyMenu`: Reference to the `LobbyMenu` object representing the lobby menu.
- `windowManager`: Reference to the `WindowManager` object managing the SFML window.
- `hostOrJoinMenu`: Reference to the `HostOrJoinMenu` object representing the “Host or Join” menu.
- `game`: Reference to the `Game` object managing the game.
- `sprite`: Reference to the `Sprite` object for level configuration.
- `commandsToServer`: Reference to the `CommandsToServer` object for commands to the server.
- `buttonManager`: Reference to the `ButtonManager` object managing the buttons.
- `ipAdress`: Reference to the `IpAdress` object to manage the IP address.

### Example of use
```cpp
LobbyMenu myLobbyMenu; // Make sure myLobbyMenu is correctly initialized.
WindowManager myWindowManager; // Make sure myWindowManager is correctly initialized.
HostOrJoinMenu myHostOrJoinMenu; // Make sure myHostOrJoinMenu is correctly initialized.
Game myGame; // Make sure myGame is correctly initialized.
Sprite mySprite; // Make sure mySprite is properly initialized.
CommandsToServer myCommandsToServer; // Make sure myCommandsToServer is correctly initialized.
ButtonManager myButtonManager; // Make sure myButtonManager is correctly initialized.
IpAddress myIpAddress; // Make sure myIpAddress is correctly initialized.
InLoopMenus::lobbyMenuInLoop(myLobbyMenu, myWindowManager, myHostOrJoinMenu, myGame, mySprite, myCommandsToServer, myButtonManager, myIpAdress);
```

## Function `menuChoice`

### Constructor :
```cpp
void InLoopMenus::menuChoice(
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
    IpAdress& ipAdress);
```

This function allows you to switch between different menus depending on the current status.

### Settings :

- `menu`: Reference to the `Menu` object representing the current menu.
- `introMenu`: Reference to the `InLoopMenus` object for Functions linked to the intro menu.
- `windowManager`: Reference to the `WindowManager` object managing the SFML window.
- `music`: Reference to the `Music` object managing music.
- `clock`: Reference to the `sf::Clock` object to measure time.
- `choiceMenu`: Reference to the `ChoiceMenu` object representing the choice menu.
- `hostOrJoinMenu`: Reference to the `HostOrJoinMenu` object representing the “Host or Join” menu.
- `lobbyMenu`: Reference to the `LobbyMenu` object representing the lobby menu.
- `buttonManager`: Reference to the `ButtonManager` object managing the buttons.
- `game`: Reference to the `Game` object managing the game.
- `commandsToServer`: Reference to the `CommandsToServer` object for commands to the server.
- `settingMenu`: Reference to the `SettingMenu` object representing the Settings menu.
- `inLoopGame`: Reference to the `InLoopGame` object for Functions linked to the game loop.
- `event`: Reference to the `sf::Event` object to manage events.
- `sprite`: Reference to the `Sprite` object for level configuration.
- `onGameClock`: Reference to the `sf::Clock` object to measure game time.
- `registry`: Reference to the `Registry` object to manage the game state.
- `ipAdress`: Reference to the `IpAdress` object to manage the IP address.

### Example of use :
```cpp
// Make sure all required objects are properly initialized before calling the Function.
menuChoice(menu, introMenu, windowManager, music, clock, choiceMenu, hostOrJoinMenu, lobbyMenu, buttonManager, game, commandsToServer, settingMenu, inLoopGame, event, sprite, onGameClock, registry, ipAdress);
```

## Function `updateScore`

### Constructor :
```cpp
void InLoopGame::updateScore(WindowManager& windowManager, Registry& registry);
```

This Function updates the score display in the game window.

### Settings :

- `windowManager`: Reference to the `WindowManager` object used to manage the window.
- `registry`: Reference to the `Registry` object which stores game data.

### Example of use :
```cpp
WindowManager myWindowManager; // Make sure your WindowManager object is correctly initialized.
Registry myRegistry; // Make sure your Registry object is correctly initialized.
InLoopGame myInLoopGame;
myInLoopGame.updateScore(myWindowManager, myRegistry);
```

## Function `refreshRegistry`

### Constructor :
```cpp
void InLoopGame::refreshRegistry(Registry& registry, CommandsToServer& commandsToServer, IpAdress& ipAdress);
```

This Function sends refresh commands to the server at regular intervals.

### Settings :
- `registry`: Reference to the `Registry` object which stores game data.
- `commandsToServer`: Reference to the `CommandsToServer` object used to send commands to the server.
- `ipAdress`: `IpAdress` object containing the IP address of the server.

### Example of use :
```cpp
Registry myRegistry; // Make sure your Registry object is correctly initialized.
CommandsToServer myCommandsToServer; // Make sure your CommandsToServer object is correctly initialized.
IpAddress myIpAddress; // Make sure your IpAdress object is correctly initialized.
InLoopGame myInLoopGame;
myInLoopGame.refreshRegistry(myRegistry, myCommandsToServer, myIpAdress);
```

## Function `pingServer`

### Constructor :
```cpp
void InLoopGame::pingServer(CommandsToServer& commandsToServer, IpAdress& ipAdress);
```

This Function pings the server at regular intervals to maintain the connection.

### Settings :

- `commandsToServer`: Reference to the `CommandsToServer` object used to send commands to the server.
- `ipAdress`: `IpAdress` object containing the IP address of the server.

### Example of use :
```cpp
CommandsToServer myCommandsToServer; // Make sure your CommandsToServer object is correctly initialized.
IpAddress myIpAddress; // Make sure your IpAdress object is correctly initialized.
InLoopGame myInLoopGame;
myInLoopGame.pingServer(myCommandsToServer, myIpAdress);
```

## Function `gameInLoop`

### Constructor :
```cpp
void InLoopGame::gameInLoop(
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
    IpAdress& ipAdress);
```

This Function represents the main loop of the game and manages events, game logic, interactions with the server, and rendering.

### Settings :

- `event`: Reference to the `sf::Event` object containing the game events.
- `windowManager`: Reference to the `WindowManager` object used to manage the window.
- `game`: Reference to the `Game` object which represents the state of the game.
- `music`: Reference to the `Music` object used to manage the game's music.
- `commandsToServer`: Reference to the `CommandsToServer` object used to send commands to the server.
- `sprite`: Reference to the `Sprite` object containing information on the player's sprite.
- `onGameClock`: Reference to the `sf::Clock` object used to measure time in the game loop.
- `registry`: Reference to the `Registry` object which stores game data.
- `buttonManager`: Reference to the `ButtonManager` object used to manage the game's buttons.
- `choiceMenu`: Reference to the `ChoiceMenu` object used to manage the choice menu.
- `ipAdress`: `IpAdress` object containing the IP address of the server.

### Example of use :
```cpp
sf::Event myEvent; // Make sure your sf::Event object is correctly initialized.
WindowManager myWindowManager; // Make sure your WindowManager object is correctly initialized.
Game myGame; // Make sure your Game object is correctly initialized.
Music myMusic; // Make sure your Music object is correctly initialized.
CommandsToServer myCommandsToServer; // Make sure your CommandsToServer object is correctly initialized.
Sprite mySprite; // Make sure your Sprite object is correctly initialized.
sf::Clock myOnGameClock; // Make sure your sf::Clock object is correctly initialized.
Registry myRegistry; // Make sure your Registry object is correctly initialized.
ButtonManager myButtonManager; // Make sure your ButtonManager object is correctly initialized.
ChoiceMenu myChoiceMenu; // Make sure your ChoiceMenu object is correctly initialized.
IpAddress myIpAddress; // Make sure your IpAdress object is correctly initialized.
InLoopGame myInLoopGame;
myInLoopGame.gameInLoop(myEvent, myWindowManager, myGame, myMusic, myCommandsToServer, mySprite, myOnGameClock, myRegistry, myButtonManager, myChoiceMenu, myIpAdress);
```

## Function `Game::setPath`

### Constructor :
```cpp
void Game::setPath(Sprite mSprite);
```

This Function initializes the textures and sprites used for the background, the scenery elements, and the game cursor using the paths provided by the `Sprite` object.

### Paramètre :

- `mSprite` : `Sprite` object containing the paths to the necessary images.

### Example of use :
```cpp
Sprite mySprite;  // Make sure your Sprite object is properly initialized.
Game myGame;
myGame.setPath(mySprite);
```

## Function `moveParallax`

### Constructor :
```cpp
void Game::moveParallax();
```

This Function moves the different elements of the scenery (backgrounds, buildings, etc.) at different speeds to create a parallax effect.

### Example of use :
```cpp
Game myGame;
myGame.moveParallax();
```

## Function `repeatParallax`

### Constructor :
```cpp
void Game::repeatParallax();
```

This Function checks if the scenery elements have exceeded the screen and replaces them in the appropriate place to create a continuous scroll.

### Example of use :
```cpp
Game myGame;
myGame.repeatParallax();
```

## Function `isPaused`

### Constructor :
```cpp
void Game::isPaused();
```

This Function manages the change of game pause state.

### Example of use :
```cpp
Game myGame;  // Make sure your Game object is correctly initialized.
myGame.isPaused();
```

## Function `setCursorPosition`

### Constructor :
```cpp
void Game::setCursorPosition(sf::RenderWindow& window);
```

This Function updates the player's cursor position based on mouse and joystick inputs.

### Settings :

- `window` : Reference to the `sf::RenderWindow` object representing the game window.

### Example of use :
```cpp
sf::RenderWindow myWindow; // Make sure your sf::RenderWindow object is correctly initialized.
Game myGame; // Make sure your Game object is correctly initialized.
myGame.setCursorPosition(myWindow);
```

## Function `Game::draw`

### Constructor :
```cpp
void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

This Function renders in-game graphics, such as backgrounds, buildings, and the player cursor.

### Settings :

- `target`: Reference to the `sf::RenderTarget` object representing the rendering target.
- `states`: Rendering state to apply.

### Example of use :
```cpp
sf::RenderWindow myWindow; // Make sure your sf::RenderWindow object is correctly initialized.
Game myGame; // Make sure your Game object is correctly initialized.
sf::RenderStates myRenderStates; // Make sure your sf::RenderStates object is correctly initialized.
myGame.draw(myWindow, myRenderStates);
```

## Function `displayHealth`

### Constructor :
```cpp
void Game::displayHealth(Registry& registry, Music& music, WindowManager& windowManager);
```

This Function displays the player's health level in the game window.

### Settings :

- `registry`: Reference to the `Registry` object which stores game data.
- `music`: Reference to the `Music` object used to manage the game's music.
- `windowManager`: Reference to the `WindowManager` object used to manage the window.

### Example of use :
```cpp
Registry myRegistry; // Make sure your Registry object is correctly initialized.
Music myMusic; // Make sure your Music object is correctly initialized.
WindowManager myWindowManager; // Make sure your WindowManager object is correctly initialized.
Game myGame; // Make sure your Game object is correctly initialized.
myGame.displayHealth(myRegistry, myMusic, myWindowManager);
```