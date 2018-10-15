#include "Dial.h"

//TODO: Consider removing modRef() since it doesn't actually effect any of the maths if value > 9

inline Dial::Dial(char i) : value(i) {
	util::modRef(value);
}



inline Dial Dial::operator+(int i)
{
	return Dial(value + i);
}

inline Dial Dial::operator-(int i)
{
	return Dial(value - i);
}

inline Dial &Dial::operator+=(int i)
{
	value += i;
	util::modRef(value);
	return *this;
}

inline Dial &Dial::operator-=(int i)
{
	value -= i;
	util::modRef(value);
	return *this;
}
