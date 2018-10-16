#pragma once

#include "Lock.h"
#include <thread>


template <unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
class Safe
{
public:
	Lock<NUM_DIALS> locks[NUM_LOCKS];
	char *UHF, *LHF, *PHF;

	//Designed to be ran by threads. Solves all locks in parallel.
	void solveLockParallelized(char const *root, bool *locked);


	Safe(char *uhf, char *lhf, char *phf) : UHF(uhf), LHF(lhf), PHF(phf) {};
	~Safe() {};

	void generateLockParallelized(const char (&root)[NUM_DIALS], int numThreads);

};

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
inline void Safe<NUM_LOCKS, NUM_DIALS>::generateLockParallelized(const char(&root)[NUM_DIALS], int numThreads)
{

	bool locked[NUM_LOCKS * 2] = {};

	for (int i = 0; i < numThreads; ++i) {
		std::thread t(&Safe<NUM_LOCKS, NUM_DIALS>::solveLockParallelized, this, root, locked);
		t.detach();
	}

}


