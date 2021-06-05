#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>

#define MAXLEN 10

// карта сборки
struct Map
{
	// что собираем
	int res = -2;

	// из чего собираем
	struct Comp
	{
		int num;
		int quant;
	};
	std::vector < Map::Comp > comp;

	int size() { return comp.size(); }
	void resize(int n) { comp.resize(n); }
};


// база склада
class Base
{
public:
	std::vector < std::string > name;
	std::vector <int> quant;
	int num;
	std::vector < std::vector <int> > hash_name;
	std::vector < struct Map > map;
	std::vector < std::vector <int> > hash_map;
	int ind(std::string str) { return (str.length() % MAXLEN); }
	int ind(struct Map m) { return (m.size() % MAXLEN); }

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

	// Конвертация карты в виде вектора строк в карту в виде структуры
	struct Map convert_map(std::vector <std::string> M)
	{
		struct Map m;
		if ((M.size() < 2) || !(M.size() % 2)) { return m; }
		m.resize((M.size() - 1) / 2);
		m.res = find_detail(M[0]);
		for (int i = 0; i < m.size(); i++)
		{
			m.comp[i].num = find_detail(M[2 * i + 1]);
			for (int d = 1, j = M[2 * i + 2].length() - 1; j >= 0; d *= 10, j--)
				m.comp[i].quant += d * (M[2 * i + 2][j] - '0');
		}
		return m;
	}


	int find_detail(std::string str) //  найти номер детали в базе по названию
	{
		int i = ind(str);
		for (int j = 0; j < hash_name[i].size(); j++)
			if (str == name[hash_name[i][j]])
				return hash_name[i][j];
		return -1;
	}
	int add_detail(std::string str, int q = 0) // добавить в базу q деталей str
	{
		if (q < 0) return 0;
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
	int del_detail(std::string str, int q = 0) // удалить из базы q деталей str
	{
		if (q < 0) return 0;
		int I = find_detail(str);
		if (I == -1) return -1;
		if (quant[I] < q)
			return -1;
		quant[I] -= q;
		return q;
	}

	int map_eq(struct Map m1, struct Map m2) // проверка карт на равенство
	{
		// если данные не соответствуют базе возвращаем -1
		if ((m1.size() == 0) || (m2.size() == 0) || (m1.res < 0) || (m2.res < 0) || (m1.res >= num) || (m2.res >= num))
			return -1;
		// если есть отличие в каких-то деталях возвращаем 0
		if ((m1.size() != m2.size()) || (m1.res != m2.res))
			return 0;

		// если это одна и та же карта возвращаем 1
		struct Map mm1 = m1, mm2 = m2;
		int s = m1.size();
		for (int i = 0; i < s; i++)
		{
			for (int j = 0; j < s; j++)
			{
				if (mm1.comp[i].num == mm2.comp[j].num)
					if (mm1.comp[i].quant != mm2.comp[j].quant)
						return 0;
					else
					{
						mm1.comp.erase(mm1.comp.begin() + i, mm1.comp.begin() + i + 1);
						mm2.comp.erase(mm2.comp.begin() + j, mm2.comp.begin() + j + 1);
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
	int find_map(struct Map m) // найти номер карты в базе
	{
		if ((m.size() < 1) || (m.res < 0) || (m.res >= num)) return -2;
		int i = ind(m);
		for (int j = 0; j < hash_map[i].size(); j++)
			if (map_eq(m, map[hash_map[i][j]]))
				return hash_map[i][j];
		return -1;
	}
	int add_map(struct Map m) // добавить карту в базу
	{
		int f = find_map(m);
		if (f != -1) return f;
		map.push_back(m);
		hash_map[ind(m)].push_back(map.size() - 1);
		return map.size() - 1;
	}
	int find_map(std::vector <std::string> M) // найти номер карты в базе
	{
		struct Map m;
		m = convert_map(M);
		if (m.res < 0) return m.res;

		for (int i = 0; i < m.size(); i++)
			if (m.comp[i].num < 0) return m.comp[i].num;
		return find_map(m);
	}
	int add_map(std::vector <std::string> M) // добавить карту в базу
	{
		if ((M.size() < 3) || !(M.size() % 2)) return -2;
		add_detail(M[0]);
		for (int i = 1; i <= (M.size() - 1) / 2; i++)
			add_detail(M[2 * i - 1]);
		int f = find_map(M);
		if (f != -1) return f;

		struct Map m;
		m = convert_map(M);
		map.push_back(m);
		hash_map[ind(m)].push_back(map.size() - 1);
		return map.size() - 1;
	}


	int show_details(int ms) // показать список деталей
	{
		std::cout << "    List of details:\n";
		for (int I = 0; I < num; I++)
			std::cout << "    " << I + 1 << ") Name: " << name[I] << ", quant: " << quant[I] << "\n";

		char mes[1024];
		char key[1024];
		bzero(mes, sizeof(mes));
		sprintf(mes, "%d", num);
		write(ms, mes, sizeof(mes));

		for (int I = 0; I < num; I++)
		{
			bzero(mes, sizeof(mes));
			for (int i = 0; i < name[I].length(); i++)
				mes[i] = name[I][i];
			write(ms, mes, sizeof(mes));

			bzero(mes, sizeof(mes));
			sprintf(mes, "%d", quant[I]);
			write(ms, mes, sizeof(mes));
		}
		return 0;
	}
	int show_maps(int ms) // показать список карт
	{
		std::cout << "    List of maps:\n";
		for (int I = 0; I < map.size(); I++)
		{
			std::cout << "    " << I + 1 << ") Name: " << name[map[I].res] << ":\n";
			for (int i = 1; i <= map[I].size(); i++)
				std::cout << "      " << i << ". Name: " << name[map[I].comp[i - 1].num] << ", quant: " << map[I].comp[i - 1].quant << "\n";
		}

		char mes[1024];
		char key[1024];
		bzero(mes, sizeof(mes));
		sprintf(mes, "%d", (int)map.size());
		write(ms, mes, sizeof(mes));

		for (int I = 0; I < map.size(); I++)
		{
			bzero(mes, sizeof(mes));
			for (int i = 0; i < name[map[I].res].length(); i++)
				mes[i] = name[map[I].res][i];
			write(ms, mes, sizeof(mes));

			bzero(mes, sizeof(mes));
			sprintf(mes, "%d", map[I].size());
			write(ms, mes, sizeof(mes));

			for (int i = 1; i <= map[I].size(); i++)
			{
				bzero(mes, sizeof(mes));
				for (int j = 0; j < name[map[I].comp[i - 1].num].length(); j++)
					mes[j] = name[map[I].comp[i - 1].num][j];
				write(ms, mes, sizeof(mes));

				bzero(mes, sizeof(mes));
				sprintf(mes, "%d", map[I].comp[i - 1].quant);
				write(ms, mes, sizeof(mes));
			}
		}
		return 0;
	}
	int show_base(int ms) // показать списки деталей и карт
	{
		char mes[1024];
		bzero(mes, sizeof(mes));
		strcpy(mes, "show_details");
		write(ms, mes, sizeof(mes));
		show_details(ms);

		bzero(mes, sizeof(mes));
		strcpy(mes, "show_maps");
		write(ms, mes, sizeof(mes));
		show_maps(ms);
		return 0;
	}


	int can_build_map(int nn) // можно ли построить деталь по карте номер nn (nn = 1, 2, ...)
	{
		int n = nn - 1;
		if ((n >= map.size()) || (n < 0)) return -1;

		int kol = 0;
		for (int i = 0; i < num; i++)
			if (kol < quant[i]) kol = quant[i];

		for (int i = 0; i < map[n].size(); i++)
			if (quant[map[n].comp[i].num] < map[n].comp[i].quant) return 0;
			else
				if (kol > (quant[map[n].comp[i].num] / map[n].comp[i].quant))
					kol = quant[map[n].comp[i].num] / map[n].comp[i].quant;
		return kol;
	}
	int can_build_map(struct Map m) // можно ли построить деталь по карте  m
	{
		int n = find_map(m);
		return can_build_map(n + 1);
	}
	int can_build_map(std::vector <std::string> M) // можно ли построить деталь по карте M
	{
		int n = find_map(M);
		return can_build_map(n + 1);
	}


	int build_map(int nn, int kol) // построить kol деталей по карте номер nn (nn = 1, 2, ...)
	{
		int c = can_build_map(nn);
		int n = nn - 1;
		if (c <= 0) return c;
		if ((kol > c) || (kol < 0)) return -3;
		quant[map[n].res] += kol;
		for (int i = 0; i < map[n].size(); i++)
			quant[map[n].comp[i].num] -= kol * map[n].comp[i].quant;
		return kol;
	}

	int do_from(std::istream& in, int ms);

	int write_in_file(std::ostream& out)
	{
		out << "add_details\n";
		for (int i = 0; i < num; i++)
		{
			out << name[i] << " " << quant[i] << "\n";
		}
		out << "\n";
		
		for (int i = 0; i < map.size(); i++)
		{
			out << "add_map " << map[i].res;
			for (int j = 0; j < map[i].size(); j++)
				out << name[map[i].comp[j].num] << " " << map[i].comp[j].quant << " ";
			out << "\n";
		}
		return 0;
	}
};



// прочитать следующее слово
int scan_next(char*& cur, char mes[])
{
	for (int i = 0; i < strlen(mes); i++)
		mes[i] = 0;
	while (cur[0] == ' ') cur = cur + 1;
	if (cur[0] == 0) return -1;
	sscanf(cur, "%s", mes);
	cur = cur + strlen(mes);
	while (cur[0] == ' ') cur = cur + 1;

	return 0;
}

int scan_next(char*& cur, int& num)
{
	while (cur[0] == ' ') cur = cur + 1;
	if (cur[0] == 0) return -1;
	sscanf(cur, "%d", &num);
	while ((cur[0] != ' ') && (cur[0] != 0)) cur = cur + 1;
	while (cur[0] == ' ') cur = cur + 1;

	return 0;
}