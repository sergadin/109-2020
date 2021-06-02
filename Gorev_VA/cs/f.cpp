#include <iostream>
#include <vector>
#include "database.h"
#include <sstream>

int f(char *buf, char *&mes)
{
	
	scanf(buf, "%s", mes);
	return 0;
}

int main()
{
	char buf[1024] = "Hellow world\n";
	char *cur = buf;
	char mes[1024];
	//mes = new char[1024];
	std::cout << buf;
	
	std::cout << mes << "\n";
	f(buf, mes);
	std::cout << mes << "\n";
	sscanf(buf, "%s", &mes);
	std::cout << mes << "\n";
	
	return 0;
}
