#pragma once
#include <irrlicht.h>
#include <vector>
#include "TrackUtil.hpp"
#include "TrackSegment.hpp"
#include "CongruentGenerator.hpp"

using namespace std;

class TrackGenerator : CongruentGenerator
{
protected:
	irr::u32 originalSeed;

	

	core::list<TrackSegment*> segmentsCache;

	TrackPoint* getExitPoint(int);

	

public:
	TrackGenerator(irr::u32 seed);
	~TrackGenerator(void);

	core::list<TrackSegment*> segments;
	TrackSegment* getSegment(int);
	
	/** function that returns point of track **/

};

