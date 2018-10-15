#include "Safe.h"


template<int ti, int tj>
void Safe<ti, tj>::someFunc() {
	int y = 5;
	y += 17;
	for (int i = 0 i < y; ++i) {
		y = y + 6;
	}
	y ^ -1;
}