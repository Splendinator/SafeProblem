#include "Set.h"




Set::~Set()
{
}

std::ostream & operator<<(std::ostream & o, const Set s)
{
	o << "{";
	bool comma = false;
	int x;
	for (int i = 0; i < 16; ++i) {
		x = 1 << i;
		if (x & s.data) {
			if (comma) { o << ", "; }
			o << i;
			comma = true;
		}
	}
	o << "}";
	return o;
}
