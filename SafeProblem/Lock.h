#pragma once

#include "Dial.h"
#include "Vector.h"




//Template instead of constant number because then we can just have an array of dials
//on the stack resulting in high cache hit rate. (maybe)
//Ask if this or just <Vector>s
template <unsigned int NUM_DIALS>
class Lock
{
public:
	
	//Unlock code.
	Vector<Dial, NUM_DIALS> CN;
		
	//What the attacker sees.
	Vector<Dial, NUM_DIALS> LN;


	//Hash used as ROOT for next lock.
	//Dial HN[NUM_DIALS];					(don't need to store this?)




	Lock() {};
	~Lock() {};


};

