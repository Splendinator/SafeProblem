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
		UHF[i] = 0;//(rand() % 19) - 9;
		LHF[i] = (rand() % 19) - 9;
		PHF[i] = (rand() % 19) - 9;
	}		

	DIF = UHF + LHF + PHF;

}

inline void generateRoot() {
	
	

	Safe<5, 4> s[10000];
	Dial d[4];
	Vector<Dial, 4> root;  


	for (int i = 0; i < 10000; ++i) {
		d[3] = i % 10;
		d[2] = i % 100 / 10;
		d[1] = (i % 1000 / 100);
		d[0] = (i / 1000);
		root = d;

		s[i] = Safe<5,4>(&UHF, &LHF, &PHF, DIF);

		s[i].solveLocks(root);

	}

	for (int i = 0; i < 10000; ++i) {

		d[3] = i % 10;
		d[2] = i % 100 / 10;
		d[1] = (i % 1000 / 100);
		d[0] = (i / 1000);

		for (int j = 0; j < 5; ++j) {
			if (Vector<Dial, 4>::hasDupes(s[i][j].CN))
				goto next;
		}
		

		cout << d[0] << d[1] << d[2] << d[3] << " | ";
		cout << s[i][0].CN[0] << s[i][0].CN[1] << s[i][0].CN[2] << s[i][0].CN[3] << " ";
		cout << s[i][1].CN[0] << s[i][1].CN[1] << s[i][1].CN[2] << s[i][1].CN[3] << " ";
		cout << s[i][2].CN[0] << s[i][2].CN[1] << s[i][2].CN[2] << s[i][2].CN[3] << " ";
		cout << s[i][3].CN[0] << s[i][3].CN[1] << s[i][3].CN[2] << s[i][3].CN[3] << " ";
		cout << s[i][4].CN[0] << s[i][4].CN[1] << s[i][4].CN[2] << s[i][4].CN[3] << endl;
		
		next:
		continue;
	}

}

inline void generateRoot2() {



}

int main(char **argv, int argc) {
	srand(141);
	generateHash();

	cout << "HASH: " << UHF << " | " << LHF << " | " << PHF << " | " << DIF << endl;
	
	generateRoot();

	//cout << Vector<Dial, 4>::hasDupes(Vector<Dial, 4>({ 2,3,0,7 }));


	int END;
	cin >> END;

	return 0;
}