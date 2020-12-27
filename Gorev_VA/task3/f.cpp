#include <iostream>
#include <string.h>
using namespace std;

const int M = 4;

template <class T>
class slot
{
public:
	string key_;
	T val_;
	
	slot()
	{
		
	}
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
/*class node
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
		friend node;
	};
	
	slot cur_;  // array of current slots
	slot next_; // array of next slots
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
		cout << "\"~node()\" occured\n";
		delete[] cur_;
		delete[] next_;
		n_ = 0;
	}
};*/
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
	slot <int> N();
	
	return 0;
}
