# Server

<<<<<<< HEAD
### This is a technique documentation for explain the differents tools offered by the server

# Tables of Contents

- [Function `Server::startListening`](#function-serverstartlistening)
  - [Example of use](#example-of-use-)
- [Function `Server::startSending`](#function-serverstartsending)
  - [Example of use](#example-of-use-1)
- [Function `Server::sendMessage`](#function-serversendmessage)
  - [Example of use](#example-of-use-2)
- [Function `Server::addClient`](#function-serveraddclient)
  - [Example of use](#example-of-use-3)
- [Function `Server::PlayerLoop`](#function-serverplayerloop)
  - [Example of use](#example-of-use-4)
- [Function `Server::playerProjectileMove`](#function-serverplayerprojectilemove)
  - [Example of use](#example-of-use-5)
- [Function `Server::ennemyMove`](#function-serverennemymove)
  - [Example of use](#example-of-use-6)
- [Function `Server::GameLoop`](#function-servergameloop)
  - [Example of use](#example-of-use-7)
- [Function `Server::createPlayer`](#function-servercreateplayer)
  - [Example of use](#example-of-use-8)
- [Function `Server::randNb`](#function-serverrandnb)
  - [Example of use](#example-of-use-9)
- [Function `Server::createEnnemy`](#function-servercreateennemy)
  - [Example of use](#example-of-use-10)
- [Function `Server::createBullet`](#function-servercreatebullet)
  - [Example of use](#example-of-use-11)
- [Function `Server::addMessage`](#function-serveraddmessage)
  - [Example of use](#example-of-use-12)
- [Function `Server::playerMove`](#function-serverplayermove)
  - [Example of use](#example-of-use-13)
- [Function `Server::sendAllEntites`](#function-serversendallentites)
  - [Example of use](#example-of-use-14)
- [Function `Server::refreshClientRegistry`](#function-serverrefreshclientregistry)
  - [Example of use](#example-of-use-15)
- [Function `Server::startGame`](#function-serverstartgame)
  - [Example of use](#example-of-use-16)
- [Function `Server::handleReceivedData`](#function-serverhandlereceiveddata)
  - [Example of use](#example-of-use-17)

## Function `Server::startListening`

The server Function `startListening` is responsible for receiving the data. It uses the Boost.Asio library for asynchronous communication. The received data is processed in the Function `handleReceivedData`. The Function also uses an `m_registryMutex` locking mechanism to ensure secure access to shared data.

### Example of use :
```cpp
Registry registry; // Instantiate a Registry object
Server server;
server.startListening(registry);
```

## Function `Server::startSending`

The server Function `startSending` manages the sending of data to clients. It uses a separate thread to periodically check for messages waiting in the `m_messages` queue and sends them to the appropriate clients.

### Example of use :
```cpp
Server server;
std::thread sendingThread(&Server::startSending, &server);
sendingThread.join(); // Wait for the sending thread to complete
```

## Function `Server::sendMessage`

The `sendMessage` Function sends `TransferData` data to connected clients. The data is converted to a `buffer` byte array before sending.

### Example of use :
```cpp
Server server;
TransferData data; // Initialize the data to send
server.sendMessage(data);
```

## Function `Server::addClient`

The `addClient` Function adds a client to the list of clients if it does not already exist.

### Example of use :
```cpp
Server server;
boost::asio::ip::udp::endpoint clientEndpoint; // Initialize the client endpoint
std::size_t clientId; // Initialize Client ID
server.addClient(clientEndpoint, clientId);
```

## Function `Server::PlayerLoop`

The `PlayerLoop` Function is a loop that runs continuously, checks the life of each client and removes inactive clients from the list. It also sends a delete message to the registry and updates the registry accordingly.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
server.PlayerLoop(registry);
```

## Function `Server::playerProjectileMove`

This Function manages the movement of players' projectiles. It updates the position of the projectile and checks if it has reached a limit (800 in our case). If the projectile exceeds this limit, it is deleted from the registry, and a deletion message is added to the message queue.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Entity playerProjectile;  // The player's projectile entity
std::size_t projectileId;  // The player's projectile ID
Server server;
server.playerProjectileMove(registry, playerProjectile, projectileId);
```

## Function `Server::ennemyMove`

This Function manages the movement of enemies. It updates the enemy's position based on their speed and checks if they have reached a limit on the left of the screen (-100 in our case). If the enemy exceeds this limit, it is deleted from the registry, a new enemy is created, and a deletion message is added to the message queue.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Entity ennemy;  // Enemy Entity
std::size_t ennemyId;  // Enemy ID
Server server;
server.ennemyMove(registry, ennemy, ennemyId);
```

## Function `Server::GameLoop`

This Function represents the main loop of the game on the server. It controls the movement of enemies and player projectiles in a loop. The loop is suspended for a short period of 50 ms between each iteration.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
server.GameLoop(registry);
```

## Function `Server::createPlayer`

This Function creates a player by adding the necessary components to a new entity in the registry. It also generates a `NEW_PLAYER` message to inform clients of the new player.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
std::size_t playerId = server.createPlayer(registry);
```

## Function `Server::randNb`

This Function generates a random number in the specified range [x, y].

### Example of use :
```cpp
int x = 1;
int y = 10;
int randomNumber = Server::randNb(x, y);
```

## Function `Server::createEnnemy`

This Function creates an enemy by adding the necessary components to a new entity in the registry. It also generates a `NEW_ENNEMY` message to inform clients of the new enemy.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
server.createEnnemy(registry);
```

## Function `Server::createBullet`

This Function creates a player shot by adding the necessary components to a new entity in the registry. It also generates a `PLAYER_PROJECTILE` message to inform clients of the new projectile.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
int posX = 100;
int posY = 200;
server.createBullet(registry, posX, posY);
```

## Function `Server::addMessage`

This Function adds a message to the message queue. It parses the message to extract the necessary data and stores it in the queue.

### Example of use :
```cpp
Server server;
std::string message = "NEW_PLAYER 1 0 0 1 1 Player\n";
server.addMessage(message);
```

## Function `Server::playerMove`

This Function updates a player's position in the specified direction. It also generates a N`EW_POS` message to inform clients of the player's new position.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
std::size_t playerId = 1;  // Player ID
COMMAND direction = RIGHT;  // Desired direction
server.playerMove(registry, direction, playerId);
```

## Function `Server::sendAllEntites`

This Function sends information about all registry entities to clients. It generates appropriate messages for each entity.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
server.sendAllEntites(registry);
```

## Function `Server::refreshClientRegistry`

This Function refreshes the client registry by checking whether the entity specified by the ID still exists in the registry. If not, a `DELETE` message is added.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
int clientId = 1;  // Client ID
server.refreshClientRegistry(registry, clientId);
```

## Function `Server::startGame`

This Function starts the game by initially creating a few enemies. It is usually called when a client logs in for the first time.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
bool gameStarted = server.startGame(registry);
```

## Function `Server::handleReceivedData`

This Function manages the data received from the client. It analyzes the received command and performs appropriate actions, such as creating entities, updating positions, etc.

### Example of use :
```cpp
Registry registry;  // Initialize the registry
Server server;
boost::asio::error_code error;
std::size_t bytesReceived;
boost::asio::ip::udp::endpoint remoteEndpoint;
server.handleReceivedData(error, bytesReceived, registry, remoteEndpoint);
```
=======
### This is a documentation for explain the server

# Tables of Contents

>>>>>>> refs/remotes/origin/Client
