#include "profile.h"

profile::profile(const char *programname, int N)
{	
	if(programname == 0 || N == 0){
		throw Exception(1, "invalid input for profile");
	}
	
	program = programname;
	categories = N;
	transactions = new int[N];
	transactions_sum = new double[N];
	for(int i=0; i<N; ++i)
	{
		transactions[i] = 0;
		transactions_sum[i] = 0;
	}
}

profile::~profile()
{
	categories = 0;
	program=0;
	delete[] transactions;
	delete[] transactions_sum;
}

const char* profile::get_program()
{
	return this->program;
}

int profile::get_categories() const
{
	return this->categories;
}

void profile::transaction(int category, double sum)
{
	this->transactions_sum[category-1]+=sum;
	this->transactions[category-1]+=1;
}

bool profile::compare(const profile& p) const
{
	double sum1, sum2;
	if ((this->program != p.program)||(this->categories != p.categories)){
		throw Exception(2, "uncomparable profiles");
	}
	
	for(int i=0; i<this->categories; ++i){
		sum1 += this->transactions_sum[i];
		sum2 += p.transactions_sum[i];
	}
	return (sum1>sum2);
	
}

double profile::get_sum(int category) const
{	
	if ((category<1)||(category>this->categories)){
		throw Exception(4, "incorrect category");
	}
	
	return this->transactions_sum[category-1];
}

int profile::get_quantity(int category) const
{
	if ((category<1)||(category>this->categories)){
		throw Exception(4, "incorrect category");
	}
	
	return this->transactions[category-1];
}

void profile::merge(profile& p)
{
	if ((this->program != p.program)||(this->categories != p.categories)){
		throw Exception(3, "unmergable profiles");
	}
	
	for(int i=0; i<this->categories; ++i){
		this->transactions[i] += p.transactions[i];
		this->transactions_sum[i] += p.transactions_sum[i];
	}
}


