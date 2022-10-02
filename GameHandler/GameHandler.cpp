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
    void SnakeTruncate(Snake *s, Snake::item *to);
    void RemoveSnake(Snake *s);
    void AddSnake(Snake *s);

    // FoodHandler
    void AddFood();

    // FieldHandler
    void HandleOutOfField(Snake *s);

    // DrawHandler
    void DrawField();
    void DrawFieldFor(const Snake *s);
};

bool GameHandler::IsSnake(Snake *s)
{
    if (s->GetLen() == 1)
        return false;
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
            delete it;
            return true;
        }
    }
    delete it;
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
    foods->Push(new Food(rand() % x, rand() % y));
}

bool GameHandler::IsOtherSnake(Snake *s) // return false if it is not
                                         // neccessary to delete snakes
{
    List<Snake>::Iterator *it = snakes->Iterate();
    Snake::item *head = s->last;
    Snake::item *second_snake_start;
    while (it->More())
    {
        ListCursor<Snake> cr(it->Next());
        if (s != &(*cr))
        {
            if (cr->last == head)
            {
                delete it;
                return true;
            }
            second_snake_start = cr->first;
            while (second_snake_start != cr->last)
            {
                if (head->pos == second_snake_start->pos)
                {
                    SnakeTruncate(&(*cr), second_snake_start);
                    delete it;
                    return false;
                }
                second_snake_start = second_snake_start->next;
            }
        }
    }
    delete it;
    return false;
}

void GameHandler::SnakeTruncate(Snake *s, Snake::item *to)
{
    Snake::item *p = s->first;
    while (p != to)
    {
        Snake::item *tmp = p->next;
        delete p;
        s->len--;
        p = tmp;
    }
    s->first = p;
}

void GameHandler::RemoveSnake(Snake *s)
{
    List<Snake>::Iterator *it = snakes->Iterate();
    ListCursor<Snake> sn_c;
    while (it->More())
    {
        sn_c = it->Next();
        if (&(*sn_c) == s)
        {
            snakes->Remove(&sn_c);
            break;
        }
    }
    delete it;
}

void GameHandler::AddSnake(Snake *s)
{
    snakes->Push(s);
}

void GameHandler::DrawField()
{
    /*
        erase all field
        draw all food
        start drawing every snake
    */
    int x = field->GetSizeX() + 1;
    int y = field->GetSizeY();
    int i, j;
    for (i = 0; i < y; i++)
    {
        for (j = 0; j < x - 1; j++)
            field->field[i * x + j] = ' ';
        field->field[i * x + j] = '\n';
    }
    field->field[field->full_len - 1] = 0;
    List<Food>::Iterator *it_food = foods->Iterate();
    while (it_food->More())
    {
        ListCursor<Food> cr_food = it_food->Next();
        field->field[cr_food->GetX() + cr_food->GetY() * x] = '*';
    }
    delete it_food;
    List<Snake>::Iterator *it_snake = snakes->Iterate();
    while (it_snake->More())
    {
        ListCursor<Snake> cr_snake = it_snake->Next();
        Snake::item *p = cr_snake->first;
        while (p)
        {
            field->field[p->pos.GetX() + p->pos.GetY() * x] = '#';
            p = p->next;
        }
    }
    delete it_snake;
}

void GameHandler::DrawFieldFor(const Snake *s)
{
    int x = field->GetSizeX() + 1;
    List<Snake>::Iterator *it_snake = snakes->Iterate();
    while (it_snake->More())
    {
        ListCursor<Snake> cr_snake = it_snake->Next();
        if (&(*cr_snake) == s)
            field->field[cr_snake->last->pos.GetX() +
                         cr_snake->last->pos.GetY() * x] = '@';
        else
            field->field[cr_snake->last->pos.GetX() +
                         cr_snake->last->pos.GetY() * x] = '%';
    }
    delete it_snake;
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
GameHandlerGemstone::operator DrawHandler()
{
    return DrawHandler(handler);
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

bool SnakeHandler::IsOtherSnake(Snake *s)
{
    return handler->IsOtherSnake(s);
}

void SnakeHandler::SnakeTruncate(Snake *s, Snake::item *to)
{
    handler->SnakeTruncate(s, to);
}

void SnakeHandler::RemoveSnake(Snake *s)
{
    handler->RemoveSnake(s);
}

void SnakeHandler::AddSnake(Snake *s)
{
    handler->AddSnake(s);
}

/////////////////////////

DrawHandler::DrawHandler(GameHandler *_handler) : handler(_handler) {}

void DrawHandler::DrawField()
{
    handler->DrawField();
}

void DrawHandler::DrawFieldFor(const Snake *s)
{
    handler->DrawFieldFor(s);
}

/////////////////////////
