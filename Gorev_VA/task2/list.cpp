

































/*#include <string>
#include <iostream>
#include "clock.h"

Clock nextClock(const Clock &C)
{
	Clock nextC(C);
	nextC.mark_[C.num_]++;

	return nextC;
}

Clock nextClock(const Clock &prevClock, const Clock &sendingClock)
{
	Clock C(prevClock);
	C.mark_[prevClock.num_]++;

	if (C.N_ != sendingClock.N_)
		throw ClockError(-1, std::string("Количество процессов в подаваемых часах разное\n"));
	for (int i = 0; i < C.N_; i++)
		if (C.mark_[i] < sendingClock.mark_[i])
			C.mark_[i] = sendingClock.mark_[i];

	return C;
}

Clock Clock::operator=(const Clock &C)
{
	if (mark_ == C.mark_)
		return *this;
	N_ = C.N_;
	num_ = C.num_;
	delete[] mark_;
	mark_ = new int[N_];
	for (int i = 0; i < N_; i++)
		mark_[i] = C.mark_[i];

	for (int i = 0; i < N_; i++)
		std::cout << mark_[i] << " ";
	std::cout << "\n";
	return *this;
}

bool operator<(const Clock &left, const Clock &right)
{
	if (left.N_ != right.N_)
		throw ClockError(-2, std::string("Количество процессов в подаваемых часах разное\n"));
	for (int i = 0; i < left.N_; i++)
		if (left.mark_[i] > right.mark_[i])
			return 0;
	return 1;
}*/