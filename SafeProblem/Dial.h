#pragma once

#include "Utility.cpp"
#include <ostream>

class Dial
{
private:

	//TODO: Maybe use shorts or ints because overflow will break program;
	char value;


public:
	
	Dial(char i = 0);
	~Dial() {};

	//Turn dial downwards (number increases)
	Dial operator+ (int i);	

	//Turn dial upwards	  (number decreases)
	Dial operator- (int i);		

	//Turn dial downwards (number increases)
	Dial &operator+= (int i);	

	//Turn dial upwards	  (number decreases)
	Dial &operator-= (int i);

	friend std::ostream &operator<<(std::ostream &o, Dial d);
};



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


