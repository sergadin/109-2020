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
		base_ = current_ = 0;
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
		node *N;
		N = current_;
		while (N->next_ != 0)
			N = N->next_;
		return N->val_;
	}
	bool is_empty() const
	{
		return (base_ == 0);
	}
	
	int del_item() // delete item from the end of the list
	// return 0 if list is empty
	// return 1 if list is not empty
	// if current_ - last element, current_ moves 1 step to first element 
	{
		node *N;
		if (base_ == 0)
			return 0;
			
		N = current_;
		while (N->next_ != 0)
			N = N->next_;
		// N become the last element
		if (N == base_)
		{
			delete base_;
			base_ = current_ = 0;
			return 1;
		}
		
		if (N == current_)
		{
			current_ = base_;
			while (current_->next_ != N)
				current_ = current_->next_;
			current_->next_ = 0;
		}
		delete N;
		return 1;
	}
	int add_item(const T item) // add item to the beginning of the list
	// return 1 if item - first created element
	// return 0 if item - not first created element
	{
		if (base_ == 0)
		{
			base_ = current_ = new node;
			current_->val_ = item;
			current_->next_ = 0;
			return 1;
		}
		
		node *new_element = new node;
		new_element->val_ = item;
		new_element->next_ = base_;
		base_ = new_element;
		return 0;
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
	list <int> M;
	M.add_item(1);
	M.add_item(2);
	M.add_item(3);
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
