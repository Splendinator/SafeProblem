#include <iostream>
#include "Safe.h"
#include "Utility.h"
#include "Dial.h"
#include "Vector.h"
#include "Set.h"
#include "IO.h"
#include <random>
#include <exception>
#include <fstream>

using namespace std;
using namespace util;

Vector<Dial,4> UHF, LHF, PHF, DIF;
Vector<Dial, 4> roots[10000];




inline void generateHash() {
	for (int i = 0; i < 4; ++i) {
		UHF[i] = (rand() % 19) - 9;
		LHF[i] = (rand() % 19) - 9;
		PHF[i] = (rand() % 19) - 9;
	}		

	DIF = UHF + LHF + PHF;

}


//LINEAR ORDER ROOT GENERATION ALGORITHM
//inline int generateRoot() {
//	
//	Safe<5, 4> s[10000];
//	
//	Dial d[4];
//	Vector<Dial, 4> root;  
//
//
//	for (int i = 0; i < 10000; ++i) {
//		d[3] = i % 10;
//		d[2] = i % 100 / 10;
//		d[1] = (i % 1000 / 100);
//		d[0] = (i / 1000);
//		root = d;
//
//		s[i] = Safe<5,4>(UHF, LHF, PHF, DIF);
//
//		s[i].solveLocks(root);
//
//	}
//
//	for (int i = 0; i < 10000; ++i) {
//
//		d[3] = i % 10;
//		d[2] = i % 100 / 10;
//		d[1] = (i % 1000 / 100);
//		d[0] = (i / 1000);
//
//		for (int j = 0; j < 5; ++j) {
//			if (Vector<Dial, 4>::hasDupes(s[i][j].CN))
//				goto next;
//		}
//		
//
//		//cout << d[0] << d[1] << d[2] << d[3] << " | ";
//		//cout << s[i][0].CN[0] << s[i][0].CN[1] << s[i][0].CN[2] << s[i][0].CN[3] << " ";
//		//cout << s[i][1].CN[0] << s[i][1].CN[1] << s[i][1].CN[2] << s[i][1].CN[3] << " ";
//		//cout << s[i][2].CN[0] << s[i][2].CN[1] << s[i][2].CN[2] << s[i][2].CN[3] << " ";
//		//cout << s[i][3].CN[0] << s[i][3].CN[1] << s[i][3].CN[2] << s[i][3].CN[3] << " ";
//		//cout << s[i][4].CN[0] << s[i][4].CN[1] << s[i][4].CN[2] << s[i][4].CN[3] << endl;
//		
//		next:
//		continue;
//	}
//	return 0;
//}

const static int NUMLOCKS = 5;

//LOGARITHMIC ORDER ROOT GENERATION ALGORITHM
inline int generateRoot2(void *safes) {
	

	Safe<NUMLOCKS, 4> *safe = (Safe<NUMLOCKS, 4> *)safes;

	int counter = 0;
	Set s[60];
	Set *ab = s, *ac = &s[10], *ad = &s[20], *bc = &s[30], *bd = &s[40], *cd = &s[50];	//Sets of possible numbers in the form XY[n] where X is the first dial, n is the number on that dial and Y is another dial.
																						//i.e  AB[2] = {3,4,5}  means    "If dial A is 2, dial B can be 3,4, or 5."
	
	Vector<Dial, 4> root;


	char relDif;		//Relative difference in rate of change of two dials.
	int temp = 0;
					
	//Generate Initial Values
	for (int i = 0; i < 3; ++i) { 
		for (int j = i + 1; j < 4; ++j) {
			relDif = (DIF[i] - DIF[j]).toChar();						for (int k = 0; k < NUMLOCKS; ++k)
				s[temp] |= Dial(relDif * k).toChar();
			s[temp].inverse();
			temp += 10;
		}
	}



	//Domino effect to get the rest
	for (int i = 1; i < 10; ++i) {
		ab[i] = ab[i-1] << 1;
		ac[i] = ac[i-1] << 1;
		ad[i] = ad[i-1] << 1;
		bc[i] = bc[i-1] << 1;
		bd[i] = bd[i-1] << 1;
		cd[i] = cd[i-1] << 1;
	}
	
	//Show Sets
	//for (int i = 0; i < 60; ++i)
	//	cout << s[i] << endl << ((i % 10 == 9) ? "\n" : "");

	//Smartly try all remaining possible combinations, deleting any impossibilities from future iterations.
	for (int a = 0; a < 10; ++a) {
		
		for (int b = 0; b < 10; ++b) {
			if (!ab[a].has(b)) {
				continue;
			}
			for (int c = 0; c < 10; ++c) {
				if (!ac[a].has(c) || !bc[b].has(c)) {
					if ((ac[a] & bc[b]) == 0) {				//This if statement checks for any potential redundancies as we go and eliminates them.
						for (int i = 0; i < 10; ++i)
							ab[Dial(a + i).toChar()] -= Dial(char(b) + i).toChar();
					}
					continue;
				}

				for (int d = 0; d < 10; ++d) {
					if (!ad[a].has(d) || !bd[b].has(d) || !cd[c].has(d)) {
						if ((ad[a] & bd[b]) == 0) {
							for (int i = 0; i < 10; ++i)
								ab[Dial(a + i).toChar()] -= Dial(char(b) + i).toChar();
						}
						if ((ad[a] & cd[c]) == 0) {
							for (int i = 0; i < 10; ++i)
								ac[Dial(a + i).toChar()] -= Dial(char(c) + i).toChar();
						}
						if ((bd[b] & cd[c]) == 0) {
							for (int i = 0; i < 10; ++i)
								bc[Dial(b + i).toChar()] -= Dial(char(c) + i).toChar();
						}
						continue;
					};
					root = Vector<Dial, 4>({ Dial(a) ,Dial(b), Dial(c), Dial(d) });
					root = root - UHF;
					safe[counter].solveLocks(root);
					roots[counter] = root;
					++counter;
				}
			}
		}


	}


	

	return counter;
}

inline void findHash(void *safes, int numSafes) {

	Safe<5, 4> *s = (Safe<5, 4> *)safes;

	Vector<Dial, 4> dif = s[0][1].LN - s[0][0].LN;
	Vector<Dial, 4> target = (s[0][0].LN - s[0].ROOT);		//CHF + LHF;
	Vector<Dial, 4> phf = dif - target;

	Set schf[4] = { 2047,2047,2047,2047 };
	
	for (int i = 0; i < numSafes; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 4; ++k) {
				if (k == i) continue;
				s[i].ROOT[j];
			}
		}
	}
	


}


int main(char **argv, int argc) {
	srand(141);
	generateHash();

	cout << UHF << endl;
	cout << LHF << endl;
	cout << PHF << endl;
	cout << DIF << endl;
	cout << endl;

	
	int numSafes;
	Safe<5, 4> safes[10000];
	
	for (int i = 0; i < 10000; ++i)
		safes[i] = Safe<5,4>(UHF, LHF, PHF, DIF);

	//CW1
	IO keyFile("../key.txt");
	IO safeFile("../safe.txt");
	
	//CW2
	IO lockedFile("../locked.txt");
	IO solvedKeyFile("../keySolved.txt");
	IO solvedSafeFile("../safeSolved.txt");
	

	numSafes = generateRoot2(safes);

//Option to generate safes randomly.
//Option to read them in from a key file.

//Option to decode safes from a locked file.

	try {
		//CW1 - Generate
		keyFile.printKey(roots, UHF, LHF, PHF, numSafes);
		safeFile.printMultiSafe(safes, numSafes);
		lockedFile.printLockedSafe(safes,numSafes);
	
		//CW2
		numSafes = lockedFile.readLockedSafe(safes);
		safeFile.printMultiSafe(safes, numSafes);
	}
	catch (IOException err) {
		cout << err.what();
		exit(1);
	}
	
	findHash(safes, numSafes);
	

	int END;
	cin >> END;

	return 0;
}