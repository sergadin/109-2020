#include <string>
#include <iostream>
#include "clock.h"

Clock::Clock(int N, int num)
{
	N_ = N;
	num_ = num;
	mark_ = new int[N];
	for (int i = 0; i < N; i++)
		mark_[i] = 0;
}

Clock nextClock(const Clock &C)
{
	Clock nextC(C.N_, C.num_);
	newC.mark_ = new int[C.N_];
	for (int i = 0; i < C.N_; i++)
		newC.mark_[i] = C.mark_[i];
	newC.mark_[C.num_]++;
	for (int i = 0; i < C.N_; i++)
		std::cout << C.mark_[i] << " " << newC.mark_[i] << "\n";
	
	return newC;
	
}

















/*intset::intset(int minval, int maxval)
{
	size_ = 0;
	maxval_ = maxval;
	minval_ = minval;
	//std::cout << minval_ << ", " << maxval_ << "\n";
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
		throw intsetError(-1, std::string("Нулевой размер присваиваемой строки"));
	minval_ = IS.minval_;
	maxval_ = IS.maxval_;
	ar_ = new int[IS.size_];
	size_ = IS.size_;
	for (int i = 0; i < IS.size_; i++)
		ar_[i] = IS.ar_[i];
}

intset::intset(const intset& IS)
{
	if (IS.size_ <= 0)
		throw intsetError(-2, std::string("Нулевой размер присваиваемой строки"));
	minval_ = IS.minval_;
	maxval_ = IS.maxval_;
	ar_ = new int[IS.size_];
	size_ = IS.size_;
	for (int i = 0; i < IS.size_; i++)
		ar_[i] = IS.ar_[i];
}

bool intset::find_item(int item) const
{
	for (int i = 0; i < size_; i++)
		if (ar_[i] == item)
			return 1;
	return 0;
}

void intset::put(int item)
{
	if (find_item(item))
		return;
	if ((item > maxval_) || (item < minval_))
		throw intsetError(-3, std::string("Требуемое значение вне исходного диапазона"));
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

int intset::find_max() const
{
	int max = minval_;
	if (size_ == 0)
	{
		throw intsetError(-4, std::string("Множество пусто: в нем нет максимума"));
	}
	for (int i = 0; i < size_; i++)
		if (ar_[i] > max)
			max = ar_[i];
	return max;
}

int intset::find_min() const
{
	int min = maxval_;
	if (size_ == 0)
	{
		throw intsetError(-5, std::string("Множество пусто: в нем нет минимума"));
	}
	for (int i = 0; i < size_; i++)
		if (ar_[i] < min)
			min = ar_[i];
	return min;
}

intset& operator*= (intset &left, const intset &right)
{
	for (int i = 0, j = 0; i <= left.size_; i++)
	{
		if (i >= left.size_)
		{
			left.size_ = j;
			if (left.size_ == 0)
			{
				delete[] left.ar_;
			}
			break;
		}
		if (right.find_item(left.ar_[i]))
		{
			left.ar_[j] = left.ar_[i];
			j++;
		}
	}
	return left;
}

intset operator* (const intset &left, const intset &right)
{
	intset IS(left.minval_, left.maxval_);

	if (left.minval_ <= right.minval_)
		IS.minval_ = left.minval_;
	else
		IS.minval_ = right.minval_;
	if (left.maxval_ >= right.maxval_)
		IS.maxval_ = left.maxval_;
	else
		IS.maxval_ = right.maxval_;

	if (left.size_ <= 0)
		return IS;
	IS.ar_ = new int[left.size_];

	for (int i = 0, j = 0; i <= left.size_; i++)
	{
		if (i >= left.size_)
		{
			IS.size_ = j;
			if (IS.size_ == 0)
			{
				delete[] IS.ar_;
			}
			break;
		}
		if (right.find_item(left.ar_[i]))
		{
			IS.ar_[j] = left.ar_[i];
			j++;
		}
	}
	return  IS;
}

bool operator== (const intset &left, const intset &right)
{
	for (int i = 0; i < left.size_; i++)
		if (!right.find_item(left.ar_[i]))
			return 0;
	for (int j = 0; j < right.size_; j++)
		if (!left.find_item(right.ar_[j]))
			return 0;
	return 1;
}

*/