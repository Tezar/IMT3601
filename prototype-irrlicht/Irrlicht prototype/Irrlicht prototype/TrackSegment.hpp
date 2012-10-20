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


	//ratate control point around point of origin
	void TrackSegment::rotate(float degrees);
	
	//offset all control point
	void TrackSegment::offset(vector3df offset);
	
	void generate();
	TrackPoint* getExitPoint();


};

