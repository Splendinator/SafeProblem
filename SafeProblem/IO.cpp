#include "IO.h"






void IO::printNumSolutions(unsigned int x) throw(IOException)
{
	if (!fs.is_open()) throw IOException();
	fs.seekg(0, 0);
	fs << "NS " << x << std::endl;
}

void IO::printKey(Vector<Dial, 4> *roots, Vector<Dial, 4> UHF, Vector<Dial, 4> LHF, Vector<Dial, 4> PHF, unsigned int numRoots) throw (IOException)
{
	if (!fs.is_open()) throw IOException();
	fs.seekg(0, 0);
	printNumSolutions(numRoots);
	for (int i = 0; i < numRoots; ++i) {
		fs << "ROOT:" << roots[i][0] << roots[i][1] << roots[i][2] << roots[i][3] << std::endl;
		fs << "UHF: " << UHF << std::endl;
		fs << "LHF: " << LHF << std::endl;
		fs << "PHF: " << PHF << std::endl;
	}
}

void IO::printKey(Safe<5, 4>* s, int numSafes) throw(IOException)
{
	if (!fs.is_open()) throw IOException();
	printNumSolutions(numSafes);

	for (int i = 0; i < numSafes; ++i) {
		fs << "ROOT: " << s[i].ROOT << std::endl;
		fs << "UHF: " << s[i].UHF << std::endl;
		fs << "LHF: " << s[i].LHF << std::endl;
		fs << "PHF: " << s[i].PHF << std::endl;
	}
}


void IO::printLockedSafe(Safe<5, 4> *s, int numSafes) throw(IOException)
{

	if (!fs.is_open()) throw IOException();
	fs.seekg(0, 0);
	printNumSolutions(numSafes);
	for (int j = 0; j < numSafes; ++j) {
		fs << "ROOT: " << s[j].ROOT << std::endl;
		for (int i = 0; i < 5; ++i) {
			fs << "LN" << i << ": " << s[j].locks[i].LN << std::endl;
		}
	}
}

int IO::readLockedSafe(Safe<5, 4>* safe) throw(IOException)
{
	if (!fs.is_open()) throw IOException();
	fs.seekg(0, 0);

	int numSafes;
	int x;
	std::string s;
	char c[4];
	Dial d[24];

	fs >> s;		
	fs >> numSafes;

	for (int i = 0; i < numSafes; ++i) {
		for (int j = 0; j < 6 /* NUM_LOCKS + 1 */; ++j) {
			fs >> s;
			for (int k = 0; k < 4; ++k) {
				while (!((fs >> c[k], c[k]) >= 48 && c[k] <= 57) && !(c[k] == '+') && !(c[k] == '-'));

				if (c[k] == '+') {
					fs >> x;
					d[k + 4 * j] = x;
				}
				else if (c[k] == '-') {
					fs >> x;
					x = -x;
					d[k + 4 * j] = x;
				}
				else {
					c[k] -= 48;
					d[k + 4 * j] = c[k];
				}
			}
		}
		safe[i] = Safe<5,4>();
		safe[i].ROOT = Vector<Dial, 4>({ d[0], d[1], d[2], d[3] });

		for (int j = 1; j < 6 /*NUM_LOCKS*/; ++j)
			safe[i].locks[j-1].LN = Vector<Dial,4>({ d[j * 4 + 0], d[j * 4 + 1], d[j * 4 + 2], d[j * 4 + 3] });
		
	}
	return numSafes;
}

void IO::printMultiSafe(Safe<5, 4>* safes, int numSafes)
{
	fs.seekg(0, 0);
	printNumSolutions(numSafes);
	for (int i = 0; i < numSafes; ++i) {
		fs << safes[i];
	}
}



//void IO::printLockedSafe(const Safe<5, 4> &s) throw(IOException)
//{
//	if (!fs.is_open()) throw IOException();
//	fs << "ROOT: " << s.ROOT << std::endl;
//	for (int i = 0; i < 5; ++i) {
//		fs << "LN" << i << ": " << s.locks[i].LN << std::endl;
//	}
//}

//void IO::readLockedSafe(Safe<5, 4> *safe) {
//
//	int x;
//	std::string s;
//	char c[4];
//	Dial d[24];
//
//	fs >> s;		//NS
//	fs >> x;		
//
//	for (int i = 0; i < x; ++i) {
//		for (int j = 0; j < 6 /* NUM_LOCKS + ! */; ++j) {
//			for (int k = 0; k < 4; ++k) {
//				while (!((fs >> c[i], c[i]) >= 48 && c[i] <= 57) && !(c[i] == '+') && !(c[i] == '-'));
//
//				//std::cout << c[i];
//				if (c[k] == '+') {
//					fs >> x;
//					d[k + 4 * j] = x;
//				}
//				else if (c[k] == '-') {
//					fs >> x;
//					x = -x;
//					d[k + 4 * j] = x;
//				}
//				else {
//					c[k] -= 48;
//					d[k + 4 * j] = c[i];
//				}
//				std::cout << d[k];
//			}
//			std::cout << std::endl;
//		}
//	}
//
//}
//

