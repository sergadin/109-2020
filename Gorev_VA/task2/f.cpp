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
public:
	class iterator
	{
	private:
		node *current_;
	public:
		void go_next()
		{
			current_ = current_->next_;
		}
		T get_current_item()
		{
			return current_->val_;
		}
		bool is_last()
		{
			return (current_->next_ == 0);
		}
		bool is_valid()
		{
			return !(current_ == 0);
		}
		friend list;
	};
	iterator begin()
	{
		iterator I;
		I.current_ = base_;
	}
	
	list() // create empty list
	{
		last_ = base_ = 0;
	}
	list(const list <T> &L)
	{
		node *N;
		last_ = base_ = 0;
		if (L.base_ != 0)
		{
			N = L.base_;
			add_item(L.base_->val_);
			N = N->next_;
			while(N != 0)
			{
				add_item(N->val_);
				N = N->next_;
			}
		}
	}
	~list()
	{
		//deletelist();
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
	int del_item() // delete item from the beginning of the list
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
	
	int deletelist() // return number of deleted elements
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
	list <T> &operator=(const list <T> &L)
	{
		if (base_ != L.base_)
		{
			list <T> *new_list = new list <T>(L);
			deletelist();
			base_ = new_list->base_;
			last_ = new_list->last_;
		}
	}
};

int main(void)
{
	std::cout << "---Create \"list <int> L\"\n";
	list <int> L;
	std::cout << "---Add items 1, 2, 3 in L\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	std::cout << "---Create \"list <int> M(L)\"\n";
	list <int> M(L);
	
	std::cout << "---Check operator ==: \"M == L\":\n";
	if (M == L)
		std::cout << "M = L\n\n";
	else
		std::cout << "M != L\n\n";
	
	std::cout << "---Find elements:\n";
	std::cout << "L:\n";
	std::cout << "first element: " << L.get_first_item() << "\n";
	std::cout << "last element: " << L.get_last_item() << "\n";
	
	std::cout << "\n";
	std::cout << "---Delete first element in L\n";
	L.del_item();
	std::cout << "---Find elements:\n";
	std::cout << "L:\n";
	std::cout << "first element: " << L.get_first_item() << "\n";
	std::cout << "last element: " << L.get_last_item() << "\n";
	
	std::cout << "\n";
	std::cout << "---Check operator ==: \"M == L\":\n";
	if (M == L)
		std::cout << "M = L\n";
	else
		std::cout << "M != L\n";
	std::cout << "---Check operator ==: \"L == L\":\n";
	if (L == L)
		std::cout << "L = L\n";
	else
		std::cout << "L != L\n";
		
	std::cout << "\n";
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "---Delete M\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";
	
	std::cout << "\n";
	std::cout << "---Add items 1, 2, 3 in L\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	
	
	std::cout << "\n";
	std::cout << "---Add items 1, 2, 3 in L\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	std::cout << "---Check operator =: \"M = L\"\n";
	M = L;
	std::cout << "---Find elements:\n";
	std::cout << "M:\n";
	std::cout << "first element: " << M.get_first_item() << "\n";
	std::cout << "last element: " << M.get_last_item() << "\n";
	//std::cout << "---Check operator =: \"L = L\"; \" M = M\"\n";
	//L = L;
	//M = M;
	
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "---Delete M\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";
	std::cout << "---Delete M\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	
	std::cout << "\n";
	std::cout << "---Add items 1, 2, 3 in L\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	
	list <int>::iterator i = L.begin();
	std::cout << "---Check class iterator: \"while i isnot last write current item\"\n";
	while(!i.is_last())
	{
		std::cout << i.get_current_item() << "\n";
		i.go_next();
	}
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";
	return 0;
}
