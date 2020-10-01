#include <iostream>
#include "intset.h"

intset::intset(int maxval, int minval)
{
	size_ = 0;
	maxval_ = maxval;
	minval_ = minval;
	std::cout << maxval_ << ", " << minval_;
}

intset::intset(intset& IS)
{
	
}
intset::~intset()
{
	if (size != 0)
		delete[] ar_;
	size_ = 0;
	minval_ = 0;
	maxval_ = 0;
}
int main(void)
{
	intset IS(-1, 1);
	return 0;
}
