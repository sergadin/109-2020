#include "B.h"

ListItem::ListItem()
{
	next = NULL;
	prev = NULL;
	data = NULL;
}


ListItem::ListItem(T data, ListItem *next, ListItem *prev)
{
	data_ = data;
	next_ = next;
	prev_ = prev;
}


//добавление элемента в начало
void list::add_first_elem(T element)
{
	ListItem *new_elem = new ListItem;
	new_elem ->data = element;
	new_elem ->next = head;
//	new_elem ->prev = head;
	head = new_elem;
}

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

void list::del_last_elem()
{
        ListItem *item;
        item = last;
        last = last->prev;
}


void list::go_next()
{
	current = current->next;
}

void list::go_back()
{
        current = current->prev;
}


void list::print()
{
	ListItem *elem;
	elem  = get_first();

	while (elem -> next != NULL)
	{
		printf ("%d\n", elem->current);
		go_next();
	}
}

void list::get_first()
{
	return head;
}

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

void list::del_elem(ListItem &item)
{
//if next || prev == null  ???

	item->prev->next = item->next;
	item->next->prev = item->prev;

}

void list::swap_elem(ListItem &item, ListItem &elem)
{
//if next || prev == null  ???



}

list list::operator = (const list &other)
{

}
