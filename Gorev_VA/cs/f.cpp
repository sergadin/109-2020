#include <iostream>
#include <fstream>
#include <sstream>

#include <strings.h>
#include "database.h"

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

int ff(std::ofstream &out)
{
	out << 1234;
}

int main()
{
	std::ifstream in("database.txt");
	if (in.is_open())
		f(in);
		
	std::cout << "\n\n\n\n\n";
	
	std::ofstream out("file.txt");
	
	if (out.is_open())
		ff(out);
	
	std::cout << "\n\n\n\n\n";
	
	char buf[1024] = "Hellow world!";
	int len = strlen(buf) + 1;
	char* p = (char*)&len;
	std::cout << *p;
	
	return 0;
}
