#ifndef MOVEANDPOSITION_HPP_SENTRY
#define MOVEANDPOSITION_HPP_SENTRY

#include "../Point/Point.hpp"

class MoveVector : public Point
{
public:
    MoveVector(int x, int y) : Point(x, y) {}
    virtual ~MoveVector() {}
};

class Position : public Point
{
public:
    Position(int x, int y) : Point(x, y) {}
    virtual ~Position() {}
};

#endif