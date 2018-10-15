#include <iostream>
#include "Safe.h"
#include "Utility.h"
#include "Dial.h"


struct sTR {
	int x = 2, y = 4, z = 6;

};

using namespace std;
using namespace util;

int main(char **argv, int argc) {

	//cout << sizeof(Dial) << endl;
	//cout << sizeof(Lock<4>) << endl;
	//cout << sizeof(Safe<5,4>) << endl;
	

	Safe<5, 4> s;
	
	s.UHF[0] = 1;
	s.LHF[0] = 1;
	s.PHF[0] = 1;

	s.generateLockParallelized({ 0,0,0,0 }, 3);

	for (int i = 0; i < 10000; ++i);

	for (int i = 0; i < 5; ++i) {
		cout << s.locks[i].CN[0] << " " << s.locks[i].LN[0] << endl;
	}

	int END;
	cin >> END;

	return 0;
}