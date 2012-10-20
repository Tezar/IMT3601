#include "TrackSegment.hpp"


TrackSegment::TrackSegment(void)
{
	//x,z is plane, y is elevation
	
	//add reset control points
	controlPoints.push_back(vector3df(0,0,0));
	controlPoints.push_back(vector3df(0,0,0));
	
	//add short stub to smooth the transion
	controlPoints.push_back(vector3df(10,0,0));

}


TrackSegment::~TrackSegment(void)
{
}


void TrackSegment::generate()
{
	//default implementation, for start we just add equally spaced segments and move them a little
	
	for(int i=2; i < 5; i++){
		irr::s32 r = random(20)-10;	//we have to retype tosigned otherwise compiler make stupid assumptions and let our number underflow
		controlPoints.push_back(core::vector3df(i*10,0, r ));
	}
	controlPoints.push_back( core::vector3df( *controlPoints.getLast() ));
}

void TrackSegment::rotate(float degrees)
{
	//rotate around origin
	for(core::list<core::vector3df>::Iterator iterator = controlPoints.begin(); iterator != controlPoints.end();  iterator++)
	{
		(*iterator).rotateXZBy(degrees);
	}
}

void TrackSegment::offset(vector3df offset)
{
	//offset all control point
	for(core::list<core::vector3df>::Iterator iterator = controlPoints.begin(); iterator != controlPoints.end();  iterator++)
	{
		(*iterator) += offset;
	}
}



TrackPoint* TrackSegment::getExitPoint()
{
	TrackPoint* point = new TrackPoint();
	
	vector3df last = *controlPoints.getLast();
	vector3df beforeLast = *(controlPoints.getLast()-2);

	vector3df diff = last-beforeLast;

	point->position.set(last);
	point->direction = diff.getHorizontalAngle().Y-90;

	return point;
}