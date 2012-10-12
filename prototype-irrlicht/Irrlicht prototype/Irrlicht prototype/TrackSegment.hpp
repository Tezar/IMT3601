#pragma once
#include <irrlicht.h>
#include "TrackUtil.hpp"
#include "CongruentGenerator.hpp"

using namespace irr;
using namespace core;


class TrackSegment : CongruentGenerator
{

public:
	TrackSegment(void);
	~TrackSegment(void);

	list<TrackPoint>* generateTrackPoints();
};

