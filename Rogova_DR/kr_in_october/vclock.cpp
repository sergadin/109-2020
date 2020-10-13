#include <string>
#include "vclock.h"
#include <iostream>

Vclock::Vclock(int N, int k)
{
	if((k > N - 1) || (k < 0))
	{
		throw MatrError(-1, std::string("Fuuuu..."));
	}
	elements_ = new int[N];
	for(int i = 0; i < N; i++)
	{
		elements_[i] = 0;
	}
	N_ = N;
	k_ = k;
}


Vclock::~Vclock() 
{
	delete[] elements_;
}


void Vclock::local_ev()
{
	elements_[k_] += 1;
		
}

void Vclock::global_ev(const Vclock& M)
{
	if(M.N_ != N_)
        {
                throw MatrError(-1, std::string("Fuuuu1..."));
		return;
        }
	if(k_ == M.k_)
	{
		for(int i = 0; i < N_; i++)
		{
			if(elements_[i] != M.elements_[i])
			{
				throw MatrError(-1, std::string("Fuuu2...."));
			}
		}
		return;
	}
	for(int i = 0; i < N_; i ++)
	{
		if(i != k_)
		{
			if(M.elements_[i] > elements_[i])
			{
				elements_[i] = M.elements_[i];		
			}	
		}
		else
		{
			elements_[i] += 1;
		}
	}
	std::cout << "global event" << this <<std::endl;
	


}

bool operator <= (const Vclock& lev, const Vclock& prav)
{
	if(&lev == &prav)
        {
                return true;
        }
	if(lev.N_ != prav.N_)
	{
		throw MatrError(-1, std::string("Fuuu3...."));
		return false;
	}
	for(int i = 0; i < lev.N_; i ++)
	{
		if(lev.elements_[i] > prav.elements_[i])
		{
			return false;
		}
	}
	return true;
}
Vclock & Vclock::operator=(const Vclock & prav)
{
        if(this == &prav)
        {
                return *this;
        }
        delete[] elements_;
        elements_ = new int[prav.N_];
	N_ = prav.N_;
        k_ = prav.k_;
        for(int i = 0; i < N_; i++)
	{
                elements_[i] = prav.elements_[i];
	}
        return *this;
}

std::ostream & operator<<(std::ostream &os, const Vclock &q)
{
	os << "Vclock of size" << q.N_  << "number of event:\n" << q.k_;
	for(int i = 0; i < q.N_; i ++)
	{
		os << "\t" << q.elements_[i] << "\n";
	}
	return os;

}


