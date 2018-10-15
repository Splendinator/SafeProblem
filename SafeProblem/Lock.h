#pragma once

#include "Dial.h"




//Template instead of constant number because then we can just have an array of dials
//on the stack resulting in high cache hit rate. (maybe)
//Ask if this or just <Vector>s
template <int NUM_DIALS>
class Lock
{
public:
	
	//Unlock code.
	Dial CN[NUM_DIALS];

	//What the attacker sees.
	Dial LN[NUM_DIALS];

	//Hash used as ROOT for next lock.
	//Dial HN[NUM_DIALS];					(don't need to store this?)




	Lock() {};
	~Lock() {};


};

