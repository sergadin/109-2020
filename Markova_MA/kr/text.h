#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
using namespace std;
#define Max(a, b) ((a)>(b) ? (a) : (b))
#define Min(a, b) ((a)<(b) ? (a) : (b))
class UserException
{
	private:
		int code_;
		std::string error_;
	public:
		UserException (int code, std::string reason)
		{
			code_ = code;
			error_ = reason;
		}

		const std::string error() const
		{
			return error_;
		}
};

/*
string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}
*/

class ZZ
{
	private:
		int n_;
		int k_;
		//string s;
		int *mas_;
		ZZ();
	public:
		ZZ (int k, int n); //создает пустой
		void name (); //
		void message (ZZ &to);
		bool operator <(const ZZ b);
		void print() const;
		ZZ operator=(const ZZ &C);
		~ZZ();
};




