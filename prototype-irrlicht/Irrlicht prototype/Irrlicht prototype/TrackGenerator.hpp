#pragma once
#include <irrlicht.h>
#include <vector>
#include "TrackUtil.hpp"
#include "CongruentGenerator.hpp"

using namespace std;
using namespace irr;
using namespace core;



class TrackGenerator : CongruentGenerator
{
protected:
	irr::u32 originalSeed;

	/** holds entry point for each segment */
	vector<TrackPoint> reentryValues;

	/** function that returns point of track **/
	list<TrackPoint>* getSegmentPoints(int);

public:
	TrackGenerator(irr::u32 seed);
	~TrackGenerator(void);
};

