#include "text.h"

ZZ::ZZ (int k, int n) //создает пустой
{
	n_ = n;
	k_ = k;
	mas_ = new int[n];
	for(int i = 0; i < n;)
	{
		mas_[i] = 0;
	}
	size_ = 1;
}

void ZZ::name (int temp)
{
	mas_[k_] = size_;
	size_++;
}

void ZZ::message (int from, int to)
{
	if(from.k_ > to.k_)
	{
		return;
	}
	for(int i = 0;i < from.k_;i++)
	{
		to.mas_[i] = from.mas_[i];
	}
}

bool ZZ::operator <(const ZZ b) // a < b
{
	if(n_ != b.n_)
	{
		return false; // ошибка
	}
	if(k_ == b.k_)
	{
		if(size_ < b.size_)
		{
			return true;
		}
		return false;
	}
	int temp = Min(k_, b.k_)
	for(int i = 0;i < temp; i++)
	{
		if(mas_[i] != b.mas_[i])
			return false; //ошибка
	}
	if(mas_[temp + 1] < b.mas_[temp + 1])
		return true;
	return false;
}

/*UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}*/