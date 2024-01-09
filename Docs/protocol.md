# Protocol

### This is a documentation for the communication between the server and the client

# Tables of Contents

- [Entites](#entites)
    - [Player](#player)
    - [Ennemy](#ennemy)
    - [Player Projectile](#Player-Projectile)
- [Server](#Server)
    - [Login](#Login)
    - [Position](#position)
    - [Input](#input)
- [Update](#update)
    - [Update entites](#update-entites)

## Entites

### Player

Message: `NEW_PLAYER [ID] [X] [Y] [TYPE]`

This message is sent to the client when a new player is created

### Ennemy

Message: `NEW_ENNEMY [ID] [X] [Y] [TYPE]`

This message is sent to the client when a new ennemy is created

Message: `MOVE_ENNEMY [ID]`

This message is sent to the client when a ennemy is moved

Message: `DELETE_ENNEMY [ID]`

This message is sent to the client when a ennemy is move


### Player Projectile

Message: `PLAYER_PROJECTILE [ID] [X] [Y] [TYPE]`

This message is sent to the client when a new projectile is created  

Message `MOVE_PROJECTILE [ID]`

This message is sent to the client when a projectile is moved  

Message: `DELETE_PROJECTILE [ID]`

This message is sent to the client when a projectile is deleted

## Server

### Login

Message: `LOGIN`

This message sent by the client when conecting to the server to create a player in the game

### Position

Message: `NEW_POS [X] [Y]`

This message send the player position to the client

### Input

Messages:

- `[UP] [ID]`: Up key
- `[DOWN] [ID]`: Down key
- `[RIGHT] [ID]`: Right key
- `[LEFT] [ID]`: Left key
- `[SHOOT] [ID]`: Shoot key

Keys are binds on the client side


## Update

### Update entites
Message:
```
UPDATE
[ID] [X] [Y] [TYPE]
[ID] [X] [Y] [TYPE]
[ID] [X] [Y] [TYPE]
```

This message send all entites currently created on the server

## Error

Message: `Unknown command: [CMD]`

This message is send when the command is not konw in the server side

Message: `Error in handleReceive`

This message is send when an error is ocuring in the client side.