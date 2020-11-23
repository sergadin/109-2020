#include "B_1.h"

template <class T>
list<T>::list()
{
	ListItem *current = new ListItem;
        current->next = NULL;
        current->prev = NULL;
        current->data = NULL;
}


//добавление элемента в конец
template <class T>
void list<T>::add_last_elem(T element)
{
        ListItem *new_elem = new ListItem;
        new_elem ->data = element;
        new_elem ->prev = last;
        last = new_elem;
}


//добавление элемента в начало
template <class T>
void list<T>::add_first_elem(T element)
{
        ListItem *new_elem = new ListItem;
        new_elem ->data = element;
        new_elem ->next = first;
        first = new_elem;
}

//удаление первого элемента
template <class T>
void list<T>::del_first_elem()
{
        first->data = first->next;//пока думаю над этим

}


