#include "B.h"
#include <iostream>
//namespace list;

template <class T>
list::ListItem::ListItem()
{
	next = NULL;
	prev = NULL;
	data = NULL;
}
/*
template <class T>
ListItem::ListItem(T data, ListItem *next, ListItem *prev)
{
	data_ = data;
	next_ = next;
	prev_ = prev;
}



ListItem::ListItem(const &l)
{
	data = l.data;
	next = l.next;
	prev = l.prev;
}

template <class T>
//добавление элемента в начало
void list::add_first_elem(T element)
{
	ListItem *new_elem = new ListItem;
	new_elem ->data = element;
	new_elem ->next = head;
//	new_elem ->prev = head;
	head = new_elem;
}

template <class T>
//добавление элемента в конец
void list::add_last_elem(T element)
{
        ListItem *new_elem = new ListItem;
        new_elem ->data = element;
//        new_elem ->next = head;
        new_elem ->prev = last;
        head = new_elem;
}


//удаление первого элемента
void list::del_first_elem()
{
	ListItem *item;
	item = head;
	head = head->next;


}

//удаление последнего элемента
void list::del_last_elem()
{
        ListItem *item;
        item = last;
        last = last->prev;
}

//шаг вперёд
void list::go_next()
{
	current = current->next;
}

//шаг назад
void list::go_back()
{
        current = current->prev;
}


void list::print()
{
	ListItem *elem;
	elem  = get_first();

//проверка, что следующий элемент есть

	while (elem -> next != NULL)
	{
		printf ("%d\n", elem->current);
		go_next();
	}
}


void list::get_first()
{
	ListItem *current = new ListItem;
	current->prev = NULL;
	current->data = head;
	current->next = head->next;
}

template <class T>
void list::add_after_elem(T element, ListItem &item)
{
//if next || prev == null  ???
	ListItem *new_item = new ListItem;

	new_item->prev = *item->data;
	new_item->data = element;
	new_item->next = *item->next;

	item->next = *element;
	item->next->prev = *element; //но это не точно, пусть пока так будет
}

template <class T>
void list::add_before_elem(T element, ListItem &item)
{
//if next || prev == null  ???
        ListItem *new_item = new ListItem;

        new_item->prev = *item->prev;
        new_item->data = element;
        new_item->next = *item->data;

        item->prev = *element;
        item->prev->next = *element; //но это не точно, пусть пока так будет
}

template <class T>
void list::del_elem(ListItem &item)
{
//if next || prev == null  ???

	item->prev->next = *item->next;
	item->next->prev = *item->prev;

}

template <typename T>
void list::swap_elem(ListItem &item, ListItem &elem)
{
//if next || prev == null  ???



}

//list list::operator = (const list &other)
//{

//}
*/
