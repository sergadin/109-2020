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

bool intset::find_item(int item)
{
	for (int i = 0; i < size_; i++)
		if (ar_[i] == item)
			return 1;
	return 0;
}

void intset::put(int item)
{
	if (find_item(item))
		return
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

void intset::del(int item)
{
	if (size_ == 0)
		return;
	for (int i = 0, j = 0; i <= size_ ; i++)
	{
		if (i >= size_)
		{
			size_ = j;
			if (size_ == 0)
			{
				delete[] ar_;
			}
		}
		if (ar_[i] != item)
		{
			ar_[j] = ar_[i];
			j++;
		}
	}
}

int intset::find_max()
{
	int max = minval_;
	if (size_ == 0)
	{
		std::cout << "Set os emtpy\n";
		return maxval_ + 1;
	}
	for (int i = 0; i < size_; i++)
		if (ar_[i] > max)
			max = ar_[i];
	return max;
}

int intset::find_min()
{
	int min = maxval_;
	if (size_ == 0)
	{
		std::cout << "Set os emtpy\n";
		return minval_ - 1;
	}
	for (int i = 0; i < size_; i++)
		if (ar_[i] < min)
			min = ar_[i];
	return min;
}

