#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "taylor.h"

int main(int argc, char** argv)
{
	int index;
	double epsilon = 1E-3;
	for (index = 0; index < 24; ++index)
	{
		test(epsilon, "cos", taylorCos, cos);
		epsilon /= 10;
	}
	return 0;
}
