#include <iostream>
#include "list.h"

template <class T>
class queue
{
private:
	list <T> L_;
public:
	queue() {   }
	queue(const queue <T> &Q)
	{
		L_ = Q.L_;
	}
	~queue()
	{
		L_.deletelist();
	}
	int add_item(const T item) // add item to the end of the queue
	// return 0 if queue is empty
	// return 1 if queue is not empty
	{
		return L_.add_item(item);
	}
	int del_item() // delete item from the beginning of the queue
	// return 0 if queue is empty
	// return 1 if queue is not empty
	{
		return L_.del_item();
	}
	bool operator==(const queue <T> &Q) const
	{
		return (L_ == Q.L_);
	}
	queue <T> &operator=(const queue <T> &Q)
	{
		L_ = Q.L_;
		return *this;
	}
	friend std::ostream &operator<<(std::ostream& os, const queue <T> &Q)
	{
		return (os << Q.L_);
	}
};