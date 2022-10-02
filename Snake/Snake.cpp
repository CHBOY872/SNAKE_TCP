#include "../GameHandler/GameHandler.hpp"
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
    if (*mv == move || *mv == MoveVector(0, 0))
        return;
    move = *mv;
}

void Snake::Eat(Food *food)
{
    item *tmp = new item(first->pos);
    tmp->pos -= move;
    tmp->next = first;
    first = tmp;
    len++;
}
