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
	

	//Safe<5, 4> s;
	
	//s.generateLockParallelized({ 2,3,4,5 },3);

	Dial d;

	d + 6;

	int END;
	cin >> END;

	return 0;
}