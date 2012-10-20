#pragma once
#include <irrlicht.h>
#include "TrackUtil.hpp"
#include "CongruentGenerator.hpp"

using namespace irr;


class TrackSegment : public CongruentGenerator
{

public:
	TrackSegment(void);
	~TrackSegment(void);

	//generate track that will start at origin TrackPoint and will be smoothed by value
	void TrackSegment::generate(TrackPoint*, int);

	TrackPoint* getExitPoint();

	TrackPointList* getTrack();

protected:
	TrackPoint exitPoint;
	TrackPointList trackPoints;
};

