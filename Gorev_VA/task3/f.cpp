#include <iostream>
#include <string.h>
using namespace std;

const int M = 4;

template <class T>
class slot
{
private:
	string key_;
	T val_;
public:
	slot(string key, T val)
	{
		key_ = key;
		val_ = val;
	}
	~slot()
	{
		cout << "произошел ~slot()\n";
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
			string key_;
			T val_;
		};
	};
	node ver_;
public:
};*/

int main(void)
{
	slot <int> B("str", 1);
	return 0;
}
