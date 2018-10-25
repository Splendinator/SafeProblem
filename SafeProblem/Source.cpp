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

inline int findHash(void *safes, int numSafes, Vector<Dial, 4> *hashes) {

	int counter = 0;

	Safe<5, 4> *s = (Safe<5, 4> *)safes;

	Vector<Dial, 4> dif = s[0][1].LN - s[0][0].LN;
	Vector<Dial, 4> target = (s[0][0].LN - s[0].ROOT);		//CHF + LHF;
	Vector<Dial, 4> phf = dif - target;


	Set a[4] = { 2047,2047,2047,2047 };
	Set b[4] = { 2047,2047,2047,2047 };
	Set c[4] = { 2047,2047,2047,2047 };
	Set d[4] = { 2047,2047,2047,2047 };





	for (int i = 0; i < numSafes; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 5; ++k) {

				if (j != 0) a[j] -= char(((s[i].ROOT[j] - s[i].ROOT[0]).toChar()) + Dial(((dif[j] - dif[0]).toChar()*k)).toChar());
				if (j != 1) b[j] -= char(((s[i].ROOT[j] - s[i].ROOT[1]).toChar()) + Dial(((dif[j] - dif[1]).toChar()*k)).toChar());
				if (j != 2) c[j] -= char(((s[i].ROOT[j] - s[i].ROOT[2]).toChar()) + Dial(((dif[j] - dif[2]).toChar()*k)).toChar());
				if (j != 3) d[j] -= char(((s[i].ROOT[j] - s[i].ROOT[3]).toChar()) + Dial(((dif[j] - dif[3]).toChar()*k)).toChar());

			}
		}
	}
	
	
	//cout << a[1] << endl << a[2] << endl << a[3] << endl << endl;
	//cout << b[0] << endl << b[2] << endl << b[3] << endl << endl;
	//cout << c[0] << endl << c[1] << endl << c[3] << endl << endl;
	//cout << d[0] << endl << d[1] << endl << d[2] << endl << endl;

	//Using b[0] AS AB
	//Using c[0] AS AC | Using C[1] as BC
	//Using d[0] AS AD...

	for (char ap = 0; ap < 10; ++ap) {
		for (char bp = 0; bp < 10; ++bp) {
			if (!((b[0] << ap).has(bp))) continue;
			for (char cp = 0; cp < 10; ++cp) {
				if (!(((c[0] << ap).has(cp)) || ((c[1] << bp).has(cp)))) continue;
				for (char dp = 0; dp < 10; ++dp) {
					if (!(((d[0] << ap).has(dp)) || ((d[1] << bp).has(dp)) || ((d[2] << cp).has(dp)))) continue;
					
					hashes[counter++] = Vector<Dial, 4>({ ap,bp,cp,dp });
					hashes[counter++] = target - hashes[counter - 1];
					hashes[counter++] = phf;
					
				
				}
			}
		}
	}
	
	return counter / 3;

}


int main(char **argv, int argc) {		
	
	int numSafes;
	Safe<5, 4> safes[10000];
	Vector<Dial, 4> hashes[10000];

	for (int i = 0; i < 10000; ++i)
		safes[i] = Safe<5,4>(UHF, LHF, PHF, DIF);

	//CW1
	IO keyFile("../key.txt");
	IO safeFile("../safe.txt");
	
	//CW2
	IO lockedFile("../locked.txt");
	IO solvedKeyFile("../keySolved.txt");
	


	cout << "What would you like to do?" << endl
		 << "1 - Generate safes from a random hash" << endl 
		 << "2 - " 

	try {
		//CW1 - Generate
		keyFile.printKey(roots, UHF, LHF, PHF, numSafes);
		safeFile.printMultiSafe(safes, numSafes);
		lockedFile.printLockedSafe(safes,numSafes);
	
		//CW2
		numSafes = lockedFile.readLockedSafe(safes);
	}
	catch (IOException err) {
		cout << err.what();
		exit(1);
	}
	
	numSafes = findHash(safes, numSafes, hashes);
	for (int i = 0; i < numSafes; ++i) {
		safes[i] = Safe<5,4>(hashes[3 * i], hashes[3 * i + 1], hashes[3 * i + 2]);
	}

	try {
		solvedKeyFile.printKey(safes, numSafes);
	}
	catch (IOException err) {
		cout << err.what();
		exit(1);
	}

	

	int END;
	cin >> END;

	return 0;
}