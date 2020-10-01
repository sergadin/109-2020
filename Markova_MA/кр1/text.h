#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
using namespace std;
#define Max(a, b) ((a)>(b) ? (a) : (b))
#define Min(a, b) ((a)<(b) ? (a) : (b))
class ZZ
{
	private:
		int left_;
		int right_;
		int mas_;
		int size_;
		ZZ();
	public:
		ZZ new_(int left, int right); //создает пустой
		//ZZ operator =(const ZZ &other);
		//ZZ operator *(const ZZ &other);
		//ZZ operator *=(const ZZ &other);
		//bool operator ==(const ZZ &other);
		void copy_ (const ZZ a);
		void push_ (int a);
		void clean_ (int a);
		
		int size() {
			return size_;
		}
		
		bool isEmpty() const;
		int min_ () const;
		int max_() const;
		
		int left() {return left_;}
		int right() {return right_;}
		
		void print() const;
		~ZZ();
};
/*
bool ZZ:operator ==(const ZZ &a, const ZZ &b)
{
	if(a.size_ != b.size_ || a.left_ ! = b.left_ || a.right_ != b.right_)
	{
		return false;
	}
	for(int i = 0;i < abs(-a.left_ + a.right_+1); i++)
	{
		if(a.mas_[i] != b.mas_[i])
			return false;
	}
	return true;
}

ZZ ZZ:operator *(const ZZ &a, const ZZ &b)
{
	int left1 = Max(a.left_, b.left_), right1 = Min(a.right_, b.right_);
	ZZ c(left1, right1);
	for(int i = left1 - a.left_; i < right1; i++)
	{
		if(a.mas[i] == 0 || a.mas[i] == 1)
		{
			c.mas[i] = a.mas[i];
			c.size_+= a.mas[i];
		}
	}
	return c;
}
ZZ ZZ:operator *=(const ZZ &b)
{
	left_ = Max(a.left_, b.left_), right1 = Min(a.right_, b.right_);
	free mas_;
	int size = abs(-left_ + right_ + 1), size_ = 0;
	int mas_ = (int*)malloc(size*sizeof(*array));
	if (!array) {
        throw UserException(1, "Memory Allocation Error");
    }
	for(int i = 0; i < size; i++)
	{
		mas_[i] = b.mas[i + left_ - left_b];
	}
	
}

ZZ ZZ:operator =(const ZZ &other)
{
	return 
}
*/

class UserException {
	private:
		int code_;
		string message_;
	public:
		UserException(int code, string message);
		string message() const;
		int code() const;
};

/*UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}
*/

