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
		controlPoints.push_back(core::vector3df(i*10,0,random(10)-5 ));
	}
}


TrackPoint* TrackSegment::getExitPoint()
{
	TrackPoint* point = new TrackPoint();
	
	vector3df last = *controlPoints.end();
	vector3df beforeLast = *(controlPoints.end()--);

	vector3df diff = beforeLast-last;

	point->position.set(last);
	point->direction = diff.getHorizontalAngle().Y;

	return point;
}