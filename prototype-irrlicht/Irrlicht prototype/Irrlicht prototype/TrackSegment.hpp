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

	core::list<core::vector3df> controlPoints;


	void generate();
	TrackPoint* getExitPoint();


};

