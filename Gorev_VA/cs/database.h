#include <vector>
#include <string>
#include <iostream>

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
		if ((m1.size() < 2) || (m2.size() < 2) || !(m1.size() % 2) || !(m2.size() % 2))
			return -1;
		if (m1.size() != m2.size())
			return 0;
		if (m1[0] != m2[0])
			return 0;
		
		std::vector <int> mm1 = m1, mm2 = m2;
		int s = (m1.size() - 1) / 2;
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				if (mm1[1 + 2*i] == mm2[1 + 2*j])
					if (mm1[2 + 2*i] != mm2[2 + 2*j])
						return 0;
					else
					{
						mm1.erase(mm1.begin() + 1 + 2*i, mm1.begin() + 3 + 2*i);
						mm2.erase(mm2.begin() + 1 + 2*j, mm2.begin() + 3 + 2*j);
						s--;
						i--;
						break;
					}
				if (i == s - 1)
					return 0;
			}
		}
		if (s)
			return 0;
		return 1;
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
