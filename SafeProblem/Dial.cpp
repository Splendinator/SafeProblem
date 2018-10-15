#include "Dial.h"

//TODO: Consider removing modRef() since it doesn't effect the maths.


std::ostream &operator<<(std::ostream &o, Dial d) {
	return o << int(d.value);
}
