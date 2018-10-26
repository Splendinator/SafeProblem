#include "Safe.h"


template Safe<1, 4>;
template Safe<2, 4>;
template Safe<3, 4>;
template Safe<4, 4>;
template Safe<5, 4>;
template Safe<6, 4>;
template Safe<7, 4>;
template Safe<8, 4>;
template Safe<9, 4>;




template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
Safe<NUM_LOCKS, NUM_DIALS>::Safe()
{
	*(char *)&UHF = -1;
	*(char *)&LHF = -1;
	*(char *)&PHF = -1;
	*(char *)&ROOT = -1;
}

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
Safe<NUM_LOCKS, NUM_DIALS>::Safe(Vector<Dial, NUM_DIALS> uhf, Vector<Dial, NUM_DIALS> lhf, Vector<Dial, NUM_DIALS> phf) : UHF(uhf), LHF(lhf), PHF(phf)
{
	DIF = uhf + lhf + phf;
	*(char *)&ROOT = -1;		//Signal that root is uninitialised.
}

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
Safe<NUM_LOCKS, NUM_DIALS>::Safe(Vector<Dial, NUM_DIALS> uhf, Vector<Dial, NUM_DIALS> lhf, Vector<Dial, NUM_DIALS> phf, const Vector<Dial, NUM_DIALS>& dif) : UHF(uhf), LHF(lhf), PHF(phf), DIF(dif)
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
		locks[i].CN = locks[i-1].HN + UHF;
		locks[i].LN = locks[i  ].CN + LHF;
		locks[i].HN = locks[i  ].LN + PHF;
	}
}

template<unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
bool Safe<NUM_LOCKS, NUM_DIALS>::isInOrder()
{
	int left, right, total;
	for (int i = 0; i < NUM_LOCKS; ++i) {
		total = 0;
		for (int j = 0; j < NUM_DIALS; ++j)
			total += locks[i].CN[j].toChar();
		if (total%2) return false;
		if (i == 0) left = total;
		if (i == NUM_LOCKS - 1) right = total;
	}

	return left < right;
}


