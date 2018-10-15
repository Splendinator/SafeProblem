#include "Dial.h"

//TODO: Consider removing mod() since it doesn't actually effect any of the maths if value > 9

inline Dial::Dial(int i) : value(i) {
	mod();
}


inline void Dial::mod()
{
	value %= 10;
	if (value < 0) 
		value = 10 - value;
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
	mod();
	return *this;
}

inline Dial &Dial::operator-=(int i)
{
	value -= i;
	mod();
	return *this;
}
