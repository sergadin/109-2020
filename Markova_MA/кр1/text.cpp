#include "text.h"

ZZ::new_(int left, int right)
{
	int size = abs(-left + right + 1), size_ = 0;
	int mas_ = (int*)malloc(size*sizeof(*mas));
	for(int i = 0;i < size;i++)
	{
		mas[i] = 0;
	}
}

void ZZ::copy_ (const ZZ a)
{
	int size = abs(-a.left() + a.right() + 1);
	ZZ c(a.left(), a.right());
	for(int i = 0; i < size;i++)
	{
		c.mas_[i] = a.mas_[i];
	}
	c.size_ = a.size_;
}

void ZZ::push_ (int a)
{
	/*if(a < left_ || a > right_)
	{
		throw(-1, "a < left || a > right");
	}*/
	int temp = a - left_;
	if(mas_[temp] == 1)
		return;
	mas_[a - left_] = 1;
	size_++;
}

void ZZ::clean_ (int a);
{
	if(a < left_ || a > right_)
	{
		throw(-1, "a < left || a > right");
	}
	if(mas_[a - left_] != 1)
		return;
	mas_[a - left_] = 0;
	size_--;
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
		return;
	}
	int min;
	for(int i = 0; i < abs(-left_ + right_ + 1);i++)
	{
		if(mas_[i] == 1)
		{
			min = left_ + i;
			return min;
		}
	}
}

int ZZ::max_() const
{
	
	if(size_ == 0)
	{
		return -1;
	}
	int min;
	for(int i = abs(-left_ + right + 1) - 1; i >= 0;i--)
	{
		if(mas_[i] == 1)
		{
			min = left_ + i;
			return min;
		}
	}
}

ZZ::~ZZ()
{
	if(size_ != 0)
		delete[] mas_;
	size_ = 0;
	left_ = 0;
	right = 0;
}

void ZZ::print() const {
    if (size_ == 0) 
	{
		cout << "no elements";
		cout << " " << left_ << " " << right_ << endl;
		return;
    }
	cout << left_ << " " << right_ << endl;
	for(int i = 0; i < abs(right_ - left_ + 1); i++) {
		if(mas_[i] == 1)
        printf("%d ", left_ + i);
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