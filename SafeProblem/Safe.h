#pragma once

#include "Lock.h"

//Templating this way doesn't seem to recompile, since it works when definitions are in header file??
template <int NUM_LOCKS, int NUM_DIALS>
class Safe
{
private:
	Lock<NUM_DIALS> locks[NUM_LOCKS];

public:

	Safe() {};
	~Safe() {};



};

