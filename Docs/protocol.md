# Protocol

### This is a documentation for the communication between the server and the client

# Tables of Contents

- [Entites](#entites)
    - [Player](#player)
- [Position](#position)
- [Input](#input)
- [Update](#update)
    - [Update entites](#update-entites)

## Entites

### Player

Message: `NEW [X] [Y] [TYPE]`

This message is sent to the client when a new player is created


## Position

Message: `NEW_POS [X] [Y]`

This message send the player position to the client

## Input

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
