#include "Safe.h"


template Safe<5, 4>;


template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
inline void Safe<NUM_LOCKS, NUM_DIALS>::generateLockParallelized(const char(&root)[NUM_DIALS], int numThreads)
{

	bool locked[NUM_LOCKS * 2] = {};

	for (int i = 0; i < numThreads; ++i) {
		std::thread t(&Safe<NUM_LOCKS, NUM_DIALS>::solveLockParallelized, this, root, locked);
		t.detach();
	}

}

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
void Safe<NUM_LOCKS, NUM_DIALS>::solveLockParallelized(char const *root, bool *locked)
{ 

	for (int lock = 0; lock < NUM_LOCKS; ++lock) {
		for (int i = 0; i < 2; ++i) {
			if (!locked[lock * 2 + i]) {
				
				locked[lock * 2 + i] = true;

				//Avoid 50:50 if statement, requires CN to be exactly before LN.
				*(&locks[lock].CN + i) = DIF*lock + *UHF * i;
				

			}
		}
	}
}