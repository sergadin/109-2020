#include <iostream>
#include <fstream>
#include <sstream>

#include <strings.h>
#include "database.h"
#include "server.h"

int f(std::istream &in)
{
	int i = 1;
	std::string str;
	while (in >> str)
	{
		std::cout << i << ") " << str << "\n";
		i++;
	}
	std::cout << "It's done\n";
	return 0;
}

int main()
{
	std::ifstream in("database.txt");
	if (in.is_open())
		f(in);
	return 0;
}
