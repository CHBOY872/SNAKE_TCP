# SNAKE_TCP/IP

Snake TCP/IP is an online game which was written in C++ language. Spend your time playing that game and finding some bugs and errors! :)

## How to build

Type in terminal
```
./build.sh
```
to build a game

## How to play

The standard size of field is 79x19, food count is 10 but you can change it in `src/main.cpp` file and rebuild a game.
The standard time of updating a field is 500000 usec, but you can change it in `src/Server/Server.cpp` file and rebuild a game.

If you want to start moving or change direction, you should use key `WASD` keys and `Enter`.
Type one of `WASD` keys and press `Enter` to send to server the key you wrote.

- `*` Food which you should eat
- `@` YOUR Snakes head
- `%` OTHER PLAYERS Snakes head
- `#` Snakes body

You should eat a food, thus your snake will grow.

You can eat the body of another snake, thus reducing other snakes size.

If you stumble to other snakes head, you and another player who plays another snake quit from game.
