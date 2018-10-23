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
private: std::fstream fs;

public:


	IO(std::string filepath) : fs(filepath) {};
	~IO();

	//Prints all valid solutions for a set UHF,LHF, and PHF combo.
	//length of the array pointed to by roots should be of length <numRoots>
	void printSolutions(Vector<Dial, 4> *roots, Vector<Dial, 4> UHF, Vector<Dial, 4> LHF, Vector<Dial, 4> PHF, unsigned int numRoots) throw (IOException);
	
};



