#pragma once

#include "Lock.h"
#include <string>
#include <thread>
#include <iostream>
#include "IO.h"

template <unsigned int NUM_LOCKS, unsigned int NUM_DIALS>
class Safe
{
private:
	//Designed to be ran by threads. Solves all locks in parallel.
	void solveLocksParallelized(const Vector<Dial, NUM_DIALS> &v, bool *locked);

public:
	Lock<NUM_DIALS> locks[NUM_LOCKS];
	Vector<Dial,NUM_DIALS> UHF, LHF, PHF, DIF;
	Vector<Dial,NUM_DIALS> ROOT;


	Safe() {};

	Safe(Vector<Dial, NUM_DIALS> uhf, Vector<Dial, NUM_DIALS> lhf, Vector<Dial, NUM_DIALS> phf);
	Safe(Vector<Dial, NUM_DIALS> uhf, Vector<Dial, NUM_DIALS> lhf, Vector<Dial, NUM_DIALS> phf, const Vector<Dial, NUM_DIALS> &dif);
	~Safe() {};

	void generateLockParallelized(const Vector<Dial, NUM_DIALS> &v, int numThreads);

	//Solves all locks.
	void solveLocks(const Vector<Dial, NUM_DIALS> &root);

	Lock<NUM_DIALS> &operator[](const int x) { return locks[x]; }






	friend std::ostream &operator<<(std::ostream &os, Safe<NUM_LOCKS, NUM_DIALS> s) {
		return os;
	}


	friend std::istream &operator>>(std::istream &is, Safe<NUM_LOCKS, NUM_DIALS> &safe) {
		std::string s;
		char type[3] = {};	//"CN" , "HN" or "LN"
		int number; // 0, 1, 2, 3, or 4.
		char dialc[NUM_DIALS + 1] = {}; //0000 - 9999;
		Dial diald[NUM_DIALS];

		//Skip over "NOT VALID" text
		is >> s;
		if (s == "NOT") { is >> s; }
		

		//read in all parts one at a time.
		for (int i = 0; i < NUM_LOCKS * 3; ++i) {
			
			//Read in type (CN0 - HN4)
			while ((is >> type[0], type[0]) == ','); //Ignore all commas, we are using whitespace seperation.
			is >> type[1];
			is >> number;

			//Read in Dial (0000 - 9999)
			while ((is >> dialc[0], dialc[0]) == ',');
			for (int j = 1; j < NUM_DIALS; is >> dialc[j++]);
			for (int j = 0; j < NUM_DIALS; ++j) {
				dialc[j] -= 48;			//Convert to int from ASCII
				diald[j] = dialc[j];	//Convert to dial from int
			}

			if		(type == "CN")	safe.locks[number].CN = diald;
			else if (type == "LN")	safe.locks[number].LN = diald;
			else					safe.locks[number].HN = diald;

		}
		return is;
	
	}


};