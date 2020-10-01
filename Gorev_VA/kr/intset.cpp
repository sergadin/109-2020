#include <iostream>
#include "intset.h"

intset::intset(int maxval, int minval)
{
	size_ = 0;
	maxval_ = maxval;
	minval_ = minval;
	std::cout << maxval_ << ", " << minval_ << "\n";
}

intset::~intset()
{
	if (size_ != 0)
		delete[] ar_;
	size_ = 0;
	minval_ = 0;
	maxval_ = 0;
}

intset::intset(intset& IS)
{
	
}

int main(void)
{
	return 0;
}
