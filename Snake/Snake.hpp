#ifndef SNAKE_HPP_SENTRY
#define SNAKE_HPP_SENTRY

#include "../Field/Field.hpp"
#include "../Food/Food.hpp"
#include "../MoveAndPosition/MoveAndPosition.hpp"

class GameHandler;
class GameHandlerGemstone;

class Snake
{
    friend class FieldHandler;
    friend class SnakeHandler;
    friend class GameHandler;
    struct item
    {
        Position pos;
        item *next;
        item(const Position &_pos) : pos(_pos), next(0) {}
    };
    item *first;
    item *last; // snakes head

    int id;

    MoveVector move;
    GameHandlerGemstone *the_master;

public:
    Snake() : first(0), last(0), move(0, 0), the_master(0) {}
    Snake(const Position &_pos, int _id, GameHandlerGemstone *_the_master)
        : first(new item(_pos)), last(first), id(_id),
          move(0, 0), the_master(_the_master) {}
    ~Snake()
    {
        while (first)
        {
            item *tmp = first->next;
            delete first;
            first = tmp;
        }
    }

    void Move();
    void ChangeDirection(MoveVector *mv);
    void Eat(Food *food);
};

#endif