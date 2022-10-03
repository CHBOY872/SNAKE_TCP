#include "Food.hpp"
#include "../List/List.hpp"

template <>
void List<Food>::Remove(ListCursor<Food> *cursor)
{
    item *tmp = (*cursor->itm)->next;
    delete (*cursor->itm)->val;
    delete (*cursor->itm);
    (*cursor->itm) = tmp;
}