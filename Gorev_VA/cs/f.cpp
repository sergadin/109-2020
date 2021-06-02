#include <iostream>
#include <vector>
#include "database.h"
#include <sstream>

int f(char buf[], char mes[])
{
	sscanf(buf, "%s", mes);
	return 0;
}

int main()
{
	char buf[1024] = "Hellow world\n";
	char *cur = buf;
	char mes[1024];
	
	f(buf, mes);
	std::cout << mes;
	
	
	
	return 0;
}
