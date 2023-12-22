# Protocol

### This is a documentation for the communication between the server and the client

# TOC

- [Player](#player)
- [Position](#position)
- [Input](#input)

## Player

Message: `NEW ID POS TYPE`

This message is sent to the client to inform that a new player is created

## Position

Message: `POS [X] [Y] [MOV_SPEED] [DIRECTION]`

This message send the player position to the server

## Input

Messages:

- `UP`: Up key
- `DOWN`: Down key
- `RIGHT`: Right key
- `LEFT`: Left key
- `SHOOT`: Shoot key

Keys are binds on the client side
