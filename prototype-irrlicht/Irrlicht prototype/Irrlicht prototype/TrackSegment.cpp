#include "TrackSegment.hpp"


TrackSegment::TrackSegment(void)
{
	exitPoint.position.set(0,0,0);
	exitPoint.direction = 0;
}

TrackSegment::TrackSegment(int id)
{
	exitPoint.position.set(0,0,0);
	exitPoint.direction = 0;
	this->id = id;
}



TrackSegment::~TrackSegment(void)
{
}


void TrackSegment::generate(TrackPoint* origin, int smoothnes)
{
	core::list<core::vector3df> controlPoints;

	/******************* control points generation ****************************/
	//x,z is plane, y is elevation
	//add reset control points
	controlPoints.push_back(vector3df(0,0,0));
	controlPoints.push_back(vector3df(0,0,0));

	//add short stub to smooth the transion
	controlPoints.push_back(vector3df(10,0,0));

	//default implementation, for start we just add equally spaced segments and move them a little
	for(int i=2; i < 5; i++){
		irr::s32 r = random(20)-10;	//we have to retype tosigned otherwise compiler make stupid assumptions and let our number underflow
		controlPoints.push_back(core::vector3df(i*10,0, r ));
	}
	//repeat last point so the spline ends on it
	controlPoints.push_back( core::vector3df( *controlPoints.getLast() ));


	//move to our final coords
	if(origin != 0)
	{
		for(core::list<core::vector3df>::Iterator iterator = controlPoints.begin(); iterator != controlPoints.end();  iterator++)
		{
			(*iterator).rotateXZBy(origin->direction);
			(*iterator) += origin->position;
		}
	}

	vector3df last = *controlPoints.getLast();
	vector3df beforeLast = *(controlPoints.getLast()-2);
	vector3df diff = last-beforeLast;

	exitPoint.position.set(last);
	exitPoint.direction = diff.getHorizontalAngle().Y-90;


	int countControl = controlPoints.size();

	core::list<vector3df>::Iterator iterator = controlPoints.begin();
	for (int i =0; i < countControl-3; ++i, ++iterator )
	{
		vector3df p0 = *iterator;
		vector3df p1 = *(iterator+1);
		vector3df p2 = *(iterator+2);
		vector3df p3 = *(iterator+3);

		irr::f32 increment = 1.0/smoothnes;
		for(int step=0;step < smoothnes; step++)
		{
			irr::f32 position = increment*step;
			TrackPoint* point = new TrackPoint(position,p0,p1,p2,p3);
			trackPoints.push_back( point );
		}
	}



	
}


TrackPoint* TrackSegment::getExitPoint()
{
	return &(this->exitPoint);
	
}