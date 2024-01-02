# Protocol

### This is a documentation for the communication between the server and the client

# TOC

- [Position](#position)
- [Input](#input)
- [Update](#update)
    - [Update entites](#update-entites)


## Position

Message: `POS [X] [Y] [MOV_SPEED] [DIRECTION]`

This message send the player position to the server

## Input

Messages:

- `[UP]`: Up key
- `[DOWN]`: Down key
- `[RIGHT]`: Right key
- `[LEFT]`: Left key
- `[SHOOT]`: Shoot key

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
