#include <iostream>
#include <cstring>
#include<stdio.h>
#include "kr3.h"
using namespace std;
bonus::bonus(const std::string &name, int n)
{
	if (n<0 || n==0) 
	{
		throw bonusError(-1, std::string( "prog is dead"));
	}

	actions_ = new int[n]; /* массив на количество  действий в категории */
	money_ = new double[n]; /* массив на количество денег потраченных в категории */

	for(int i = 0; i < n; i++)
	{
		actions_[i] = 0;
	}

	for(int j = 0; j < n; j++)
	{
		money_[j] = 0;
	}
       	n_ = n;
}

//чистка памяти
bonus::~bonus()
{
	delete[] actions_;
	delete[] money_;

}

// счетчики 
void bonus::dollars(int category, double m)
{
	if (category > this -> n_){
		throw bonusError(-5, std::string ("category error"));
	}
	actions_[category] = actions_[category] + 1; //счестчик операций
	money_[category] =  money_[category] + m; // записываем итог по деньгам
	return;
}

// слияние покупок        
void samePerson(const bonus &fperson, const bonus &sperson)
{
	if (fperson.n_ == sperson.n_ && fperson.name_==sperson.name_){
		printf("same person\n\n");
		for (int  i = 0; i < fperson.n_; i++){
			fperson.money_[i] = fperson.money_[i] + sperson.money_[i]; // считаем деньги
			fperson.actions_[i] = fperson.actions_[i] + sperson.actions_[i];	// считаем операции 
            sperson.money_[i]=fperson.money_[i];
            sperson.actions_[i]=fperson.actions_[i];
		} 
}
        else 
        {
        printf("not the same person");
	}
}        

//узнаем кто побогаче 
bool operator == (const bonus &N, const bonus &M)
{
	double k1 = 0, k2 = 0; 
	if (N.n_ != M.n_)
	{
		printf("error in the number of categories\n\n");
        return -1;
	}

	for (int i=0; i < N.n_; i++){
		k1 = k1 + N.money_[i];
		k2 = k2 + M.money_[i];
	}
	
	if (k1 == k2)
	{
        printf("equal\n");
        return 0;
	}

	if (k1 > k2)
	{
        printf("first one more loyal \n");
        return 1;
	}
    
	if (k1 < k2)
	{
        printf("second one more loyal \n");
        return 1;
	}
}

// вывод каких-то штук
std::ostream & operator<<(std::ostream& os, const bonus& N)
{
	os << "number of categories " << N.n_ << " number of actions &  amount of money\n";
	for(int i = 0; i < N.n_; i ++)
	{
		os <<  N.actions_[i]  << "  " << N.money_[i]  << "\n";
	}

	return os;

}

