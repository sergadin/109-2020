#include "Lamport.h"
#include <iostream>
#include <math.h>

Lamport::Lamport(int N, int K) 
{
	if(N <= 0 || K < 0 || K > N-1)
		throw Exception(-1, std::string("wrong parameters"));

	clock_ = new int[N];
	N_ = N;
	K_ = K;
	for(int i = 0; i < N; i++)
		clock_[i] = 0;
}

Lamport::~Lamport()
{
	delete[] clock_;
}

bool Lamport::operator <(const Lamport &right)
{
	if(N_ != right.N_)
		throw Exception(-1, std::string("You try to compare clocks in different dimensions"));
	
	bool result = false;
	for(int i = 0; i < N_; i++)
	{
		if(clock_[i] > right.clock_[i])
		{
			result = false;
			break;
		}
		if(clock_[i] < right.clock_[i])
			result = true;
	}
	return result;
}

Lamport Lamport::operator =(const Lamport &right)
{
	if(N_ != right.N_)
		throw Exception(-1, std::string("You try to do something with clocks in diffent dimenstions"));	
	for(int i = 0; i < N_; i++)
		clock_[i] = right.clock_[i];
}

std::ostream& operator <<(std::ostream &os, const Lamport &a)
{
	for(int i = 0; i < a.N_; i++)
		os << a.clock_[i] << " ";
	os << std::endl;

	return os;
}

void Lamport::step ()
{
	clock_[K_]++;
}

void Lamport::send (Lamport &receiver)
{
	receiver.clock_[receiver.K_]++;
	for(int i = 0; i < N_; i++)
	{
		if(receiver.clock_[i] < clock_[i])
			receiver.clock_[i] = clock_[i];
	}
}
