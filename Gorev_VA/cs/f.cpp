#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

int main()
{
	char *str ="ABC DEF";
	
	char mes[20];
	sscanf(str+4, "%s", &mes);
	std::cout << mes << strlen(mes);
	
	return 0;
}
