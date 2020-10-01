#include "text.h"

ZZ::ZZ(int left, int right)
{
	int size_ = 0;
	left_ = left;
	right_ = right;
}

void ZZ::copy_ (const ZZ a)
{
	left_ = a.left();
	right_ = a.right();	
	mas_ = (int*)malloc(a.size_*sizeof(*mas_));
	for(int i = 0; i < a.size_;i++)
	{
		mas_[i] = a.mas_[i];
	}
	size_ = a.size_;
}

void ZZ::push_ (int a)
{
	if(a < left_ || a > right_)
	{
		//throw(-1, "a < left || a > right");
		cout << "1";
		return;
		
	}
	//int temp = a - left_;
	for(int i = 0; i < size_; i++)
	{
		if(a == mas_[i])
			return;
	}
	printf("2");
	int *mas;
	mas = new int[size_ + 1];
	for(int i = 0; i < size_; i++)
	{
		mas[i] == mas_[i];
	}
	mas[size_] = a;
	printf("%d", mas[size_]);
	size_++;
	if (size_ > 0)
		delete mas_;
	mas_ = mas;
}

void ZZ::clean_ (int a)
{
	if(a < left_ || a > right_)
	{
		//throw(-1, "a < left || a > right");
		return;
	}
	int yes = -1;
	for(int i = 0; i < size_; i++)
	{
		if(a == mas_[i] && !yes)
			yes = i;
	}
	if(yes == -1)
		return;
	int *mas, j = 0;
	mas = new int[size_ - 1];
	for(int i = 0; i < size_; i++)
	{
		if(i == yes)
		{
			continue;
		}
		else
		{
			mas[j] == mas_[i];
			j++;
		}
	}
	size_--;
	if (size_ > 0)
		delete[] mas_;
	mas_ = mas;
}

bool ZZ::isEmpty() const
{
	if(size_ == 0)
	{
		return 1;
	}
	return 0;
}

int ZZ::min_ () const
{
	if(size_ == 0)
	{
		return -1;
	}
	int m = mas_[0];
	for(int i = 0; i < size_; i++)
	{
		if(mas_[i] < m)
		{
			m = mas_[i];
		}
	}
	return m;
}

int ZZ::max_() const
{
	if(size_ == 0)
	{
		return -1;
	}
	int m = mas_[0];
	for(int i = 0; i < size_; i++)
	{
		if(mas_[i] > m)
		{
			m = mas_[i];
		}
	}
	return m;
}

ZZ::~ZZ()
{
	if(size_ != 0)
		delete[] mas_;
	size_ = 0;
	left_ = 0;
	right_ = 0;
}

void ZZ::print() const {
    if (size_ == 0) 
	{
		printf("no elements");
		cout << " " << 1 << " " << left_ << " " << right_ << endl;
		return;
    }
	cout << left_ << " " << right_ << endl;
	for(int i = 0; i < size_; i++) {
        printf("%d ", mas_[i]);
    }
    cout << endl;
	cout << size_ << endl;
}

/*UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}*/