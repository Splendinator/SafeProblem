#pragma once

#include "Dial.h"


//Template instead of constant number because then we can just have an array of dials
//on the stack resulting in high cache hit rate. (maybe)
//Ask if this or just <Vector>s
template <int NUM_DIALS>
class Lock
{
private:
	Dial dials[NUM_DIALS];

public:

	Lock() {};
	~Lock() {};


};

