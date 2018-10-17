#include <iostream>
#include "Safe.h"
#include "Utility.h"
#include "Dial.h"
#include "Vector.h"
#include <random>

using namespace std;
using namespace util;

Vector<Dial,4> UHF, LHF, PHF, DIF;




inline void generateHash() {
	for (int i = 0; i < 4; ++i) {
		UHF[i] = (rand() % 19) - 9;
		LHF[i] = (rand() % 19) - 9;
		PHF[i] = (rand() % 19) - 9;
	}		

	DIF = UHF + LHF + PHF;

}

inline void generateRoot() {
	
	//Safe<5, 4> s(&UHF, &LHF, &PHF, DIF);

	Safe<5, 4> s[10000];


	Dial d[4];
	Vector<Dial, 4> root;

	for (int i = 0; i < 10000; ++i) {
		d[0] = i % 10;
		d[1] = i % 100 / 10;
		d[2] = (i % 1000 / 100);
		d[3] = (i / 1000);
		root = d;

		s[i] = Safe<5,4>(&UHF, &LHF, &PHF, DIF);

		s[i].solveLocks(root);

	}

	for (int i = 0; i < 10000; ++i) {
		
		cout << s[i][0].CN << " | " << s[i][0].LN << endl;
		cout << s[i][1].CN << " | " << s[i][1].LN << endl;
		cout << s[i][2].CN << " | " << s[i][2].LN << endl;
		cout << s[i][3].CN << " | " << s[i][3].LN << endl;
		cout << s[i][4].CN << " | " << s[i][4].LN << endl;
		cout << endl;

	}





}

int main(char **argv, int argc) {
	
	generateHash();

	cout << "HASH: " << UHF << " | " << LHF << " | " << PHF << " | " << DIF << endl;

	generateRoot();

	//Dial d[4] = { 1,1,1,1 };
	//UHF = LHF = PHF = d;

	//Safe<5,4> s(&UHF,&LHF,&PHF);

	//s.generateLockParallelized({ 0,0,0,0 }, 1);

	//for (int i = 0; i < 20000; ++i);

	//for (int i = 0; i < 5; ++i) {
	//	cout << s[i].CN << " " << s[i].LN << endl;
	//}
	
	cout << Dial(-6);


	int END;
	cin >> END;

	return 0;
}