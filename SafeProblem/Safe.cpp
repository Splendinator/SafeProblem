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

				//Avoid 50:50 if statement, requires lock.h to be in the form: CN LN HN
				*(&locks[lock].CN + i) = v + (DIF*lock + *UHF * (1-i));
				

			}
		}
	}
}

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
inline void Safe<NUM_LOCKS, NUM_DIALS>::solveLocks(const Vector<Dial, NUM_DIALS> &v)
{
	//*UHF, *LHF, *PHF
	locks[0].CN = v           + *UHF;
	locks[0].LN = locks[0].CN + *LHF;
	locks[0].HN = locks[0].LN + *PHF;
	for (int i = 1; i < NUM_LOCKS; ++i) {
		locks[i].CN = v + locks[i-1].HN + *UHF;
		locks[i].LN = v + locks[i  ].CN + *LHF;
		locks[i].HN = v + locks[i  ].LN + *PHF;
	}
}



