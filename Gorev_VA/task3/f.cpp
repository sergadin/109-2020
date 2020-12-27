#include <iostream>
#include <string.h>
using namespace std;

const int M = 4;

template <class T>
class node
{
private:
	class slot
	{
	public:
		string key_;
		T val_;
		
		slot(string key, T val)
		{
			key_ = key;
			val_ = val;
		}
		~slot()
		{
			cout << "\"~slot()\" occured\n";
		}
	};
	
	slot *cur_;  // array of current slots
	slot *next_; // array of next slots
	int n_;    // number of current slots
public:
	node()
	{
		cur_ = new slot[M];
		next_ = new slot[M + 1];
		n_ = 0;
	}
	~node()
	{
		cout << "\"~slot()\" occured\n";
		delete[] cur_;
		delete[] next_;
		n_ = 0;
	}
	int add_slot(string str, T val)
	{
		if (n_ <= M)
			return 0;
		cur_[n_].key_ = str;
		cur_[n_].val_ = val;
		n_++;
		return 1;
	}
	int get_sth()
	{
		if (n_)
			return cur_[0].val_;
		return 0;
	}
};
/*class Btree
{
private:
	class node
	{
	private:
		class slot
{
public:
	string key_;
	T val_;
	
	slot(string key, T val)
	{
		key_ = key;
		val_ = val;
	}
	~slot()
	{
		cout << "\"~slot()\" occured\n";
	}
};
	};
	node ver_;
public:
};*/

int main(void)
{
	node <int> N();
	N.add_slot("str", 4);
	cout << N.get_sth();
	return 0;
}
