#include <string>
#include <iostream>

class Base
{
public:
	std::string *name_;
	int num_;
	int len(std::string str) { return str.length() % 10; }
	Base()
	{
		name_ = 0;
		num_ = 0;
	}
};

