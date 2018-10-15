#pragma once

#include "Utility.cpp"

class Dial
{
private:

	//Can't use unsigned because it fucks with mod() of negative numbers;
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


};

