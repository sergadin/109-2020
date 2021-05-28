#include <vector>
#include <string>
#include <iostream>

class Base
{
public:
	std::vector <std::string> name;
	int num;
	std::vector < std::vector <int> > hash;
	int len(std::string str) { return str.length() % 10; }
	Base()
	{
		name.resize(0);
		num = 0;
		hash.resize(0);
	}
	int add_detail(std::string str)
	{
		return 0;
	}
};

int main()
{
	Base B;
	return 0;
}
