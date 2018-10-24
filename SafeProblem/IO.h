#pragma once
#include "Vector.h"
#include "Safe.h"
#include <fstream>
#include <exception>
#include <string>



struct IOException : public std::exception {
	const char * what() const throw () {
		return "Error reading from/writing to file.";
	}
};


class IO
{
private: 
	std::fstream fs;

public:

	

	IO(std::string filepath) : fs(filepath) {};
	~IO();

	void printNumSolutions(unsigned int x) throw (IOException);
	 
	//Prints all valid solutions for a set UHF,LHF, and PHF combo.
	//length of the array pointed to by roots should be of length <numRoots>
	void printKey(Vector<Dial, 4> *roots, Vector<Dial, 4> UHF, Vector<Dial, 4> LHF, Vector<Dial, 4> PHF, unsigned int numRoots) throw (IOException);

	
	//void printLockedSafe(const Safe<5, 4> &s) throw(IOException);
	
	void printLockedSafe(const Safe<5,4> &s) throw(IOException);

	void readLockedSafe(Safe<5, 4> *safe);

};



