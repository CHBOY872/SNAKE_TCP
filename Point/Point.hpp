#ifndef POINT_HPP_SENTRY
#define POINT_HPP_SENTRY

class Point
{
    int pos_x, pos_y;

public:
    Point(int _pos_x = 0, int _pos_y = 0) : pos_x(_pos_x), pos_y(_pos_y) {}
    virtual ~Point() {}

    int GetX() { return pos_x; }
    int GetY() { return pos_y; }
    void SetX(int _pos_x) { pos_x = _pos_x; }
    void SetY(int _pos_y) { pos_y = _pos_y; }

    Point &operator=(const Point &a)
    {
        if (this != &a)
        {
            pos_x = a.pos_x;
            pos_y = a.pos_y;
        }
        return *this;
    }
    bool operator==(const Point &a)
    {
        return pos_x == a.pos_x && pos_y == a.pos_y;
    }
    const Point &operator+=(const Point &a)
    {
        pos_x += a.pos_x;
        pos_y += a.pos_y;
        return *this;
    }
    Point operator+(const Point &a)
    {
        return Point(a.pos_x + pos_x, a.pos_y + pos_y);
    }
};

#endif