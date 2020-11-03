#include <iostream>

template <class T>

class list
{
private:
	class node
	{
	public:
		T val_;
		node *next_;
	};
	node *base_; // "Empty" first element
	node *current_;
public:
	list() // create empty list
	{
		base_ = 0;
		current_ = 0;
	}
	T get_current_item()
	{
		return current_->val_;
	}
	void add_item(const T item) // add item to the beginning of list
	{
		if (base_ == 0)
		{
			base_ = current_ = new node;
			current_->val_ = item;
			current_->next_ = 0;
		}
		else
		{
			node *new_element = new node;
			new_element->val_ = item;
			new_element->next_ = base_->next_;
			base_->next_ = new_element;
		}
	}
};