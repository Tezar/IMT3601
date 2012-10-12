#pragma once
#include <irrlicht.h>
#include <vector>

using namespace std;
using namespace irr;
using namespace core;


class TrackGenerator
{
protected:
	irr::u32 originalSeed;
	irr::u32 currentSeed;

	//holds entry and exit angle for each segment
	vector<irr::f32[2]> reentryValues;

	/** restarts generator to new sequence */
	void reseed(irr::u32);
	/** returns new random number */
	int random();

	/** function that returns point of track **/
	list<core::vector3df> getSegmentPoints(int);

public:
	TrackGenerator(irr::u32 seed);
	~TrackGenerator(void);
};

