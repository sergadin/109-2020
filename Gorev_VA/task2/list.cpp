#include <iostream>
#include "list.h"

template <class T>

int list <T>::add_item(const T item) // add item to the end of the list
	// return 1 if item - first created element
	// return 0 if item - not first created element
{
	if (base_ == 0)
	{
		last_ = base_ = new node;
		base_->val_ = item;
		base_->next_ = 0;
		return 1;
	}

	node *new_element = new node;
	new_element->val_ = item;
	new_element->next_ = 0;
	last_->next_ = new_element;
	last_ = new_element;
	return 0;
}

int list <T>::del_item() // delete item from the beginning of the list
	// return 0 if list is empty
	// return 1 if list is not empty
{
	node *new_base;
	if (base_ == 0)
		return 0;
	new_base = base_->next_;
	if (last_ == base_)
		last_ = 0;
	delete base_;
	base_ = new_base;
	return 1;
}

int list <T>::deletelist() // return number of deleted elements
{
	int i = 0;
	node *N = base_;
	while (N != 0)
	{
		N = base_->next_;
		delete base_;
		base_ = N;
		i++;
	}
	return i;
}

bool list <T>::operator==(const list <T> &L) const
{
	node *N1, *N2;
	N1 = base_;
	N2 = L.base_;
	while ((N1 != 0) && (N2 != 0))
	{
		if (N1->val_ != N2->val_)
			return 0;
		N1 = N1->next_;
		N2 = N2->next_;
	}
	if (N1 != N2)
		return 0;
	return 1;
}

list <T> &list <T>::operator=(const list <T> &L)
{
	if (base_ != L.base_)
	{
		deletelist();
		node *N;
		last_ = base_ = 0;
		if (L.base_ != 0)
		{
			N = L.base_;
			add_item(L.base_->val_);
			N = N->next_;
			while (N != 0)
			{
				add_item(N->val_);
				N = N->next_;
			}
		}
	}
	return *this;
}