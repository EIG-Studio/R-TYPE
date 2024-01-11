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

## class `WindowManager`

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

## 