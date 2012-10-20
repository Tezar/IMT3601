#include <assert.h>
#include "TrackGenerator.hpp"


TrackGenerator::TrackGenerator(irr::u32 seed)
{
}


TrackGenerator::~TrackGenerator(void)
{
}

TrackPoint* TrackGenerator::getExitPoint(int position){
	if(position < 0) return 0;
	TrackSegment* segment = getSegment(position);
	return segment->getExitPoint();
}

TrackSegment* TrackGenerator::getSegment(int position)
{
	//todo:actually implement cache
	//todo: limit segment count to final number
	
	assert(position >= 0);

	TrackSegment* segment;

	segment = new TrackSegment(position);
	segment->seed(originalSeed);

	TrackPoint* origin = getExitPoint(position-1);
	segment->generate(origin);

	return segment;

}



       

