#include "B.h"

//template <typename T>

ListItem::ListItem()
{
	next = NULL;
	prev = NULL;
	data = NULL;
}

template <typename T>

ListItem::ListItem(T data, ListItem *next, ListItem *prev)
{
	data_ = data;
	next_ = next;
	prev_ = prev;
}


//добавление элемента в начало


template <class T>
void list::add_elem(T element)
{
//	ListItem current = new ListItem;
//	currernt->next = data;
}
