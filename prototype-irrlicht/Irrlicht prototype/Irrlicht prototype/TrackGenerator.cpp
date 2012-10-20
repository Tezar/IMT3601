#include "TrackGenerator.hpp"


TrackGenerator::TrackGenerator(irr::u32 seed)
{
}


TrackGenerator::~TrackGenerator(void)
{
}

TrackPoint* TrackGenerator::getExitPoint(int position){
	int size = exitPoints.size();
	//if we dont have enough we reserve some more
	if( size <= position)
	{
		exitPoints.resize(position+8,0);
	}

	//try to get it
	TrackPoint* point = exitPoints[position];

	//we have it in cache, our job here is done
	if(point != 0) return exitPoints[position];

	TrackSegment* segment = getSegment(position-1);
	point = segment->getExitPoint();
	
	delete segment;
	return point;
}

TrackSegment* TrackGenerator::getSegment(int position)
{
	TrackSegment* segment;

	segment = new TrackSegment();
	segment->seed(originalSeed*(position+1));
	segment->generate();

	if(position > 0)
	{
		TrackPoint * point = getExitPoint(position-1);
		//segment->rotate(point->direction);
		segment->offset(point->position);
		
	}


	return segment;
}



std::list<TrackPoint*> TrackGenerator::getTrackPoints(int position, int smoothnes)
{
	//reset generated point so far
	for(std::list<TrackPoint*>::const_iterator iterator = points.begin(); iterator != points.end();  iterator++)
	{
		delete (*iterator);	//delete trackpoint to prevent memory leaks
	}
	points.clear();

	/*****************************************************/

	TrackSegment* segment = getSegment(position);
	
	int countControl = segment->controlPoints.size();

	core::list<vector3df>::Iterator iterator = segment->controlPoints.begin();
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
			points.push_back( point );
		}
	}

	delete segment;
	return points;
}


       

