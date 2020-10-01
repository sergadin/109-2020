#include <string>
#include "intset.h"

Queue::Queue(unsigned int size)
{
	if(size == 0)
	{
		throw QueueError(-1, std::string( "Нулевой размер очереди в конструкторе"));
	}
	elements_ = new int[size]; 
	size_ = size; 
	n_ = 0;
}

Queue::Queue(const Queue & right)
{
        elements_ = new int[size_ = right.size_];
        for(int k = 0; k < size_; k++)
		elements_[k] = right.elements_[k];
	n_ = right.n_;
}

Queue::~Queue()
{
	delete[] elements_;
}

void Queue::put(int item)
{
	if(is_full())
		throw QueueError(-2, std::string("НЕТ МЕСТА"));
	elements_[n_++] = item;
}

int Queue::get_first() 
{
	if(is_empty())
		throw QueueError(-4, std::string("get от пустой очереди."));
	int first_item = elements_[0];
	shift_left();
	return first_item;
}	

void Queue::clear()
{
	n_ = 0;
}

void Queue::shift_left()
{
	if(is_empty())
		return;
	for(int k = 1; k < n_; k++)
	{
		elements_[k-1] = elements_[k];
	}
	--n_;
}

Queue & Queue::operator=(const Queue & right)
{
	if(this == &right)
	{
		return *this;
	}
	delete[] elements_;
	elements_ = new int[size_ = right.size_];
	for(int k = 0; k < size_; k++)
		elements_[k] = right.elements_[k];
	n_ = right.n_;
	return *this;
}

Queue & operator+=(Queue &left, const Queue& right)
{
	return left;
}

std::ostream & operator<<(std::ostream &os, const Queue &q)
{
	os << "Queue of size " << q.size_ << " with " << q.n_ << " items:\n";
	for(int k = 0; k < q.n_; k++)
	{
		os << "\t" << q.elements_[k] << "\n";
	}
	return os;
}
