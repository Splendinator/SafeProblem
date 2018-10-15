#include "Utility.h"

inline void util::modRef(int &i) {
	i %= 10;
	if (i < 0) i += 10;
}


inline void util::modRef(char &i) {
	i %= 10;
	if (i < 0) i += 10;
}


inline int util::mod(int i) {
	i %= 10;
	if (i < 0) i += 10;
	return i;
}
