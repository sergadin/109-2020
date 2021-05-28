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
	int find_detail(std::string str)
	{
		int i = ind(str);
		for (int j = 0; j < hash[i].size(); j++)
			if (str == name[hash[i][j]])
				return hash[i][j];
		return -1;
	}
	int add_detail(std::string str)
	{
		if (find_detail(str) != -1)
			return -1;
		num++;
		name.push_back(str);
		hash[ind(str)].push_back(num - 1);
		return 0;
	}
	
};
