#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define MAXLEN 10
class Base
{
public:
	std::vector <std::string> name;
	std::vector <int> quant;
	int num;
	std::vector < std::vector <int> > hash_name;
	std::vector < std::vector <int> > map;
	std::vector < std::vector <int> > hash_map;
	int ind(std::string str) { return (str.length() % MAXLEN); }
	int ind(std::vector <int> m) { return (m.size() % MAXLEN); }
	
	Base()
	{
		num = 0;
		name.resize(0);
		quant.resize(0);
		map.resize(0);
		hash_name.resize(MAXLEN);
		hash_map.resize(MAXLEN);
		for (int i = 0; i < MAXLEN; i++)
		{
			hash_name[i].resize(0);
			hash_map[i].resize(0);
		}
	}
	int find_detail(std::string str)
	{
		int i = ind(str);
		for (int j = 0; j < hash_name[i].size(); j++)
			if (str == name[hash_name[i][j]])
				return hash_name[i][j];
		return -1;
	}
	int add_detail(std::string str, int q)
	{
		if (q < 0)
			return 0;
		if (find_detail(str) != -1)
			return -1;
		num++;
		name.push_back(str);
		hash_name[ind(str)].push_back(num - 1);
		quant.push_back(q);
		
		return 0;
	}
	int map_eq(std::vector <int> m1, std::vector <int> m2)
	{
		if ((m1.size() < 2) || (m2.size() < 2) || (m1.size() % 2) || (m2.size() % 2))
			return -1;
		if (m1.size() != m2.size())
			return 0;
		if (m1[0] != m2[0])
			return 0;
		std::vector <int> mm1 = m1, mm2 = m2;
		sort(mm1.begin(), mm1.end());
	}
	/*int find_map(std::vector <int> m)
	{
		if (m.size() < 2)
			return -1;
		int i = ind(m);
		for (int j = 0; j < hash_map[i].size(); j++)
			if ()
	}*/
};


int main()
{
	Base B;
	std::string S = "AAA";
	B.add_detail(S, 1);
	B.add_detail("BBBB", 2);
	B.add_detail("CCC", 3);
	std::cout << B.num << ", " << B.name[0] << ", " << B.hash_name[3][0] << "\n";
	std::cout << B.num << ", " << B.name[1] << ", " << B.hash_name[4][0] << "\n";
	std::cout << B.num << ", " << B.name[2] << ", " << B.hash_name[3][1] << "\n";
	
	return 0;
}
