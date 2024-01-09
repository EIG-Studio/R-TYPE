# GameEngine

### This is a documentation for explain the gameEngine

# Tables of Contents

- [Introduction](#introduction)
- [Game Engine Operation](#Game-Engine-Operation)
    - [Client Side](#client-side)
    - [Server Side](#server-side)
- [Using the Game Engine](#Using-the-Game-Engine)
    - [Public Methods of the Registry](#Public-Methods-of-the-Registry)
    - [Private Methods of the Registry](#Private-Methods-of-the-x²Registry)
- [GameEngine Technical Documentation](techGameEgine.md)

## Introduction

A game engine using the ECS (Entity-Component-System) method is designed to streamline and optimize the development of video games by separating various aspects of the game into entities, components, and systems.

In this model:

- An *entity* represents an object in the game.
- A *component* is a characteristic or specific aspect of that entity.
- A *system* is processing logic that acts on entities possessing certain components.
The use of ECS brings increased modularity to game development, allowing developers to more efficiently manage the growing complexity of projects.

Major advantages include:

- Component reuse.
- Ease of adding new features.
- Optimized performance.

ECS also facilitates operation parallelization, providing significant gains in efficiency and execution speed.

In summary, a game engine based on the ECS method offers a more flexible and efficient approach to structuring and developing complex video games, allowing developers to focus on specific elements of gameplay without sacrificing performance.

## Game Engine Operation

Our game engine is designed as a static library, subsequently used by both the server and the client in a video game, providing a robust architecture for managing entities and interactions between the server and clients.

### Server Side

On the server side, it acts as a central authority, managing game logic, critical calculations, and synchronization of the game world state. The ECS engine is used to maintain the absolute truth of the game, handle collisions, perform physical simulation, and process global events.

Game entities, representing objects and players, are centrally updated by the server. Specific components such as position, health, or other properties are managed in the server system, ensuring global game consistency.

### Client Side

On the other side, each client also uses its ECS engine to display the game updated by server-received data through the SFML library.

Clients receive regular updates from the server to synchronize their local instances with the global game state.

Locally generated player events, such as movements or actions, are then transmitted to the server for validation and propagation to all clients. This enables instantaneous responsiveness to player actions.

In summary, the use of an ECS-based game engine shared between the server and clients in a video game provides a distributed and consistent architecture, allowing smooth interaction between different parts while maintaining synchronization and game integrity.

## Using the Game Engine

To use the game engine effectively, one must utilize the `Registry` class, playing a central role in an ECS-based game engine.

The `Registry` class acts as a global manager that stores and organizes game entities. It offers essential functionalities such as creating and destroying entities, adding and removing components, and retrieving specific components associated with an entity.

By facilitating the management of entities and their components, the `Registry` enables the game engine to apply systems effectively, contributing to a modular, flexible, and extensible code design. Its central role in an ECS-based engine makes it a key component for dynamic object management and consistent implementation of game logic.

### Public Methods of the Registry

Public methods expose essential functionalities for external interaction with the Registry.

- The CreateEntity method allows the creation of a new entity, assigning a unique identifier to each generated entity.
- The DestroyEntity function offers the possibility to remove a specific entity from the registry, contributing to dynamic game object management.

Public template methods, such as `addComponent`, `removeComponent`, `getComponent`, and `hasComponent`, provide considerable flexibility to manipulate components associated with entities. These methods allow adding, removing, retrieving, and checking the presence of components of different types. These functionalities are fundamental for the dynamic construction and modification of entities, offering a modular approach to defining individual features of game objects.

### Private Methods of the Registry

Private methods, such as `addComponent`, `removeComponent`, `getComponent`, and `hasComponent`, encapsulate the internal logic needed to perform these operations on entities and their components. These private methods are used to ensure consistent updating of the internal registry when adding or removing components, contributing to the stability and coherence of the ECS system in the game engine.