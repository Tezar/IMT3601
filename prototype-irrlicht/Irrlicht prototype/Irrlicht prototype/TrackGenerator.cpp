#include "TrackGenerator.hpp"


TrackGenerator::TrackGenerator(irr::u32 seed)
{
}


TrackGenerator::~TrackGenerator(void)
{
}


TrackSegment* TrackGenerator::getSegment(int position)
{
	int size = segmentCache.size();
	//if we dont have enough we reserve some more
	if( size <= position)
	{
		segmentCache.reserve(position+3);
	}

	TrackSegment* segment = segmentCache[position];

	if(segment != 0) return segment;

	segment = new TrackSegment();
	segment->seed(originalSeed+position);
	segment->generate();

	segmentCache[position] = segment;

	return segment;
}

list<TrackPoint>* TrackGenerator::getTrackPoints(int position, int smoothnes = 30)
{
	list<TrackPoint>* points = new list<TrackPoint>();
	TrackSegment* segment = getSegment(position);
	
	int countControl = segment->controlPoints.size()+2;
	
	for ( irr::core::list<vector3df>::Iterator iterator = segment->controlPoints.begin(), end = segment->controlPoints.end()-3; iterator != end; ++iterator)
	{
		vector3df p0 = *iterator;
		vector3df p1 = *(iterator+1);
		vector3df p2 = *(iterator+2);
		vector3df p3 = *(iterator+3);

		irr::f32 increment = 1.0/smoothnes;
		for(int step=0;step < smoothnes; step++)
		{
			irr::f32 position = increment*step;
			TrackPoint point = TrackPoint(position,p0,p1,p2,p3);
			points->push_back( point );
		}
	}

	

	vector<core::vector3df*> controlPoints (countControl);
	//controlPoints[0] = 

	return points;
}


       

