#include <iostream>
#include <string.h>
//using namespace std;

const int M = 4;

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
	slot <T> *next_; // array of next slots
	int n_;    // number of current slots
public:
	node()
	{
		cur_ = new slot<T>[M];
		next_ = new slot<T>[M + 1];
		n_ = 0;
	}
	~node()
	{
		std::cout << "\"~node()\" occured\n";
		delete[] cur_;
		delete[] next_;
		n_ = 0;
	}
	int sth()
	{
		return 0;
	}
	
};

int main(void)
{
	node <int> N;
	N.sth();
	return 0;
}
