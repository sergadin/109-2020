#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
using namespace std;



class UserException {
	private:
		int code_;
		string message_;
	public:
		UserException(int code, string message);
		string message() const;
		int code() const;
};