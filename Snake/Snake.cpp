#include "Snake.hpp"

void Snake::Move()
{
    if (move == Position(0, 0))
        return;
    item *tmp;
    for (tmp = first; tmp->next; tmp = tmp->next)
        tmp->pos = tmp->next->pos;
    last->pos += move;
    ((FieldHandler)*the_master).HandleOutOfField(this);
}

void Snake::ChangeDirection(MoveVector *mv)
{
    if (*mv == move)
        return;
    move = *mv;
}

void Snake::Eat(Food *food)
{
    item *tmp = new item(*food);
    tmp->pos += move;
    last->next = tmp;
    last = tmp;
}