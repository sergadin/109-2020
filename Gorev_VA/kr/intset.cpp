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
	
	std::cout << size_ << " " << minval_ << " " << maxval_ << "\n";
	for (int i = 0; i < size_; i++)
	std::cout << ar_[i] << "\n";
}

void intset::put(int item)
{
	if ((item > maxval_) || (item < minval_))
		return;
	int *ar;
	ar = new int[size_ + 1];
	for (int i = 0; i < size_; i++)
		ar[i] = ar_[i];
	ar[size_] = item;
	if (size_ > 0)
		delete[] ar_;
	size_++;
	ar_ = ar;
} 

int main(void)
{
	intset IS(-2, 2);
	IS.put(1);
	intset IS1(IS);
	return 0;
}
