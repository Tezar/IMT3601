#pragma once
#include <irrlicht.h>
#include "TrackUtil.hpp"

using namespace irr;
using namespace core;


class CongruentGenerator
{
protected:
	irr::u32 currentSeed;

public:
	CongruentGenerator(void);
	~CongruentGenerator(void);

	/** restarts generator to new sequence */
	void reseed(irr::u32);
	/** returns new random number */
	int random();

};

