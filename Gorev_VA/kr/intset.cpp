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

int main(void)
{
	return 0;
}
