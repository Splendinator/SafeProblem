#pragma once

#include "Lock.h"
#include <thread>


template <int NUM_LOCKS, int NUM_DIALS>
class Safe
{
public:
	Lock<NUM_DIALS> locks[NUM_LOCKS];
	char UHF[NUM_DIALS], LHF[NUM_DIALS], PHF[NUM_DIALS];

	//Designed to be ran by threads. Solves all locks in parallel.
	void solveLockParallelized(char const *root, int threadId);




	Safe() {};
	~Safe() {};

	void generateLockParallelized(const char (&root)[NUM_DIALS], int numThreads);

};


