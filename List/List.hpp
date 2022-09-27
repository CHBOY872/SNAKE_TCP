#ifndef LIST_HPP_SENTRY
#define LIST_HPP_SENTRY

template <class T>
class ListCursor;

template <class T>
class List
{
    friend class ListCursor<T>;
    struct item
    {
        T *val;
        item *next;
    };
    item *first;

public:
    List() : first(0) {}
    ~List()
    {
        while (first)
        {
            item *p = first->next;
            delete first->val;
            delete first;
            first = p;
        }
    }

    void Push(T *val)
    {
        item *tmp = new item;
        tmp->val = val;
        tmp->next = first;
        first = tmp;
    }

    void Pop()
    {
        item *tmp = first->next;
        delete first->val;
        delete first;
        first = tmp;
    }

    void Remove(ListCursor<T> *cursor);

    class Iterator
    {
        friend class List<T>;
        List<T> *the_master;
        item **first;
        Iterator(List<T> *_the_master, item **_first)
            : the_master(_the_master), first(_first) {}

    public:
        bool More() { return (*first); }
        ListCursor<T> Next();
    };

    Iterator *Iterate() { return new Iterator(this, &first); }
};

template <class T>
class ListCursor
{
    friend class List<T>;
    List<T> *the_master;
    typename List<T>::item **itm;

public:
    ListCursor(List<T> *_the_master, typename List<T>::item **_itm)
        : the_master(_the_master), itm(_itm) {}

    operator T *() { return (*itm)->val; }
    T *operator->() { return (*itm)->val; }
};

template <class T>
void List<T>::Remove(ListCursor<T> *cursor)
{
    item *tmp = (*cursor->itm)->next;
    delete (*cursor->itm);
    (*cursor->itm) = tmp;
}

template <class T>
ListCursor<T> List<T>::Iterator::Next()
{
    ListCursor<T> res(the_master, first);
    first = &(*first)->next;
    return res;
}

#endif