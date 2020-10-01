#include <iostream>
#include "intset.h"

intset::intset(int maxval, int minval)
{
	intset;
	size_ = 0;
	maxval_ = maxval;
	minval_ = minval;
	std::cout << maxval_ << ", " << minval_ << endl;
}

intset::intset(intset& IS)
{
	return *this;
}
