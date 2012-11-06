#include "TrackSegment.hpp"


TrackSegment::TrackSegment(void)
{
	init();
}

TrackSegment::TrackSegment(int id)
{
	init();
	this->id = id;
}


void TrackSegment::init()
{
	exitPoint.position.set(0,0,0);
	exitPoint.direction = 0;

	segmentShape = 0;
	segmentBodies = 0;
}

TrackSegment::~TrackSegment(void)
{
	//remove what we allocated
	if(segmentShape)
	{
		delete segmentShape;
		segmentShape = 0;
	}
	
	if(segmentBodies){
		//todo: actually list thru them a nd free them as well

		delete segmentBodies;
		segmentBodies = 0;
	}
		

}



core::list<core::vector3df>* TrackSegment::createControlPoints(){
	core::list<core::vector3df>* controlPoints = new core::list<core::vector3df>();

	/******************* control points generation ****************************/
	//x,z is plane, y is elevation
	//add reset control points

	//irrlich angle calculation presumes that 0 angle o Y axis is aligned with Z axis, so it's imporatant to do gennerall progress 0 is aligned with Z axis, so its 
	controlPoints->push_back(vector3df(0,0,-50)); //far away control point that will assure straight connection
	controlPoints->push_back(vector3df(0,0,0));
	controlPoints->push_back(vector3df(0,0,10));

	//add short stub to smooth the transion
	controlPoints->push_back(vector3df(10,0,10));
	//controlPoints.push_back(vector3df(0,0,15));
	//controlPoints.push_back(vector3df(0,0,20));
	
	
	//default implementation, for start we just add equally spaced segments and move them a little
	for(int i=4; i < 6; i++){
		irr::s32 r = random(10)-5;	//we have to retype tosigned otherwise compiler make stupid assumptions and let our number underflow
		controlPoints->push_back(core::vector3df(r,0, i*10 ));
	}
	//repeat last point so the spline ends on it
	controlPoints->push_back( core::vector3df( *controlPoints->getLast() ));


	return controlPoints;

} 


void TrackSegment::generate(TrackPoint* origin, int smoothnes)
{
	core::list<core::vector3df>* controlPoints = createControlPoints();

	//move to our final(global) coords 
	if(origin != 0)
	{
		for(core::list<core::vector3df>::Iterator iterator = controlPoints->begin(); iterator != controlPoints->end();  iterator++)
		{
			(*iterator).rotateXZBy(-origin->direction);
			(*iterator) += origin->position;
		}
	}

	
	vector3df last = *controlPoints->getLast();
	vector3df beforeLast = *(controlPoints->getLast()-2);
	vector3df diff = last-beforeLast;

	exitPoint.position.set(last);
	exitPoint.direction = diff.getHorizontalAngle().Y;



	int countControl = controlPoints->size();

	TrackPoint * previousPoint = 0;

	core::list<vector3df>::Iterator iterator = controlPoints->begin();
	for (int i =0; i < countControl-3; ++i, iterator++ )
	{
		vector3df p0 = *iterator;
		vector3df p1 = *(iterator+1);
		vector3df p2 = *(iterator+2);
		vector3df p3 = *(iterator+3);

		irr::f32 increment = 1.0/smoothnes;
		//todo: add direction
		for(int step=0;step < smoothnes; step++)
		{
			irr::f32 position = increment*step;
			TrackPoint* point = new TrackPoint(position,p0,p1,p2,p3);
			
			if(previousPoint == 0)
			{
				point->direction = origin == 0 ? 90 : origin->direction;
			}else
			{
				vector3df diff = point->position-previousPoint->position ;
				vector3df angl = diff.getHorizontalAngle();
				
				f32 f = diff.getHorizontalAngle().Y;
				point->direction = f;
			}

			trackPoints.push_back( point );
			previousPoint = point;
		}

	}

	delete controlPoints;

	
}


core::list<btRigidBody*>* TrackSegment::getBodies()
{
	if(segmentBodies)
	{
		//great we already generated them
		return segmentBodies;
	}

	segmentShape = new btBoxShape(btVector3(10,10,10));

	segmentBodies = new  core::list<btRigidBody*>(); 

	//0 mass, no motion state, segment shape and zero inertia
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,0,segmentShape,btVector3(0,0,0));

	TrackPointList* track = getTrack();

	for(TrackPointList::ConstIterator iterator = track->begin(); iterator != track->end();  iterator++)
		{
			segmentBodies->push_back(new btRigidBody(groundRigidBodyCI));
		} //end trackpoint loop

	return segmentBodies;
}


TrackPointList* TrackSegment::getTrack()
{
	return &(this->trackPoints);
}

TrackPoint* TrackSegment::getExitPoint()
{
	return &(this->exitPoint);
	
}