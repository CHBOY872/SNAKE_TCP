#ifndef FIELD_HPP_SENTRY
#define FIELD_HPP_SENTRY

class FieldHandler;
class GameHandler;

class Field
{
    friend class Fieldhandler;
    friend class GameHandler;
    int size_x;
    int size_y;
    int full_len;
    char *field;

public:
    Field(int _size_x, int _size_y);
    ~Field();

    int GetFullLen() { return full_len; }
    const char *GetField() { return field; }
    int GetSizeX() { return size_x; }
    int GetSizeY() { return size_y; }
};

#endif