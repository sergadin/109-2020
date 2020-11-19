#include "text.h"

ZZ::ZZ (int k, int n) //создает пустой
{
	if(k > n || n < 1 || k < 1)
	{
		throw UserException(0, std::string("k > n || n == 0"));
	}
	n_ = n;
	k_ = k; // c 1
	mas_ = new int[n];
	for(int i = 0; i < n;i++)
	{
		mas_[i] = 0;
	}
	//size_ = 1;
}

void ZZ::name ()
{
	mas_[k_ - 1]++;
}

void ZZ::message (ZZ &to)
{
	if(k_ == to.k_ || n_ != to.n_)
	{
		throw UserException(1, std::string("your messege is wrong"));
	}
	int good;
	for(int i = 0;i < n+;i++)
	{
		good = Max(mas_[i], to.mas_[i]);
		mas_[i] = good;
	}
	mas_[k - 1]++;
}

bool ZZ::operator <(const ZZ b) // a < b
{
	if(n_ != b.n_)
	{
		throw UserException(2, std::string("wrong size")); // ошибка
	}
	int count = 0;
	for(int i = 0;i < n; i++)
	{
		if(mas_[i] > b.mas_[i])
		{
			return false;
		}
		if(mas_[i] < b.mas_[i])
		{
			count++;
		}
	}
	if(count == 0)
	{
		return false;
	}
	return true;
}

void ZZ::print() const
{
	printf("(");
	for(int i = 0;i < n_;i++)
	{
		printf("%d ", mas_[i]);
	}
	printf(") ");
}
ZZ::~ZZ()
{
	n_ = 0;
	k_ = 0;
	delete[] mas_;
}

ZZ ZZ::operator=(const ZZ &C)
{
	if (mas_ == C.mas_)
		return *this;
	n_ = C.n_;
	k_ = C.k_;
	delete[] mas_;
	mas_ = new int[n_];
	for (int i = 0; i < n_; i++)
		mas_[i] = C.mas_[i];

	/*for (int i = 0; i < N_; i++)
		std::cout << mark_[i] << " ";
	std::cout << "\n";
	*/
	return *this;
}