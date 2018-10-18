#include "Safe.h"


template Safe<5, 4>;




template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
inline void Safe<NUM_LOCKS, NUM_DIALS>::generateLockParallelized(const Vector<Dial, NUM_DIALS>& v, int numThreads)
{

	bool locked[NUM_LOCKS * 2] = {};

	for (int i = 0; i < numThreads; ++i) {
		std::thread t(&Safe<NUM_LOCKS, NUM_DIALS>::solveLocksParallelized, this, v, locked);
		t.detach();
	}

}




template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
void Safe<NUM_LOCKS, NUM_DIALS>::solveLocksParallelized(const Vector<Dial, NUM_DIALS>& v, bool * locked)
{ 
	for (int lock = 0; lock < NUM_LOCKS; ++lock) {
		for (int i = 0; i < 2; ++i) {
			if (!locked[lock * 2 + i]) {
				
				locked[lock * 2 + i] = true;

				//Avoid 50:50 if statement, requires CN to be exactly before LN in Lock.h 
				*(&locks[lock].CN + i) = v + (DIF*lock + *UHF * (1-i));
				

			}
		}
	}
}

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
inline void Safe<NUM_LOCKS, NUM_DIALS>::solveLocks(const Vector<Dial, NUM_DIALS> &v)
{
	for (int lock = 0; lock < NUM_LOCKS; ++lock) {
		for (int i = 0; i < 2; ++i) {
				//Avoid 50:50 if statement, requires CN to be exactly before LN in Lock.h 
				*(&locks[lock].CN + i) = v + ( DIF*lock + *UHF * (1-i));
		}
	}
}