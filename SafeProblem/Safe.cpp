#include "Safe.h"


template Safe<5, 4>;




template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
Safe<NUM_LOCKS, NUM_DIALS>::Safe(Vector<Dial, NUM_DIALS> uhf, Vector<Dial, NUM_DIALS> lhf, Vector<Dial, NUM_DIALS> phf)
{
	DIF = uhf + lhf + phf;
	*(char *)&ROOT = -1;		//Signal that root is uninitialised.
}

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
Safe<NUM_LOCKS, NUM_DIALS>::Safe(Vector<Dial, NUM_DIALS> uhf, Vector<Dial, NUM_DIALS> lhf, Vector<Dial, NUM_DIALS> phf, const Vector<Dial, NUM_DIALS>& dif)
{
	*(char *)&ROOT = -1;
}

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
inline void Safe<NUM_LOCKS, NUM_DIALS>::generateLockParallelized(const Vector<Dial, NUM_DIALS>& v, int numThreads)
{

	ROOT = v;

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
				*(&locks[lock].CN + i) = v + (DIF*lock + UHF * (1-i));
				

			}
		}
	}
}

//template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
//Vector<Dial, NUM_DIALS> Safe<NUM_LOCKS, NUM_DIALS>::readDials(std::istream & is)
//{
//	char c[NUM_DIALS];
//	int x;
//
//	for (int i = 0; i < NUM_DIALS; ++i) {
//		while (!((is >> c[i], c[i]) >= 48 && c[i] <= 57) && !c[i] == '+' && !c[i] == '-') {
//			if (c[i] == '+' || c[i] == '-') {
//				is >> x;
//				c[i] = x;
//			}
//			else {
//				c[i] -= 48;
//			}
//		}
//		std::cout << c[i];
//
//	}
//
//	
//	
//	return Vector<Dial, NUM_DIALS>();
//}

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
inline void Safe<NUM_LOCKS, NUM_DIALS>::solveLocks(const Vector<Dial, NUM_DIALS> &v)
{
	ROOT = v;
	locks[0].CN = v           + UHF;
	locks[0].LN = locks[0].CN + LHF;
	locks[0].HN = locks[0].LN + PHF;
	for (int i = 1; i < NUM_LOCKS; ++i) {
		locks[i].CN = v + locks[i-1].HN + UHF;
		locks[i].LN = v + locks[i  ].CN + LHF;
		locks[i].HN = v + locks[i  ].LN + PHF;
	}
}


