#ifndef FOOD_HPP_SENTRY
#define FOOD_HPP_SENTRY

#include "../MoveAndPosition/MoveAndPosition.hpp"

class Food : public Position
{
public:
    Food(int x, int y) : Position(x, y) {}
    virtual ~Food() {}
};

#endif