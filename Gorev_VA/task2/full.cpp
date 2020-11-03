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
	node *last_;
	node *current_;
public:
	list() // create empty list
	{
		last_ = base_ = current_ = 0;
	}
	list(const list <T> &L)
	{
		node *N;
		last_ = base_ = current_ = 0;
		if (L.base_ != 0)
		{
			N = L.base_;
			add_item(L.base_->val_);
			N = N->next_;
			while(N != 0)
			{
				add_item(N->val_);
				if (N == L.current_)
				current_ = last_;
				N = N->next_;
			}
		}
		
	}
	T get_current_item() const
	{
		return current_->val_;
	}
	T get_first_item() const
	{
		return base_->val_;
	}
	T get_last_item() const
	{
		return last_->val_;
	}
	bool is_empty() const
	{
		return (base_ == 0);
	}
	
	int add_item(const T item) // add item to the end of the list
	// return 1 if item - first created element
	// return 0 if item - not first created element
	{
		if (base_ == 0)
		{
			last_ = base_ = current_ = new node;
			current_->val_ = item;
			current_->next_ = 0;
			return 1;
		}
		
		node *new_element = new node;
		new_element->val_ = item;
		new_element->next_ = 0;
		last_->next_ = new_element;
		last_ = new_element;
		return 0;
	}
	int del_item() // delete item from the beginning of the list
	// return 0 if list is empty
	// if current_ != base_, return 1
	// if current_ == base_, current_ moves 1 step to first element and return 2 
	{
		node *new_base;
		if (base_ == 0)
			return 0;
		new_base = base_->next_;
		if (last_ == base_)
			last_ = 0;
		if (current_ == base_)
		{
			current_ = new_base;
			delete base_;
			base_ = new_base;
			return 2;
		}
		delete base_;
		base_ = new_base;
		return 1;
	}
	
	int deletelist() // return number of deleted elements
	{
		int N = 0;
		if (base_ == 0)
			return 0;
		current_ = base_->next_;
		delete base_;
		base_ = current_;
		return 1 + deletelist();
	}
	
	bool operator==(const list <T> &L) const
	{
		node *N1, *N2;
		N1 = base_;
		N2 = L.base_;
		while((N1 != 0) && (N2 != 0))
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
};

int main(void)
{
	list <int> L;
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	list <int> M(L);
	if (M == L)
		std::cout << "M = L\n";
	else
		std::cout << "M != L\n";
	
	std::cout << "L:\n";
	std::cout << "current element: " << L.get_current_item() << "\n";
	std::cout << "last element: " << L.get_last_item() << "\n";
	std::cout << "first element: " << L.get_first_item() << "\n";
	
	L.del_item();
	std::cout << "\n";
	
	std::cout << "L:\n";
	std::cout << "current element: " << L.get_current_item() << "\n";
	std::cout << "last element: " << L.get_last_item() << "\n";
	std::cout << "first element: " << L.get_first_item() << "\n";
	
	std::cout << "\n";
	if (M == L)
		std::cout << "M = L\n";
	else
		std::cout << "M != L\n";
	
	std::cout << "number of deleted elements: " << L.deletelist() << "\n";
	std::cout << "number of deleted elements: " << L.deletelist() << "\n";
	std::cout << "number of deleted elements: " << M.deletelist() << "\n";
	return 0;
}
