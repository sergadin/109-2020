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
		int n_;
		int k_;
		//string s;
		int *mas_;
		ZZ();
	public:
		ZZ (int k, int n); //создает пустой
		void name (int temp); //события это числа
		void message (ZZ to);
		bool operator <(const ZZ b);
		void print() const;
		~ZZ();
};


/*class UserException {
	private:
		int code_;
		string message_;
	public:
		UserException(int code, string message);
		string message() const;
		int code() const;
};
*/
/*UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}
*/

