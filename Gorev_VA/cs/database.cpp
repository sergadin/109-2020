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
		int I = find_detail(str);
		if (I != -1)
		{
			quant[I] += q;
			return q;
		}
		num++;
		name.push_back(str);
		hash_name[ind(str)].push_back(num - 1);
		quant.push_back(q);
		
		return q;
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
	int show_details()
	{
		std::cout << "    List of details:\n";
		for (int I = 0; I < num; I++)
			std::cout << "    " << I + 1 << ") Name: " << name[I] << ", quant: " << quant[I] << "\n";
		return 0;
	}
	int show_maps()
	{
		std::cout << "    List of maps:\n";
		for (int I = 0; I < map.size(); I++)
		{
			std::cout << "    " << I + 1 << ") Name: " << name[map[I][0]] << ":\n";
			for (int i = 1; i < map[I].size(); i++)
				std::cout << "      " << i << ". Name:" << name[map[I][i]] << ", quant: " << quant[map[I][i]] << "\n";
		}
			
		return 0;
	}
	int show_base()
	{
		show_details();
		show_maps();
		return 0;
	}
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
	
	std::vector <int> m, mm;
	m.resize(5);
	mm.resize(5);
	m[0] = 5, m[1] = 4, m[2] = 3, m[3] = 2, m[4] = 1;
	mm[0] = 5, mm[1] = 2, mm[2] = 1, mm[3] = 4, mm[4] = 3;
	std::cout << B.map_eq(m, mm) << "\n";
	m[0] = 5, m[1] = 4, m[2] = 3, m[3] = 2, m[4] = 1;
	mm[0] = 5, mm[1] = 2, mm[2] = 1, mm[3] = 4, mm[4] = 4;
	std::cout << B.map_eq(m, mm) << "\n";
	m[0] = 5, m[1] = 4, m[2] = 3, m[3] = 2, m[4] = 1;
	mm[0] = 5, mm[1] = 1, mm[2] = 1, mm[3] = 4, mm[4] = 3;
	std::cout << B.map_eq(m, mm) << "\n";
	//std::cout << m[0] << m[1] << m[2] << m[3] << m[4] << "\n";
	B.show_base();
	return 0;
}
