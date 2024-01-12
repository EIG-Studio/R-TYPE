# Client

### This is a technique documentation for explain the differents tools offered by the Client

# Tables of Contents

## Fonction `main`

La fonction principale de l'application qui initialise les différents composants et gère la boucle principale du jeu.

La fonction commence par initialiser plusieurs objets nécessaires au fonctionnement de l'application. Cela inclut la gestionnaire de fenêtre `WindowManager`, les menus, les Clock, les commandes vers le serveur, l'adresse IP, le sprite, et d'autres éléments.

### Boucle Principale
```cpp
int frameCount = 0;
sf::Text fpsText;
// ... (initialisation du texte et d'autres éléments)

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
La boucle principale est responsable de maintenir l'application en cours d'exécution. À chaque itération, elle gère les événements de la fenêtre, met à jour le texte des FPS, effectue des choix de menu en fonction de l'état actuel, et dessine le texte sur la fenêtre SFML.

### Fin de l'Application

Une fois que la fenêtre SFML est fermée, l'application sort de la boucle principale et se termine.

## Fonction `getLocalIpAddress`

Cette fonction utilise Boost.Asio pour récupérer l'adresse IP locale de la machine.

### Utilisation
```cpp
std::string ipAddress = getLocalIpAddress();
```

## Fonction `handleWindowEvents`

Cette fonction gère les événements de la fenêtre SFML, tels que la fermeture de la fenêtre, les touches du clavier, etc.

### Utilisation :
```cpp
sf::Event event;
handleWindowEvents(event, windowManager, menu, choiceMenu, hostOrJoinMenu, game, sprite, music);
```

## Fonction `updateFpsText`

Cette fonction met à jour le texte affichant le nombre d'images par seconde (FPS) sur la fenêtre SFML.

### Utilisation :
```cpp
sf::Text fpsText;
sf::Clock clock;
int frameCount = 0;
updateFpsText(windowManager, fpsText, clock, frameCount);
```

## Fonction `menuChoice`

Cette fonction gère les différents menus de l'application en fonction de l'état actuel.

### Utilisation :
```cpp
menuChoice(menu, introMenu, windowManager, music, clock, choiceMenu, hostOrJoinMenu, lobbyMenu, buttonManager, game, commandsToServer, settingMenu, inLoopGame, event, sprite, onGameClock, registry, ipAdress);
```

## Class `WindowManager`

La classe `WindowManager` est responsable de l'initialisation de la fenêtre SFML et fournit des méthodes pour accéder à des éléments tels que la police, l'icône, la fenêtre elle-même, et des paramètres de mouvement et de temps.

### Methode `initWindow`

Cette méthode initialise la fenêtre SFML avec des paramètres par défaut. Elle configure également la vitesse de mouvement, le FPS maximal, et charge l'icône de la fenêtre ainsi que la police utilisée dans l'application.

#### Utilisation
```cpp
int result = initWindow();
if (result == -1) {
    // Gérer l'erreur lors de l'initialisation de la fenêtre
}
```
### Methode `getFont`

Cette méthode renvoie la police `sf::Font` utilisée dans l'application.

#### Utilisation :
```cpp
sf::Font& font = getFont();
```

### Methode `getIcon`

Cette méthode renvoie l'icône `sf::Image` de la fenêtre.

#### Utilisation :
```cpp
sf::Image& icon = getIcon();
```

### Methode `getWindow`

Cette méthode renvoie la fenêtre SFML elle-même `sf::RenderWindow`.

#### Utilisation :
```cpp
sf::RenderWindow& window = getWindow();
```

### Methode `getMovementSpeed`

Cette méthode renvoie la vitesse de mouvement actuelle configurée dans la classe.

#### Utilisation :
```cpp
float speed = getMovementSpeed();
```

### Methode `getMillisecondsPerSecond`

Cette méthode renvoie le nombre de millisecondes par seconde utilisé dans le calcul du temps.

#### Utilisation :
```cpp
float msPerSecond = getMillisecondsPerSecond();
```

### Methode `getMillisecondsPerFrame`

Cette méthode renvoie le nombre de millisecondes par trame utilisé dans le calcul du temps.

#### Utilisation :
```cpp
float msPerFrame = getMillisecondsPerFrame();
```

## Fonction `split(const std::string& s, char delim)`

Cette fonction divise une chaîne en fonction d'un délimiteur et renvoie un vecteur de sous-chaînes résultantes.

### Utilisation :
```cpp
std::vector<std::string> result = split("Texte à diviser", '|');
```

## Fonction `handleReceive`

La fonction `handleReceive` est responsable du traitement des données reçues depuis le réseau. Elle prend en charge plusieurs types de commandes et met à jour la structure de données `Registry` en conséquence.

### Signature
```cpp
void handleReceive(
    Registry& registry,
    const boost::system::error_code& error,
    size_t len,
    unsigned char buffer[sizeof(TransferData)],
    std::string& mNewPos,
    Music& music);
```

### Paramètres :

- `registry`: Une référence vers la structure de données (Registry) qui stocke les entités du jeu.
- `error`: Un objet boost::system::error_code qui indique s'il y a eu une erreur lors de la réception des données.
- `len`: La taille des données reçues.
- `buffer`: Le tampon contenant les données reçues.
- `mNewPos`: Une référence vers une chaîne de caractères stockant la dernière position reçue.
- `music`: Un objet de la classe Music qui gère la lecture de fichiers audio.

### Fonctionement :

La fonction commence par vérifier s'il y a eu une erreur pendant la réception des données ou si aucune donnée n'a été reçue (cas non bloquant). Si c'est le cas, elle effectue une gestion appropriée.

En cas de réception réussie et de données non vides, elle utilise une structure de données `TransferData` pour interpréter les commandes et les arguments associés.

Commande `NEW_POS`
Si la commande est `NEW_POS`, la fonction extrait l'ID, la position X et la position Y de l'entité du paquet de données. Elle met ensuite à jour la position de l'entité correspondante dans la structure de données `Registry`.

Commande `NEW_PLAYER`
Si la commande est NEW_PLAYER`, la fonction crée une nouvelle entité joueur avec l'ID et la position fournies. Elle ajoute également des composants tels que la position, le rendu, le type et la taille à cette entité.

Commande `NEW_ENEMY`
Si la commande est `NEW_ENEMY`, la fonction crée une nouvelle entité ennemie avec l'ID et la position fournies. Elle ajoute des composants similaires à ceux du joueur.

Commande `PLAYER_PROJECTILE`
Si la commande est `PLAYER_PROJECTILE`, la fonction crée une nouvelle entité projectile du joueur avec l'ID et la position fournies.

Commande `DELETE`
Si la commande est `DELETE`, la fonction supprime une entité spécifiée de la structure de données `Registry`.

Commande `PLAY_BOOM_ENEMIES`
Si la commande est PLAY_BOOM_ENEMIES, la fonction déclenche la lecture d'un effet sonore (boomEnemies) via l'objet Music.

### Erreurs :

En cas d'erreur pendant la réception des données ou lors du traitement, la fonction imprime un message d'erreur approprié dans la console.

### Utilisation :
```cpp
handleReceive(registry, error, len, buffer, mNewPos, music);
```

## Fonction `sendToServer`

Cette fonction envoie des données au serveur via une socket réseau. Elle convertit une chaîne en une structure de données `TransferData` et envoie ces données au serveur.

### Utilisation :
```cpp
sendToServer(socket, "Commande à envoyer", ipAdress);
```

## Fonction `asyncReceiveSecondSocket`

Cette méthode utilise l'asynchronicité pour recevoir continuellement des données réseau sur une socket. Elle utilise une mutex pour assurer une manipulation sûre des données partagées.

### Utilisation :
```cpp
asyncReceiveSecondSocket(registry, music);
```

## Fonction `getNewPos`

Cette méthode renvoie la dernière version des position de chaque entity reçue.

### Utilisation :
```cpp
std::string newPos = getNewPos();
```

## Class `Button`

La classe `Button` représente un bouton graphique dans une interface utilisateur SFML. Elle inclut des fonctionnalités telles que la création, le positionnement, la vérification des clics, et le rendu.

#### Signature :
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

#### Paramètres :

- `size`: Taille du bouton.
- `position`: Position du coin supérieur gauche du bouton.
- `fillColor`: Couleur de remplissage du bouton.
- `outlineColor`: Couleur du contour du bouton.
- `outlineThickness`: Épaisseur du contour du bouton.
- `text`: Texte à afficher sur le bouton.
- `font`: Police utilisée pour le texte.
- `characterSize`: Taille du texte.

#### Fonctionnement :

Le constructeur initialise la forme `m_shape` et l'étiquette `m_label` du bouton avec les paramètres fournis. Il positionne également le texte au centre du bouton en fonction de la taille et de la position.

### Methode `checkClick`

#### Signature
```cpp
bool checkClick(float cursorX, float cursorY);
```

#### Paramètres :

- `cursorX`: Position X du curseur.
- `cursorY`: Position Y du curseur.

#### Fonctionement :

Cette méthode vérifie si le curseur se trouve sur le bouton et si le bouton de la souris (ou un bouton du joystick) est enfoncé. Si ces conditions sont remplies et que le bouton n'a pas déjà été cliqué récemment, elle renvoie `true` et marque le bouton comme "cliqué" pour éviter les clics répétés.

### Methode `checkHover`

#### Signature :
```cpp
bool checkHover(float cursorX, float cursorY);
```

#### Paramètres :

- `cursorX`: Position X du curseur.
- `cursorY`: Position Y du curseur.

#### Fonctionnement :

Cette méthode vérifie si le curseur se trouve sur le bouton. Si c'est le cas, elle change la couleur du contour du bouton pour indiquer qu'il est survolé.

### Methode `draw`

#### Signature :
```cpp
void draw(sf::RenderWindow& window) const;
```

#### Paramètres :

- `window`: Fenêtre SFML sur laquelle le bouton doit être dessiné.

#### Fonctionnement :

Cette méthode dessine la forme `m_shape` et l'étiquette `m_label` du bouton sur la fenêtre SFML fournie.

### Methode `setText`

#### Signature :
```cpp
void setText(const std::string& text);
```

#### Paramètres :

- `text`: Nouveau texte à afficher sur le bouton.

#### Fonctionnement

Cette méthode met à jour le texte affiché sur le bouton.

### Methode `setPosition`

#### Signature
```cpp
void setPosition(const sf::Vector2f& position);
```

#### Paramètres :

- `position`: Nouvelle position du coin supérieur gauche du bouton.

#### Fonctionnement :

Cette méthode met à jour la position du bouton et repositionne le texte au centre du bouton en conséquence.

### Methode `setSize`

#### Signature :
```cpp
void setSize(const sf::Vector2f& size);
```

#### Paramètres :

- `size`: Nouvelle taille du bouton.

#### Fonctionnement

Cette méthode met à jour la taille du bouton et repositionne le texte au centre du bouton en conséquence.

## Fonction `updateSpriteTexture`

###  Signature :
```cpp
void updateSpriteTexture(sf::Sprite& sprite, const std::string& texturePath);
```

Cette fonction met à jour la texture d'un sprite en utilisant une mémoire cache pour optimiser les performances de chargement des textures.

### Paramètres :

- `sprite`: Référence à un objet sf::Sprite dont la texture doit être mise à jour.
- `texturePath`: Chemin vers le fichier de texture.

### Utilisation :
```cpp
sf::Sprite mySprite;
updateSpriteTexture(mySprite, "chemin/vers/ma_texture.png");
```

## Fonction `updateSpritePositionAndPath`

### Signature :
```cpp
void updateSpritePositionAndPath(sf::Sprite& sprite, float newX, float newY, const std::string& texturePath);
```

Cette fonction met à jour la position et la texture d'un sprite.

### Paramètres :

- `sprite`: Référence à un objet sf::Sprite dont la position et la texture doivent être mises à jour.
- `newX`, `newY`: Nouvelles coordonnées X et Y du sprite.
- `texturePath`: Chemin vers le fichier de texture.

### Utilisation :
```cpp
sf::Sprite mySprite;
updateSpritePositionAndPath(mySprite, 100.0f, 150.0f, "chemin/vers/ma_texture.png");
```

## Fonction `movePlayer`

### Signature :
```cpp
void Game::movePlayer(Registry& registry, float movementSpeed, float winX, float winY, CommandsToServer& commandsToServer, Sprite mSprite, IpAdress& ipAdress);
```

Cette fonction gère le mouvement du joueur en fonction des touches du clavier et met à jour les informations nécessaires.

### Paramètres :

- `registry`: Référence à l'objet Registry contenant les entités du jeu.
- `movementSpeed`: Vitesse de déplacement du joueur.
- `winX, winY`: Dimensions de la fenêtre du jeu.
- `commandsToServer`: Référence à l'objet CommandsToServer pour envoyer des commandes au serveur.
- `mSprite`: Sprite du joueur.
- `ipAdress`: Adresse IP du serveur.

### Utilisation :
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

## Fonction `InputTypeToString`

### Signature :
```cpp
std::string Game::InputTypeToString(sf::Keyboard::Key key);
```

Cette fonction convertit une touche du clavier en une chaîne de caractères représentant le type d'entrée.

### Paramètres :

- `key`: Touche du clavier (sf::Keyboard::Key) à convertir.

### Utilisation :
```cpp
sf::Keyboard::Key myKey = sf::Keyboard::Up;
std::string inputString = InputTypeToString(myKey);
```

## Fonction `HandleMovement`

### Signature :
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
Cette fonction gère le mouvement du joueur en fonction des touches du clavier, envoie des mises à jour au serveur, et met à jour la position du sprite du joueur.

### Paramètres :

- `registry` : Référence à l'objet Registry contenant les entités du jeu.
- `key` : Touche du clavier (sf::Keyboard::Key) qui est pressée.
- `commandsToServer` : Référence à l'objet CommandsToServer pour envoyer des commandes au serveur.
- `movementSpeed` : Vitesse de déplacement du joueur.
- `deltaX` : Déplacement en pixels selon l'axe X.
- `deltaY` : Déplacement en pixels selon l'axe Y.
- `path` : Chemin vers le fichier de texture du sprite du joueur.
- `windowLimit` : Limite de la fenêtre du jeu, utilisée pour éviter le dépassement des bords.
- `spriteLimit` : Limite du sprite du joueur pour éviter le dépassement des bords.
- `ipAdress` : Référence à l'objet IpAdress représentant l'adresse IP du serveur.

### Utilisation :
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

## Fonction `SendInputUpdate`

### Signature :
```cpp
void Game::SendInputUpdate(CommandsToServer& commandsToServer, Registry& registry, const std::string& inputType, IpAdress& ipAdress);
```

Cette fonction envoie une mise à jour d'entrée au serveur.

### Parameters :

- `commandsToServer` : Référence à l'objet CommandsToServer pour envoyer des commandes au serveur.
- `registry` : Référence à l'objet Registry contenant les entités du jeu.
- `inputType` : Chaîne de caractères représentant le type d'entrée (par exemple, "UP", "DOWN", "LEFT", "RIGHT").
- `ipAdress` : Référence à l'objet IpAdress représentant l'adresse IP du serveur.

### Utilisation :
```cpp
CommandsToServer myCommands;
Registry myRegistry;
IpAdress serverIp;
std::string inputType = "UP";
Game::SendInputUpdate(myCommands, myRegistry, inputType, serverIp);
```

## Fonction `shooting`

### Signature :
```cpp
void Game::shooting(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress);
```

Cette fonction envoie une commande de tir au serveur.

### Paramètres :

- `commandsToServer` : Référence à l'objet `CommandsToServer` pour envoyer des commandes au serveur.
- `registry` : Référence à l'objet `Registry` contenant les entités du jeu.
- `ipAdress` : Référence à l'objet `IpAdress` représentant l'adresse IP du serveur.

### Utilisation :
```cpp
CommandsToServer myCommands;
Registry myRegistry;
IpAdress serverIp;
Game::shooting(myCommands, myRegistry, serverIp);
```

## Fonction `damageToPlayer`

### Signature :
```cpp
void Game::damageToPlayer(CommandsToServer& commandsToServer, Registry& registry, IpAdress& ipAdress);
```

Cette fonction envoie une commande de dommage au joueur au serveur.

### Paramètres :

- `commandsToServer` : Référence à l'objet `CommandsToServer` pour envoyer des commandes au serveur.
- `registry` : Référence à l'objet `Registry` contenant les entités du jeu.
- `ipAdress` : Référence à l'objet `IpAdress` représentant l'adresse IP du serveur.

### Utilisation :
```cpp
CommandsToServer myCommands;
Registry myRegistry;
IpAdress serverIp;
Game::damageToPlayer(myCommands, myRegistry, serverIp);
```

## Fonction `displayArrow`

### Signature :
```cpp
void Game::displayArrow(Registry& registry, WindowManager& windowManager);
```

Cette fonction affiche une flèche au-dessus du joueur dans la fenêtre.

### Paramètres :

- `registry` : Référence à l'objet `Registry` contenant les entités du jeu.
- `windowManager` : Référence à l'objet `WindowManager` représentant la gestion de la fenêtre du jeu.


### Utilisation :
```cpp
Registry myRegistry;
WindowManager myWindowManager;
Game::displayArrow(myRegistry, myWindowManager);
```

## Fonction `setPath`

### Signature :
```cpp
void Music::setPath(Sprite mSprite);
```

Cette fonction configure les chemins des fichiers sonores pour différentes actions du jeu en utilisant les chemins spécifiés dans un objet `Sprite`.

### Paramètres :

- `mSprite` : Objet de la classe `Sprite` contenant les chemins des fichiers sonores.

### Utilisation :
```cpp
Sprite mySprite;  // Assurez-vous que mySprite est correctement initialisé avec les chemins des fichiers sonores.
Music myMusic;
myMusic.setPath(mySprite);
```

## Fonction `Menu::setPath`

### Signature :
```cpp
void Menu::setPath(Sprite mSprite);
```

Cette fonction configure les textures, sprites et textes associés au menu en utilisant les chemins spécifiés dans un objet `Sprite`.

### Paramètres :

- `mSprite` : Objet de la classe `Sprite` contenant les chemins des textures, sprites et polices.

### Utilisation :
```cpp
Sprite mySprite;  // Assurez-vous que mySprite est correctement initialisé avec les chemins des textures et polices.
Menu myMenu;
myMenu.setPath(mySprite);
```

## Fonction `Menu::blinkingText`

### Signature :
```cpp
sf::Clock Menu::blinkingText(sf::Clock mClock, sf::Time mElapsed);
```

Cette fonction gère le clignotement du texte "Press ENTER to burn the city".

### Paramètres :

- `mClock` : clock SFML utilisée pour mesurer le temps entre les clignotements.
- `mElapsed` : Temps écoulé depuis le dernier clignotement.

### Utilisation :
```cpp
sf::Clock myClock;
sf::Time elapsedTime = ...;  // Mettez à jour avec le temps écoulé depuis la dernière frame.
myClock = myMenu.blinkingText(myClock, elapsedTime);
```

## Fonction `Menu::draw`

### Signature :
```cpp
void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

Cette fonction dessine les éléments du menu sur la fenêtre de rendu.

### Paramètres :

- `target` : Référence à l'objet `sf::RenderTarget` sur lequel dessiner.
- `states` : État de rendu SFML.

### Utilisation :
```cpp
sf::RenderWindow window;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
Menu myMenu;
window.draw(myMenu);  // Appelle la fonction draw de la classe Menu pour dessiner les éléments.
```

## Fonction `ChoiceMenu::setPath`

### Signature :
```cpp
void ChoiceMenu::setPath(Sprite mSprite);
```

Cette fonction configure les textures, sprites et textes associés au menu de choix en utilisant les chemins spécifiés dans un objet `Sprite`.



### Paramètres :

- `mSprite` : Objet de la classe `Sprite` contenant les chemins des textures, sprites et polices.

### Utilisation :
```cpp
Sprite mySprite;  // Assurez-vous que mySprite est correctement initialisé avec les chemins des textures et polices.
ChoiceMenu myChoiceMenu;
myChoiceMenu.setPath(mySprite);
```

## Fonction `ChoiceMenu::setCursorPosition`

### Signature :
```cpp
void ChoiceMenu::setCursorPosition(sf::RenderWindow& window);
```

Cette fonction gère la position du curseur dans le menu en fonction de la souris et du joystick.

### Paramètres :

- `window` : Référence à la fenêtre SFML.

### Utilisation :
```cpp
sf::RenderWindow myWindow;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
ChoiceMenu myChoiceMenu;
myChoiceMenu.setCursorPosition(myWindow);
```

## Fonction `ChoiceMenu::draw`

### Signature :
```cpp
void ChoiceMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

Cette fonction dessine les éléments du menu de choix sur la fenêtre de rendu.

### Paramètres :

- `target` : Référence à l'objet `sf::RenderTarget` sur lequel dessiner.
- `states` : État de rendu SFML.

### Utilisation :
```cpp
sf::RenderWindow window;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
ChoiceMenu myChoiceMenu;
window.draw(myChoiceMenu);  // Appelle la fonction draw de la classe ChoiceMenu pour dessiner les éléments.
```

## Fonction `SettingMenu::setPath`

### Signature :
```cpp
void SettingMenu::setPath(Sprite mSprite);
```

Cette fonction configure les textures et sprites associés au menu des paramètres en utilisant les chemins spécifiés dans un objet `Sprite`.

### Paramètres :

- `mSprite` : Objet de la classe Sprite contenant les chemins des textures et sprites.

### Utilisation :
```cpp
Sprite mySprite;  // Assurez-vous que mySprite est correctement initialisé avec les chemins des textures.
SettingMenu mySettingMenu;
mySettingMenu.setPath(mySprite);
```

## Fonction `SettingMenu::setCursorPosition`

### Signature :
```cpp
void SettingMenu::setCursorPosition(sf::RenderWindow& window);
```

Cette fonction gère la position du curseur dans le menu en fonction de la souris et du joystick.

### Paramètres :

- `window` : Référence à la fenêtre SFML.

### Utilisation :
```cpp
sf::RenderWindow myWindow;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
SettingMenu mySettingMenu;
mySettingMenu.setCursorPosition(myWindow);
```

## Fonction `SettingMenu::draw`

### Signature :
```cpp
void SettingMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

Cette fonction dessine les éléments du menu de choix sur la fenêtre de rendu.

### Paramètres :

- `target` : Référence à l'objet `sf::RenderTarget` sur lequel dessiner.
- `states` : État de rendu SFML.

### Utilisation :
```cpp
sf::RenderWindow window;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
SettingMenu mySettingMenu;
window.draw(mySettingMenu);  // Appelle la fonction draw de la classe ChoiceMenu pour dessiner les éléments.
```

## Fonction `HostOrJoinMenu::setPath`

### Signature :
```cpp
void HostOrJoinMenu::setPath(Sprite mSprite);
```

Cette fonction configure les textures et sprites associés au menu "Host or Join" en utilisant les chemins spécifiés dans un objet `Sprite`.

### Paramètres :

- `mSprite` : Objet de la classe Sprite contenant les chemins des textures et sprites.

### Utilisation :
```cpp
Sprite mySprite;  // Assurez-vous que mySprite est correctement initialisé avec les chemins des textures.
HostOrJoinMenu myHostOrJoinMenu;
myHostOrJoinMenu.setPath(mySprite);
```

## Fonction `HostOrJoinMenu::setCursorPosition`

### Signature :
```cpp
void HostOrJoinMenu::setCursorPosition(sf::RenderWindow& window);
```

Cette fonction gère la position du curseur dans le menu en fonction de la souris et du joystick.

### Paramètres :

- `window` : Référence à la fenêtre SFML.

### Utilisation :
```cpp
sf::RenderWindow myWindow;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
HostOrJoinMenu myHostOrJoinMenu;
myHostOrJoinMenu.setCursorPosition(myWindow);
```

## Fonction `HostOrJoinMenu::inputText`

### Signature :
```cpp
void HostOrJoinMenu::inputText(sf::Event& event, IpAdress& ipAdress);
```

Cette fonction gère la saisie de texte pour la saisie de l'adresse IP.

### Paramètres :

- `event` : Objet sf::Event contenant les informations sur l'événement.
- `ipAdress` : Objet IpAdress pour stocker l'adresse IP saisie.

### Utilisation :
```cpp
sf::Event myEvent;  // Assurez-vous que myEvent est correctement initialisé avec l'événement approprié.
IpAdress myIpAdress;  // Assurez-vous que myIpAdress est correctement initialisé.
HostOrJoinMenu myHostOrJoinMenu;
myHostOrJoinMenu.inputText(myEvent, myIpAdress);
```

## Fonction `HostOrJoinMenu::draw`

### Signature :
```cpp
void HostOrJoinMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

Cette fonction dessine les éléments du menu de choix sur la fenêtre de rendu.

### Paramètres :

- `target` : Référence à l'objet `sf::RenderTarget` sur lequel dessiner.
- `states` : État de rendu SFML.

### Utilisation :
```cpp
sf::RenderWindow window;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
HostOrJoinMenu myHostOrJoinMenu;
window.draw(myHostOrJoinMenu);  // Appelle la fonction draw de la classe ChoiceMenu pour dessiner les éléments.
```

## Fonction `LobbyMenu::setPath`

### Signature :
```cpp
void LobbyMenu::setPath(Sprite mSprite);
```

Cette fonction configure les textures et sprites associés au menu "Lobby" en utilisant les chemins spécifiés dans un objet `Sprite`.

### Paramètres :

- `mSprite` : Objet de la classe `Sprite` contenant les chemins des textures et sprites.

### Utilisation :
```cpp
Sprite mySprite;  // Assurez-vous que mySprite est correctement initialisé avec les chemins des textures.
LobbyMenu myLobbyMenu;
myLobbyMenu.setPath(mySprite);
```

## Fonction `LobbyMenu::setCursorPosition`

### Signature :
```cpp
void LobbyMenu::setCursorPosition(sf::RenderWindow& window);
```

Cette fonction gère la position du curseur dans le menu `Lobby` en fonction de la souris et du joystick.

### Paramètres :

- `window` : Référence à la fenêtre SFML.

### Utilisation :
```cpp
sf::RenderWindow myWindow;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
LobbyMenu myLobbyMenu;
myLobbyMenu.setCursorPosition(myWindow);
```

## Fonction `LobbyMenu::draw`

### Signature :
```cpp
void LobbyMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const;
```

Cette fonction dessine les éléments du menu de choix sur la fenêtre de rendu.

### Paramètres :

- `target` : Référence à l'objet `sf::RenderTarget` sur lequel dessiner.
- `states` : État de rendu SFML.

### Utilisation :
```cpp
sf::RenderWindow window;  // Assurez-vous que votre fenêtre SFML est correctement initialisée.
LobbyMenu myLobbyMenu;
window.draw(myLobbyMenu);  // Appelle la fonction draw de la classe ChoiceMenu pour dessiner les éléments.
```

## 