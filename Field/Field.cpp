#include "Field.hpp"

Field::Field(int _size_x, int _size_y) : size_x(_size_x), size_y(_size_y)
{
    field = new char *[_size_y];
    int i;
    for (i = 0; i < _size_y; i++)
    {
        field[i] = new char[_size_x];
        int j;
        for (j = 0; j < _size_x; j++)
            field[i][j] = 0;
    }
}
Field::~Field()
{
    int i;
    for (i = 0; i < size_y; i++)
        delete[] field[i];
    delete[] field;
}