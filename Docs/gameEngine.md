# GameEngine

### This is a technique documentation for explain the differents tools offered by the gameEngine

# Link to other documentation

* **You can find more information about the project [here](https://github.com/EpitechPromo2026/B-CPP-500-BDX-5-2-rtype-jules.trolle/wiki).**
* **You can find more technical information about the Server [here](server.md).**
* **You can find more technical information about the Client [here](client.md).**

# tables of contents

- [Technical Documentation Registry Class](#technical-documentation-registry-class)
  - [Methods](#methods)
  - [Features](#features)
  - [Usage](#usage)
  - [Example of use](#example-of-use)
- [Technical Documentation Game Systems](#technical-documentation-game-systems)
  - [shootingSystem](#shootingsystem)
  - [deathSystem](#deathsystem)
  - [damagedSystem](#damagedsystem)
  - [movementSystem](#movementsystem)
  - [noMoveSystem](#nomovesystem)
  - [collisionPlayer](#collisionplayer)
  - [collisionEnemy](#collisionenemy)
  - [collisionProjectile](#collisionprojectile)
  - [checkHitBox](#checkhitbox)
  - [collisionSystem](#collisionsystem)
  - [renderSystem](#rendersystem)
  - [Additional Details](#additional-details)
- [Technical Documentation Components](#technical-documentation-components)
  - [Position Component](#position-component)
  - [HealthPoint Component](#healthpoint-component)
  - [Velocity Component](#velocity-component)
  - [ID Component](#id-component)
  - [Speed Component](#speed-component)
  - [Damage Component](#damage-component)
  - [Size Component](#size-component)
  - [HitBox Component](#hitbox-component)
  - [Gravity Component](#gravity-component)
  - [Shooter Component](#shooter-component)
  - [Type Component](#type-component)
  - [Renderer Component](#renderer-component)

## Technical Documentation Registry Class

La classe `Registry` est responsable de la gestion des entités dans le système de jeu. Elle permet la création, la destruction et la manipulation d'entités ainsi que la gestion des composants associés à chaque entité.

### Methods

#### `Registry()`

- **Description:** Default class constructor `Registry`.

#### `~Registry()`

- **Description:** Default class destructor `Registry`.

#### `Entity createEntity()`

- **Description:** Creates a new entity with a unique identifier.
- **Return:** An instance of the `Entity` class representing the new entity.

#### `Entity createEntityWithID(int customID)`

- **Description:** Creates a new entity with the specified custom identifier.
- **Parameters:**
  - `customID`: Personalized entity identifier.
- **Return:** An instance of the `Entity` class representing the new entity.

#### `void destroyEntity(Entity entity)`

- **Description:** Destroys the specified entity.
- **Parameters:**
  - `entity`: The entity to be destroyed.

#### `Entity getEntity(size_t id)`

- **Description:** Retrieves an entity based on its identifier.
- **Parameters:**
  - `id`: Entity identifier.
- **Return:** An instance of the `Entity` class corresponding to the specified identifier.

#### `void setEntity(Entity& entityToCopy, int id)`

- **Description:** Replaces the existing entity with a new entity specified by its identifier.
- **Parameters:**
  - `entityToCopy`: New entity to copy.
  - `id`: Identifier of the entity to be replaced.

#### `Entity getPlayer()`

- **Description:** Recovers the player's entity.
- **Return:** An instance of the `Entity` class representing the player entity.

#### `Entity getFirstEnemy()`

- **Description:** Recover the first enemy entity.
- **Return:** An instance of the `Entity` class representing the first enemy entity.

#### `bool hasEntity(size_t id)`

- **Description:** Checks whether an entity with the specified identifier exists.
- **Parameters:**
  - `id`: Identifier of the entity to be verified.
- **Return:** `true` if the entity exists, otherwise `false`.

#### `std::vector<Entity> getListEntities(Enemy()`

- **Description:** Retrieves a list of enemy entities.
- **Return:** A vector of instances of the `Entity` class representing enemy entities.

#### `std::vector<Entity> getListPlayers()`

- **Description:** Retrieves a list of player entities.
- **Return:** A vector of instances of the `Entity` class representing player entities.

#### `std::vector<Entity> getListEntities()`

- **Description:** Retrieves a list of all entities.
- **Return:** A vector of instances of the `Entity` class, representing all entities.

#### `std::vector<Entity> getListEntities(Player_Projectile)`

- **Description:** Retrieves a list of players' projectiles.
- **Return:** A vector of instances of the `Entity` class representing player projectiles.

#### `std::vector<Entity> deletePlayersProjectile(int id)`

- **Description:** Deletes projectiles from the player specified by its ID.
- **Parameters:**
  - `id`: Identifier of the player whose shots are to be deleted.
- **Return:** A vector of instances of the `Entity` class after deleting projectiles.

#### `std::vector<Entity> deleteEnnemy(int id)`

- **Description:** Deletes the enemy specified by its ID.
- **Parameters:**
  - `id`: Identifier of the enemy to be deleted.
- **Return:** A vector of instances of the `Entity` class after the enemy has been deleted.

#### `void deleteById(int id)`

- **Description:** Deletes the entity specified by its identifier.
- **Parameters:**
  - `id`: Identifier of the entity to be deleted.

#### `void destroyEnnemy(std::vector<Entity> ennemyList)`

- **Description:** Destroys specified enemy entities.
- **Parameters:**
  - `ennemyList`: Vector of enemy entities to destroy.

#### `template <typename T> Entity addComponent(Entity entity, T component)`

- **Description:** Adds a component to the specified entity.
- **Parameters:**
  - `entity`: The entity to which to add the component.
  - `component`: The component to be added.
- **Return:** The entity updated with the new component.

#### `template <typename T> void removeComponent(Entity entity, T component)`

- **Description:** Removes a component from the specified entity.
- **Parameters:**
  - `entity`: The entity to delete the component from.
  - `component`: The component to be deleted.

#### `template <typename T> T& getComponentT(Entity& entity, T component, const char* file, const char* fn, int line)`

- **Description:** Retrieves the specified component from the entity.
- **Parameters:**
  - `entity`: The entity from which to retrieve the component.
  - `component`: The type of component to retrieve.
  - `file`: Name of the file calling the function.
  - `fn`: Name of the function calling the function.
  - `line`: Line number of the function call.
- **Return:** A reference to the specified component.
- **Exceptions:** Throws an exception if the component is not found.

#### `template <typename T> bool hasComponent(Entity& entity, T component)`

- **Description:** Checks whether the entity has the specified component.
- **Parameters:**
  - `entity`: The entity to be verified.
  - `component`: The component to verify.
- **Return:** `true` if the entity has the component, otherwise `false`.

### Features

#### `std::vector<Entity> m_entities`

- **Description:** Vector containing all the entities managed by the registry.

#### `sf::RenderWindow m_window`

- **Description:** SFML rendering window associated with the register.

#### `size_t m_id`

- **Description:** Variable to generate unique identifiers for entities.

### Usage

The `Registry` class is used for the central management of entities in the game system. Developers can create, destroy, add components and interact with entities using the methods provided by this class.

### Example of use

```cpp
// Creating a register
Registry registry;

// Entity creation
Entity playerEntity = registry.createEntity();

// Add a component to the player entity
playerEntity = registry.addComponent(playerEntity, PlayerComponent("John Doe", 100));

// Checking the existence of a component
bool hasPlayerComponent = registry.hasComponent(playerEntity, PlayerComponent);

// Retrieving a component
PlayerComponent& player = registry.getComponentT(playerEntity, PlayerComponent, __FILE__, __func__, __LINE__);
```

---

## Technical Documentation Game Systems

game systems implemented in the supplied C++ code. Systems are functions that manage specific aspects of the game, such as shooting, collisions, movement, death, etc. These systems are intended for use in an entity-based game engine.

### shootingSystem

#### Description

The shootingSystem manages the shooting behavior of entities. It checks whether an entity has the Shooter and Position components, then creates a projectile based on position and velocity.

#### Parameters

- `Entity entity`: The entity for which the system is applied.
- `Registry& registry`: A reference to the game's register.

#### How it works

1. Checks whether the entity has Shooter and Position components. If not, Return immediately.
2. Checks if the entity is shooting using the Shooter component.
3. If yes, retrieves the entity's position and creates a projectile using position and velocity.

---

### deathSystem

#### Description

The death system is responsible for destroying an entity if it has used up all its life points.

#### Parameters

- `Entity entity`: The entity for which the system is applied.
- `Registry& registry`: A reference to the game registry.

#### How it works

1. Checks if the entity has the HealthPoint component. If not, Return immediately.
2. Checks if the entity's life points are less than or equal to zero.
3. If so, destroys the entity using the register.

---

### damagedSystem

#### Description

The damage system is responsible for reducing an entity's hit points as a result of damage inflicted by another entity.

#### Parameters

- `Entity entity`: The entity inflicting the damage.
- `Entity otherEntity`: The entity taking the damage.
- `Registry& registry`: A reference to the game registry.

#### How it works

1. Checks whether the inflicting entity has the Damage component and whether the inflicted entity has the HealthPoint component. If not, Return immediately.
2. Reduces the hit entity's hit points according to the damage inflicted by the inflicting entity.

---

### movementSystem

#### Description

The displacement system is responsible for moving an entity according to its speed and current position.

#### Parameters

- `Entity entity`: The entity to be moved.
- `Registry& registry`: A reference to the game's register.

#### How it works

1. Checks if the entity has Speed, Velocity and Position components. If not, Return immediately.
2. Updates the entity's position according to its current speed and direction.
3. Resets the entity's speed after moving.

---

### noMoveSystem

#### Description

The no movement system is responsible for moving two entities towards each other without taking their speed into account.

#### Parameters

- `Entity entity`: The first entity.
- `Entity otherEntity`: The second entity.
- `Registry& registry`: A reference to the game registry.

#### How it works

1. Checks whether both entities have the Position component. If not, Return immediately.
2. Moves the first entity to the right and the second entity to the left.

---

### collisionPlayer

The player collision system is responsible for managing interactions between the player entity and other entities in the game.

#### Parameters

- `const Entity& entity`: The player's entity.
- `Entity otherEntity`: The other entity involved in the collision.
- `Registry& registry`: A reference to the game registry.

#### How it works

1. Checks if the `otherEntity` entity has the `Type` component. If so, Return immediately.
2. Checks if `otherEntity` is a player projectile. If so, Return immediately.
3. Handles collisions with enemy entities by calling `damagedSystem`.
4. Handles collisions with player or wall entities by calling `noMoveSystem`.

---

### collisionEnemy

The enemy collision system is responsible for managing interactions between the enemy entity and other entities in the game.

#### Parameters

- `const Entity& entity`: The enemy entity.
- `Entity otherEntity`: The other entity involved in the collision.
- `Registry& registry`: A reference to the game registry.

#### How it works

1. Checks if `otherEntity` has the `Type` component. If so, Return immediately.
2. Checks if `otherEntity` is an enemy projectile or an enemy entity. If so, Return immediately.
3. Handles collisions with player or player projectile entities by calling `damagedSystem`.
4. Handles collisions with wall-type entities by calling `noMoveSystem`.

---

### collisionProjectile

The projectile collision system is responsible for managing interactions between projectiles and other entities in the game.

#### Parameters

- `const Entity& entity`: The projectile entity.
- `Entity otherEntity`: The other entity involved in the collision.
- `Registry& registry`: A reference to the game registry.

#### How it works

1. Checks if `otherEntity` has the `Type` component. If so, Return immediately.
2. Checks if `otherEntity` is a projectile or a player entity. If so, Return immediately.
3. Handles collisions with enemy entities by calling `damagedSystem`.
4. Handles collisions with wall-type entities by destroying the projectile.

---

### checkHitBox

The `checkHitBox` function checks whether a point defined by coordinates (x, y) is inside a bounding box defined by its `origin` and `end` corners.

#### Parameters

- `float x`: x coordinate of the point to be checked.
- `float y`: Y coordinate of the point to be checked.
- `std::pair<float, float> origin`: Coordinates of the upper left corner of the bounding box.
- `std::pair<float, float> end`: Coordinates of the lower right corner of the bounding box.

#### Return

- `bool`: Returns `true` if the point is inside the bounding box, otherwise `false`.

---

### collisionSystem

The collision management system is responsible for detecting and managing collisions between an entity and a specified list of entities.

#### Parameters

- `Entity entity`: The entity for which the system is applied.
- `std::vector<Entity> entities`: The list of entities with which to check for collisions.
- `Registry& registry`: A reference to the game registry.

#### How it works

1. Checks if the entity has the `HitBox` and `Type` components. If not, Return immediately.
2. Determines the entity's type using the `Type` component.
3. Scans the list of entities and handles collisions by calling the appropriate function according to the entity type.

---

### renderSystem

The rendering system is responsible for graphically displaying an entity on an SFML window.

#### Parameters

- `Entity entity`: The entity for which the system is applied.
- `Registry& registry`: A reference to the game registry.
- `sf::RenderWindow& window`: The SFML window on which to render.

#### How it works

1. Checks if the entity has the `Renderer`, `Position`, and `Type` components. If not, Return immediately.
2. Retrieves the `Type` component from the entity to determine the entity type.
3. If the entity is a player (`EntityType::Player`), retrieves its position.
4. Retrieves the entity's texture and sprite from the `Renderer` components.
5. Adjusts the sprite scale according to the size defined by the `Size` component.
6. Positions the sprite according to the entity coordinates obtained from the `Position` component.
7. Applies texture to sprite.
8. Draws the sprite on the SFML window.

---

### Additional Details

#### Player Entity Rendering

If the entity is of type player (`EntityType::Player`), the entity's position is retrieved. This can be useful for specific player rendering functionalities.

#### Component Management

- `Renderer`: Provides the texture and sprite needed for rendering.
- `Position`: Provides the position coordinates of the entity.
- `Type`: Allows you to determine the entity type for specific rendering functionalities.
- `Size`: Used to adjust the scale of the sprite based on the size of the entity.

#### SFML rendering

The function uses the SFML library to render. It draws the entity sprite on the SFML window.

---

## Technical Documentation Components

This documentation provides a detailed description of the components used in the game system. These components are essential for defining the characteristics and behavior of entities.

### Position Component

#### Description

The `Position` component represents the spatial coordinates of an entity in two-dimensional space.

#### Methods

##### `Position()`

- Default constructor.

##### `Position(std::pair<int, int> originPos)`

- Constructor to initialize position coordinates with a pair of integers.

##### `~Position()`

- Default destructor.

##### `std::pair<int, int> getPosition() const`

- Returns the current position coordinates.

##### `void setPosition(std::pair<int, int> newPos)`

- Modify position coordinates.

---

### HealthPoint Component

#### Description

The `HealthPoint` component represents the number of health points of an entity.

#### Methods

##### `HealthPoint()`

- Default constructor.

##### `HealthPoint(float hp)`

- Constructor to initialize life points with a floating value.

##### `~HealthPoint()`

- Default destructor.

##### `float getHealthPoint() const`

- Returns the current number of hit points.

##### `void setHealthPoint(float mLp)`

- Modify the number of hit points.

---

### Velocity Component

#### Description

The `Velocity` component represents the speed of an entity in two-dimensional space.

#### Methods

##### `Velocity()`

- Default constructor.

####

##### `~Velocity()`

- Default destructor.

##### `std::pair<float, float> getVelocity() const`

- Returns the x and y components of the speed.

##### `void setVelocity(float x, float y)`

- Modify the x and y components of the speed.

---

### ID Component

#### Description

The `ID` component represents the unique identifier of an entity.

#### Methods

##### `ID()`

- Default constructor.

##### `ID(std::size_t id)`

- Constructor allowing the identifier to be initialized with a value of size_t.

##### `~ID()`

- Default destructor.

##### `std::size_t getID() const`

- Returns the unique identifier.

---

### Speed Component

#### Description

The `Speed` component represents the speed of movement of an entity.

#### Methods

##### `Speed()`

- Default constructor.

##### `Speed(float speed)`

- Constructor to initialize the speed with a float value.

##### `~Speed()`

- Default destructor.

##### `float getSpeed() const`

- Returns the speed value.

##### `void setSpeed(float newSpeed)`

- Modify the speed value.

---

### Damage Component

#### Description

The `Damage` component represents the amount of damage an entity can inflict.

#### Methods

##### `Damage()`

- Default constructor.

##### `Damage(float damage)`

- Constructor to initialize damage with a float value.

##### `~Damage()`

- Default destructor.

##### `float getDamage() const`

- Returns the damage value.

##### `void setDamage(int newDamage)`

- Modify the value of the damage.

---

### Size Component

#### Description

The `Size` component represents the size of an entity.

#### Methods

##### `Size()`

- Default constructor.

##### `Size(std::pair<float, float> originSize)`

- Constructor to initialize size with a pair of float values.

##### `~Size()`

- Default destructor.

##### `std::pair<float, float> getSize() const`

- Returns the current size.

##### `void setSize(std::pair<float, float> newSize)`

- Modify the value of the size.

---

### HitBox Component

#### Description

The `HitBox` component represents a hit box associated with an entity.

#### Methods

##### `HitBox()`

- Default constructor.

##### `HitBox(std::pair<float, float> originPos, std::pair<float, float> size)`

- Constructor used to initialize the position and size of the collision box.

##### `~HitBox()`

- Default destructor.

##### `std::pair<float, float> getOriPos() const`

- Returns the original position of the collision box.

##### `std::pair<float, float> getSize() const`

- Returns the current size of the collision box.

##### `void setHitBoxPosition(std::pair<float, float> originPos, std::pair<float, float> size)`

- Modify the position and size of the collision box.

---

### Gravity Component

#### Description

The `Gravity` component manages the gravity properties of an entity, specifying the strength of gravity and whether it is active or not.

#### Methods

##### `Gravity()`

- Default constructor.

##### `Gravity(float gravity, bool isGravity)`

- Constructor used to initialize the force of gravity and its activation state.

##### `~Gravity()`

- Default destructor.

##### `float getGravity() const`

- Returns the force of gravity.

##### `bool isGravity() const`

- Returns the gravity activation state.

##### `void setGravity(float newGravity)`

- Modify the force of gravity.

##### `void setIsGravity(bool isGravity)`

- Modify the state of gravity activation.

---

### Shooter Component

#### Description

The `Shooter` component manages the shooting behavior of an entity, specifying whether it is shooting or not.

#### Methods

##### `Shooter()`

- Default constructor.

##### `Shooter(bool isShooting)`

- Constructor used to initialize the firing state.

##### `~Shooter()`

- Default destructor.

##### `bool isShooting() const`

- Returns the entity's firing state.

##### `void setIsShooting(bool isShooting)`

- Modify the entity's firing state.

---

### Type Component

#### Description

The `Type` component specifies the type of an entity from the `EntityType` enumeration. It also provides a display operator overload to display the type as a string.

#### Methods

##### `Type()`

- Default constructor.

##### `Type(EntityType entityType)`

- Constructor used to initialize the entity type.

##### `~Type()`

- Default destructor.

##### `EntityType getEntityType() const`

- Returns the entity type.

##### `void setEntityType(EntityType entityType)`

- Modify the type of the entity.

##### `friend std::ostream& operator<<(std::ostream& os, const Type& type)`

- Display operator overload to display the type.

---

### Renderer Component

#### Description

The `Renderer` component manages the graphic properties of an entity, such as its texture and sprite.

#### Methods

##### `Renderer()`

- Default constructor.

##### `explicit Renderer(const std::string& texturePath)`

- Constructor to initialize the component with a texture path.

##### `~Renderer()`

- Default destructor.

##### `sf::Sprite& getRenderer()`

- Returns the rendering sprite reference.

##### `sf::Texture getTexture() const`

- Returns the texture of the component.

##### `void setRenderer(const std::string& texturePath)`

- Modify the texture and sprite of the component.

---
