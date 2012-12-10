#pragma once
#include <irrlicht.h>

using namespace irr;


class CongruentGenerator
{
protected:
	irr::u32 currentSeed;

public:
	CongruentGenerator(void);
	~CongruentGenerator(void);

	/** restarts generator to new sequence */
	void seed(irr::u32);
	/** returns new random number */
	irr::u32 random(int maxNumber);

};

