#include "Safe.h"


template Safe<5, 4>;

template<int NUM_LOCKS, int NUM_DIALS>
void Safe<NUM_LOCKS, NUM_DIALS>::generateLockParallelized(const char(&root)[NUM_DIALS], int numThreads)
{	
	for (int i = 0; i < numThreads; ++i) {
		std::thread t(&Safe<NUM_LOCKS, NUM_DIALS>::solveLockParallelized, this, root, i);
		t.detach();
	}
}


#include <iostream>
template<int NUM_LOCKS, int NUM_DIALS>
void Safe<NUM_LOCKS, NUM_DIALS>::solveLockParallelized(char const *root, int threadId)
{
	static bool locked[NUM_LOCKS * 2] = {};

	for (int lock = 0; lock < NUM_LOCKS; ++lock) {
		for (int i = 0; i < 2; ++i) {
			if (!locked[lock * 2 + i]) {
				locked[lock * 2 + i] = true;
				
				locks[lock].CN;

				for (int j = 0; j < NUM_DIALS; ++j) {
	
				}
			}
		}
	}
}