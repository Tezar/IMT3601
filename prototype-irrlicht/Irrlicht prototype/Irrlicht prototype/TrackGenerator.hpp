#pragma once
#include <irrlicht.h>

using namespace irr;
using namespace core;

class TrackGenerator
{
protected:
	irr::u32 originalSeed;
	irr::u32 currentSeed;

	/** restarts generator to new sequence */
	void reseed(irr::u32);
	/** returns new random number */
	int random();

public:
	TrackGenerator(irr::u32 seed);
	~TrackGenerator(void);
};

