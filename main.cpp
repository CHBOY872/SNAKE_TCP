#include <stdio.h>
#include "Point/Point.hpp"
#include "Field/Field.hpp"
#include "Snake/Snake.hpp"
#include "GameHandler/GameHandler.hpp"

int main()
{
    Field fld(19, 20);
    List<Food> fod;
    List<Snake> snakes;
    GameHandlerGemstone handler(&fld, &fod, &snakes);
    Snake *s = new Snake(Position(20, 6), 1, &handler);
    snakes.Push(s);
    MoveVector mv(1, 0);
    s->Move();
    s->ChangeDirection(&mv);
    s->Move();
    return 0;
}