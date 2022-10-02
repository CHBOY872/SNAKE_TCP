#include "Field.hpp"

Field::Field(int _size_x, int _size_y)
    : size_x(_size_x), size_y(_size_y),
      full_len((size_x + 1) * size_y + 1), field(new char[full_len])
{
}
Field::~Field()
{
    delete[] field;
}