#pragma once

#include <iostream>

//Set representation of the numbers between 0 and 16.
class Set
{
private:

	int data;

	//Keep it to 10 nums and loop the ones that fall off;
	void trim();

public:

	Set(int s = 0) : data(s) { trim(); };
	~Set();

	//Union
	Set &operator |=(Set s);
	Set operator |(Set s);

	//Intersection
	Set &operator &=(Set s);
	Set operator &(Set s);

	friend std::ostream &operator<<(std::ostream &o, const Set s);

};

inline Set & Set::operator|=(Set s)
{
	data |= s.data;
	trim();
	return *this;
}

inline Set Set::operator|(Set s)
{
	return Set(data | s.data);
}


inline Set & Set::operator&=(Set s)
{
	data &= s.data;
	trim();
	return *this;
}

inline Set Set::operator&(Set s)
{
	return Set(data & s.data);
}

//TODO: Generalise.
inline void Set::trim()
{
	int i = data & 0b1111110000000000;
	i >>= 10;

	data &= 0b0000001111111111;
	data |= i;

}