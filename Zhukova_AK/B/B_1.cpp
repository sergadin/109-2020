
/*

template <class T>
list<T>::list()
{
	ListItem *current = new ListItem;
        current->next = NULL;
        current->prev = NULL;
        current->data = NULL;

	go_next();
}
*/

/*
template <class T>
list<T>::list(T item)
{
	ListItem *current = new ListItem;
        current->next = NULL;
        current->prev = NULL;
        current->data = item;

	go_next();
}

*/

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
        new_elem->data = element;
	new_elem->prev = NULL;
        new_elem->next = first;
	first = new_elem;
	get_first();
}

//удаление первого элемента
template <class T>
void list<T>::del_first_elem()
{
//        first->data = first->next;//пока думаю над этим
}

//удаление последнего элемента
template <class T>
void list<T>::del_last_elem()
{
//        ListItem *item;
//        item = last;
        last = last->prev;
}
//шаг вперёд
template <class T>
void list<T>::go_next()
{
        current = current->next;
}

//шаг назад
template <class T>
void list<T>::go_back()
{
        current = current->prev;
}

template <class T>
void list<T>::print() const
{
//        ListItem *elem;
//	get_first();
//проверка, что следующий элемент есть

//	if (current->data == NULL)
//	{
//		printf ("Список пуст\n");
//	}
//	else
//	{
//
//       		while (current->next != NULL)
//	        {
//        	        printf ("%d\n", current->data);
//                	go_next();
//        	}
//	}
}

template <class T>
void list<T>::get_first()
{
        ListItem *current = new ListItem;
        current->prev = NULL;
//        current->data = first;
        current->next = first->next;
}

template <class T>
void list<T>::add_after_elem(T element, ListItem * item)
{
//if next || prev == null  ???
        ListItem *new_item = new ListItem;

//        new_item->prev = *item->data;
//       new_item->data = element;
//        new_item->next = *item->next;

//        item->next = *element;
//        item->next->prev = *element; //надо проверить, что это работает
}


template <class T>
void list<T>::add_before_elem(T element, ListItem *item)
{
//if next || prev == null  ???
        ListItem *new_item = new ListItem;

//        new_item->prev = *item->prev;
//        new_item->data = element;
//        new_item->next = *item->data;

//        item->prev = *element;
//        item->prev->next = *element; //но это не точно, пусть пока так будет
}

template <class T>
void list<T>::del_elem(ListItem *item)
{
//if next || prev == null  ???

//        item->prev->next = *item->next;
//        item->next->prev = *item->prev;

}

template <class T>
void list<T>::swap_elem(ListItem *item, ListItem *elem)
{
//if next || prev == null  ???



}

template <class T>
list<T> list<T>::operator = (const list<T> &other)
{
	get_first();

//	while (this->next != NULL)
//        {
//                this->data = other.data;
//		go_next();
//        }
        return *this;


}

template <class T>
void list<T>::change_elem(ListItem *item, T elem)
{
	item->data = elem;
}

/*template <class T>
list<T>::~list()
{
	get_first();
	while (current->next != NULL)
        {
		current = NULL;
		go_next;
	}
}
*/


//удалить лишнее!!
