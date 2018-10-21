#pragma once

#include "Lock.h"
#include <thread>


template <unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
class Safe
{
private:
	//Designed to be ran by threads. Solves all locks in parallel.
	void solveLocksParallelized(const Vector<Dial, NUM_DIALS> &v, bool *locked);

public:
	Lock<NUM_DIALS> locks[NUM_LOCKS];
	Vector<Dial,NUM_DIALS> *UHF, *LHF, *PHF, DIF;


	Safe() { UHF = LHF = PHF = nullptr; };

	Safe(Vector<Dial, NUM_DIALS> *uhf, Vector<Dial, NUM_DIALS> *lhf, Vector<Dial, NUM_DIALS> *phf) : UHF(uhf), LHF(lhf), PHF(phf) { DIF = *uhf + *lhf + *phf; };
	Safe(Vector<Dial, NUM_DIALS> *uhf, Vector<Dial, NUM_DIALS> *lhf, Vector<Dial, NUM_DIALS> *phf, const Vector<Dial, NUM_DIALS> &dif) : UHF(uhf), LHF(lhf), PHF(phf), DIF(dif) {};
	~Safe() {};

	void generateLockParallelized(const Vector<Dial, NUM_DIALS> &v, int numThreads);

	//Solves all locks.
	void solveLocks(const Vector<Dial, NUM_DIALS> &v);

	Lock<NUM_DIALS> &operator[](const int x) { return locks[x]; }

	friend std::ostream &operator<<(std::ostream &o, const Safe &s);

};


