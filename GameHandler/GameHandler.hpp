#ifndef GAMEHANDLER_HPP_SENTRY
#define GAMEHANDLER_HPP_SENTRY

#include "../Snake/Snake.hpp"
#include "../List/List.hpp"
#include "../Food/Food.hpp"

class Snake;

class GameHandler;
class FoodHandler;
class FieldHandler;
class SnakeHandler;

class GameHandlerGemstone
{
    GameHandler *handler;

public:
    GameHandlerGemstone(Field *_field,
                        List<Food> *_foods, List<Snake> *_snakes);
    ~GameHandlerGemstone();

    operator GameHandler();
    operator FoodHandler();
    operator FieldHandler();
    operator SnakeHandler();
};

class FoodHandler
{
    GameHandler *handler;

public:
    FoodHandler(GameHandler *_handler);
    void AddFood();
};

class FieldHandler
{
    GameHandler *handler;

public:
    FieldHandler(GameHandler *_handler);
    void HandleOutOfField(Snake *s);
};

class SnakeHandler
{
    GameHandler *handler;

public:
    SnakeHandler(GameHandler *_handler);
    bool IsSnake(Snake *s); // check on own collision, returns true, if it was
                            // a collision
    bool IsFood(Snake *s);
};

#endif