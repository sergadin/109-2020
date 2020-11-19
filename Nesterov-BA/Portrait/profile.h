#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
using namespace std;

class profile
{
	private:
		int categories;
		const char *program;
		int *transactions;
		double *transactions_sum;
	public:
		profile(const char *programname, int categoriesnum);
		~profile();
		const char* get_program();
		int get_categories() const;
		void transaction(int category, double sum);
		bool compare(const profile &p) const;
		double get_sum(int category) const;
		int get_quantity(int category) const;
		void merge(profile &p);	
};

class Exception {
	private:
		int code_;
		std::string message_;
	public:
		Exception(int code, std::string message) : code_(code), message_(message) {}
		std::string message() const {return message_;}
		int code() const {return code_;}
};
