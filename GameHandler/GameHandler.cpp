#include <stdlib.h>

#include "GameHandler.hpp"

class GameHandler
{
    Field *field;
    List<Food> *foods;
    List<Snake> *snakes;

public:
    GameHandler(Field *_field, List<Food> *_foods, List<Snake> *_snakes)
        : field(_field), foods(_foods), snakes(_snakes) {}
    ~GameHandler() {}

    // SnakeHandler
    bool IsSnake(Snake *s); // check on own collision, returns true, if it was
                            // a collision
    bool IsFood(Snake *s);
    bool IsOtherSnake(Snake *s);

    // FoodHandler
    void AddFood();

    // FieldHandler
    void HandleOutOfField(Snake *s);
};

bool GameHandler::IsSnake(Snake *s)
{
    Snake::item *head = s->last;
    Snake::item *p;
    for (p = s->first; p != head; p = p->next)
    {
        if (head->pos == p->pos)
            return true;
    }
    return false;
}

bool GameHandler::IsFood(Snake *s)
{
    List<Food>::Iterator *it = foods->Iterate();
    while (it->More())
    {
        ListCursor<Food> cr(it->Next());
        if (*cr == s->last->pos)
        {
            s->Eat(&(*cr));
            foods->Remove(&cr);
            AddFood();
            return true;
        }
    }
    return false;
}

void GameHandler::HandleOutOfField(Snake *s)
{
    int max_x = field->GetSizeX();
    int max_y = field->GetSizeY();
    if (s->last->pos.GetX() >= max_x)
        s->last->pos.SetX(0);
    if (s->last->pos.GetY() >= max_y)
        s->last->pos.SetY(0);
    if (s->last->pos.GetX() < 0)
        s->last->pos.SetX(max_x - 1);
    if (s->last->pos.GetY() < 0)
        s->last->pos.SetY(max_y - 1);
}

void GameHandler::AddFood()
{
    int x = field->GetSizeX();
    int y = field->GetSizeY();
    Food food(rand() % x, rand() % y);
    foods->Push(&food); // IN PUSH METHOD A NEW OBJECT WILL BE CREATED
                        // ACCORDING TO PARAMETERS WHICH WAS WRITTEN
                        // IN food OBJECT
}

/////////////////////////

GameHandlerGemstone::
    GameHandlerGemstone(Field *_field,
                        List<Food> *_foods, List<Snake> *_snakes)
    : handler(new GameHandler(_field, _foods, _snakes)) {}
GameHandlerGemstone::~GameHandlerGemstone() { delete handler; }

GameHandlerGemstone::operator FoodHandler()
{
    return FoodHandler(handler);
}
GameHandlerGemstone::operator FieldHandler()
{
    return FieldHandler(handler);
}
GameHandlerGemstone::operator SnakeHandler()
{
    return SnakeHandler(handler);
}

/////////////////////////

FoodHandler::FoodHandler(GameHandler *_handler) : handler(_handler) {}

void FoodHandler::AddFood()
{
    handler->AddFood();
}

/////////////////////////

FieldHandler::FieldHandler(GameHandler *_handler) : handler(_handler) {}

void FieldHandler::HandleOutOfField(Snake *s)
{
    handler->HandleOutOfField(s);
}

/////////////////////////

SnakeHandler::SnakeHandler(GameHandler *_handler) : handler(_handler) {}
bool SnakeHandler::IsSnake(Snake *s)
{
    return handler->IsSnake(s);
}

bool SnakeHandler::IsFood(Snake *s)
{
    return handler->IsFood(s);
}

/////////////////////////