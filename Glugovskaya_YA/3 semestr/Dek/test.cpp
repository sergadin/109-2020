#include <iostream>
#include <stdio.h>
#include <cstring>

#include "Dek.h"

//using namespace std;
int main(){
	printf("Hello\n");
	Dek <int> dek;
	dek.push_head(5);
	dek.push_head(10);
	dek.print();
	return 0;
}	