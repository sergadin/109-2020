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

	int add_item(const T item);
	int del_item();

	int deletelist();

	bool operator==(const list <T> &L) const;
	list <T> &operator=(const list <T> &L);
};