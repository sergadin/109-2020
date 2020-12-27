#include <iostream>
#include <string.h>
//using namespace std;

const int M = 2;

template <class T>
class slot
{
public:
	std::string key_;
	T val_;
	
	slot()
	{
		//nothing
	}
	slot(std::string key, T val)
	{
		key_ = key;
		val_ = val;
	}
	~slot()
	{
		std::cout << "\"~slot()\" occured\n";
	}
	int sth()
	{
		return 0;
	}
};

template <class T>
class node
{
private:
	slot <T> *cur_;  // array of current slots
	int n_;          // number of current slots
	node <T> **next_node_;
	node <T> *prev_node_;
public:
	node()
	{
		cur_ = new slot<T>[2 * M + 1];
		next_node_ = 0;
		prev_node_ = 0;
		n_ = 0;
	}
	~node()
	{
		std::cout << "\"~node()\" occured\n";
		if (cur_ != 0)
			delete[] cur_;
		n_ = 0;
		prev_node_ = 0;
		if (next_node_ != 0)
			delete[] next_node_;
	}
	int add_slot(std::string key, T val)
	{
		if (n_ >= (2 * M))
			return 0;
		cur_[n_].key_ = key;
		cur_[n_].val_ = val;
		n_++;
		return 1;
	}
	void sth()
	{
		std::cout << cur_->key_ << " " << cur_->val_ << "\n"; 
	}
};

template <class T>
class B_tree
{
private:
	node <T> *root_;
public:
	B_tree()
	{
		root_ = new node<T>;
	}
	
};

int main(void)
{
	node <int> N;
	N.add_slot("stroka", 4);
	N.sth();
	return 0;
}
