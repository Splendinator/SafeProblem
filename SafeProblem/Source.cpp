#include <iostream>
#include "Safe.h"
#include "Utility.h"
#include "Dial.h"
#include "Vector.h"
#include <random>

using namespace std;
using namespace util;

Vector<Dial,4> UHF, LHF, PHF;



inline void generateHash() {
	for (int i = 0; i < 4; ++i) {
		UHF[i] = (rand() % 19) - 9;
		LHF[i] = (rand() % 19) - 9;
		PHF[i] = (rand() % 19) - 9;
	}		
}

inline void generateRoot() {
	//Get initial CN = ROOT + UHF
	//Get difference (DIF) every iteration (UHF + LHF + PHF)
	//Just ignore initial CN. Use difference to figure out duplicate numbers 
	
	//i.e DIF = (1,0,0,0)
	//DIF[1] = (2,0,0,0)
	//DIF[2] = (3,0,0,0)
	//etc..
	//root  

}

int main(char **argv, int argc) {
	generateHash();



	

	int END;
	cin >> END;

	return 0;
}