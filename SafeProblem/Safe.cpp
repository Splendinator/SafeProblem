#include "Safe.h"


template Safe<5, 4>;




template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
void Safe<NUM_LOCKS, NUM_DIALS>::solveLockParallelized(char const *root, bool *locked)
{ 

	for (int lock = 0; lock < NUM_LOCKS; ++lock) {
		for (int i = 0; i < 2; ++i) {
			if (!locked[lock * 2 + i]) {
				
				locked[lock * 2 + i] = true;
				
				Dial *p = locks[lock].CN + (i * NUM_DIALS * sizeof(Dial));	

				for (int j = 0; j < NUM_DIALS; ++j)
					p[j] = root[j]
						+ UHF[j] * (lock + i)
						+ LHF[j] * lock
						+ PHF[j] * lock;
				
			}
		}
	}
}