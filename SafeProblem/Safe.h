#pragma once

#include "Lock.h"
#include <thread>


template <unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
class Safe
{
private:
	//Designed to be ran by threads. Solves all locks in parallel.
	void solveLockParallelized(char const *root, bool *locked);

public:
	Lock<NUM_DIALS> locks[NUM_LOCKS];
	Vector<Dial,NUM_DIALS> *UHF, *LHF, *PHF, DIF;


	Safe(Vector<Dial, NUM_DIALS> *uhf, Vector<Dial, NUM_DIALS> *lhf, Vector<Dial, NUM_DIALS> *phf) : UHF(uhf), LHF(lhf), PHF(phf) { DIF = *uhf + *lhf + *phf; };
	~Safe() {};

	void generateLockParallelized(const char (&root)[NUM_DIALS], int numThreads);

	Lock<NUM_DIALS> &operator[](const int x) { return locks[x]; }

};




