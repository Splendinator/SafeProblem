#include <iostream>
#include "Safe.h"
#include "Utility.h"


using namespace std;
using namespace util;

int main(char **argv, int argc) {

	cout << sizeof(Dial) << endl;
	cout << sizeof(Lock<4>) << endl;
	cout << sizeof(Safe<5,4>) << endl;

	

	int END;
	cin >> END;

	return 0;
}