#pragma once
#include <irrlicht.h>
#include "TrackUtil.hpp"
#include "CongruentGenerator.hpp"

using namespace irr;


class TrackSegment : public CongruentGenerator
{

public:
	irr::u32 id;

	TrackSegment(void);
	TrackSegment(int);
	~TrackSegment(void);

	//generate track that will start at origin TrackPoint and will be smoothed by value
	void TrackSegment::generate(TrackPoint*, int);

	TrackPoint* getExitPoint();

	TrackPointList* getTrack();

protected:
	TrackPoint exitPoint;
	TrackPointList trackPoints;
};

