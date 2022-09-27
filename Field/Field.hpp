#ifndef FIELD_HPP_SENTRY
#define FIELD_HPP_SENTRY

class FieldHandler;

class Field
{
    friend class Fieldhandler;
    int size_x;
    int size_y;
    char **field;

public:
    Field(int _size_x, int _size_y);
    ~Field();

    int GetSizeX() { return size_x; }
    int GetSizeY() { return size_y; }
};

#endif