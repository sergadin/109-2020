#include <iostream>

class listError
{
private:
	int code_;
	std::string reason_;
public:
	listError(int code, std::string reason)
	{
		code_ = code;
		reason_ = reason;
	}

	const std::string get_reason() const
	{
		return reason_;
	}
	const int get_code() const
	{
		return code_;
	}
};

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
			if (current_ == 0)
				throw listError(-1, std::string("in void go_next(): Attempt to call empty node *current in class iterator"));
			current_ = current_->next_;
		}
		T get_current_item()
		{
			if (current_ == 0)
				throw listError(-2, std::string("in T get_current_item(): Attempt to call empty node *current in class iterator"));
			return current_->val_;
		}
		bool is_last()
		{
			if (current_ == 0)
				throw listError(-3, std::string("in bool is_last(): Attempt to call empty node *current in class iterator"));
			return (current_->next_ == 0);
		}
		bool is_valid()
		{
			return !(current_ == 0);
		}
		friend iterator list <T>::begin() const;
	};
	iterator begin() const
	{
		iterator I;
		I.current_ = base_;
		return I;
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
			while (N != 0)
			{
				add_item(N->val_);
				N = N->next_;
			}
		}
	}
	~list()
	{
		deletelist();
	}

	T get_first_item() const
	{
		if (base_ == 0)
			throw listError(-4, std::string("in T get_first_item(): Attempt to call empty node *base_ in class list"));
		return base_->val_;
	}
	T get_last_item() const
	{
		if (last_ == 0)
			throw listError(-5, std::string("in T get_last_item(): Attempt to call empty node *last_ in class list"));
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
		last_ = 0;
		return i;
	}

	bool operator==(const list <T> &L) const
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
	list <T> &operator=(const list <T> &L)
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
	list <T> &operator+(const list <T> &L) // add list L in the end of this list
	{
		list <T> L1(L);
		last_->next_ = L1.base_;
		last_ = L1.last_;
		L1.base_ = 0;
		L1.last_ = 0;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream& os, const list <T> &L)
	{
		iterator I = L.begin();
		while (I.is_valid())
		{
			os << I.get_current_item();
			if (!I.is_last())
				os << " ";
			I.go_next();
		}
		return os;
	}
};