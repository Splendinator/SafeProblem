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
	Dial operator+ (const int i) const;	

	//Turn dial upwards	  (number decreases)
	Dial operator- (const int i) const;

	//Turn dial downwards (number increases)
	Dial &operator+= (const int i);

	//Turn dial upwards	  (number decreases)
	Dial &operator-= (const int i);

	//Turn dial downwards (number increases)
	Dial operator+ (const Dial i) const;

	//Turn dial upwards	  (number decreases)
	Dial operator- (const Dial i) const;

	//Turn dial downwards (number increases)
	Dial &operator+= (const Dial i);

	//Turn dial upwards	  (number decreases)
	Dial &operator-= (const Dial i);

	//Multiply by a number (then mod())
	Dial &operator*=(const int i);

	
	bool operator==(const Dial d) const;

	bool operator<(const int i) const { return value < i; }
	bool operator>(const int i) const { return value > i; };



	

	friend std::ostream &operator<<(std::ostream &o, Dial d);
};



inline Dial::Dial(char i) : value(i) {
	util::modRef(value);
}


inline Dial Dial::operator+(const int i) const
{
	return Dial(value + i);
}

inline Dial Dial::operator-(const int i) const
{
	return Dial(value - i);
}

inline Dial &Dial::operator+=(const int i)
{
	value += i;
	util::modRef(value);
	return *this;
}

inline Dial &Dial::operator-=(const int i)
{
	value -= i;
	util::modRef(value);
	return *this;
}



inline Dial Dial::operator+(const Dial i) const
{
	return Dial(value + i.value);
}

inline Dial Dial::operator-(const Dial i) const
{
	return Dial(value - i.value);
}

inline Dial &Dial::operator+=(const Dial i)
{
	value += i.value;
	util::modRef(value);
	return *this;
}

inline Dial &Dial::operator-=(const Dial i)
{
	value -= i.value;
	util::modRef(value);
	return *this;
}

inline Dial &Dial::operator*=(const int i)
{
	value *= i;
	util::modRef(value);
	return *this;
}

inline bool Dial::operator==(const Dial d) const
{
	return value == d.value;
}



