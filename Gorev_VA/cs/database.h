#include <vector>
#include <string>
#include <iostream>

#define MAXLEN 10
class Base
{
public:
	std::vector <std::string> name;
	int num;
	std::vector < std::vector <int> > hash;
	int ind(std::string str) { return (str.length() % MAXLEN); }
	Base()
	{
		name.resize(0);
		num = 0;
		hash.resize(MAXLEN);
		for (int i = 0; i < MAXLEN; i++)
			hash[i].resize(0);
	}
	int add_detail(std::string str)
	{
		num++;
		name.push_back(str);
		hash[ind(str)].push_back(num - 1);
		return 0;
	}
};
