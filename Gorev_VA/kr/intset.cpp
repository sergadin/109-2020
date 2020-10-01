#include <iostream>
#include "intset.h"

intset::intset(int minval, int maxval)
{
	size_ = 0;
	maxval_ = maxval;
	minval_ = minval;
	std::cout << minval_ << ", " << maxval_ << "\n";
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
	if (IS.size_ <= 0)
		return;
	minval_ = IS.minval_;
	maxval_ = IS.maxval_;
	ar_ = new int[IS.size_];
	size_ = IS.size_;
	for (int i = 0; i < IS.size_; i++)
		ar_[i] = IS.ar_[i];
	
	std::cout << size << " " << minval << " " << maxval << "\n";
	for (int i = 0; i < size; i++)
	std::cout << ar_[i] << "\n";
}

int main(void)
{
	intset IS(-1, 1);
	return 0;
}
