#include "IO.h"





IO::~IO()
{
}

void IO::printSolutions(Vector<Dial, 4> *roots, Vector<Dial, 4> UHF, Vector<Dial, 4> LHF, Vector<Dial, 4> PHF, unsigned int numRoots) throw (IOException)
{
	if (!fs.is_open()) throw IOException();
	for (int i = 0; i < numRoots; ++i) {
		fs << "ROOT:" << roots[i][0] << roots[i][1] << roots[i][2] << roots[i][3] << std::endl;
		fs << "UHF: " << UHF << std::endl;
		fs << "LHF: " << LHF << std::endl;
		fs << "PHF: " << PHF << std::endl;
	}
}
