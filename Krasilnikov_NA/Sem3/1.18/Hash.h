#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "List.h"

using namespace std;

int key(string key);

template <typename T>
class Hash
{
public:
	class pair
	{
	public:
		string key;
		T value;
		pair(string k, T val)
		{
			key = k;
			value = val;
		}
	};

	~Hash()
	{
		for (int j = 0; j < 8192; j++)
		{
			auto i = table[j].begin();
			i++;
			while (i != table[j].begin())
			{
				delete i.cur->data;
				i++;
			}
		}
	}

	List<pair*> table[8192];

	void fill(string filename)
	{
		ifstream in(filename);
		while (!in.eof())
		{
			T t;
			string k, h;
			in >> k >> h >> t;
			/*if ((string(typeid(T).name())).find("class") == string::npos)
			{
				string cmd = temp.erase(0, number);
				if (cmd.find(" ") == string::npos) t = stod(cmd);
				else while (cmd.find(" ") != string::npos)
				{
					if ((string(typeid(T).name())).find("int") != string::npos)
					{
						T new_m = new int [n];
						for (int i = 0; i < n - 1; i++) new_m[i] = t[i];
						new_m[n - 1] = stod(cmd.substr(0, cmd.find(" ")));
						cmd.erase(0, cmd.find(" "));
					}
				}
				t = stod(temp.erase(0, number));
			}
			else t = temp.erase(0, number);*/
			pair* te = new pair(k, t);
			table[key(k)].push_back(te);
		}
	}


	T get(string k)
	{
		ListItem<pair*>* temp = table[key(k)].begin().cur;
		for (int i = 0; i < table[key(k)].lenght(); i++)
		{
			temp = temp->next;
			if (temp->data->key == k) return temp->data->value;
		}
		throw Exc(1, "Incorrect key");
	}

	void insert(string k, T v)
	{
		pair* te = new pair(k, v);
		table[key(k)].push_back(te);
	}
};

