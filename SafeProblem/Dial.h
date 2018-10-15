#pragma once
class Dial
{
private:

	//Can't use unsigned because it fucks with mod() of negative numbers;
	char value;

	//Keeps the value between 0 and 10;
	void mod();


public:
	
	
	Dial(int i = 0);
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

