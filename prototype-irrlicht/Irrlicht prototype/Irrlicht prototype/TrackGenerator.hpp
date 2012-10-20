#pragma once
#include <irrlicht.h>
#include <vector>
#include "TrackUtil.hpp"
#include "TrackSegment.hpp"
#include "CongruentGenerator.hpp"

using namespace std;

class TrackGenerator : CongruentGenerator
{
protected:
	irr::u32 originalSeed;

	//todo: change to list...
	vector<TrackPoint*> exitPoints;

	TrackSegment* getSegment(int);
	TrackPoint* getExitPoint(int);

	std::list<TrackPoint*> points;

public:
	TrackGenerator(irr::u32 seed);
	~TrackGenerator(void);

	
	/** function that returns point of track **/
	std::list<TrackPoint*> getTrackPoints(int segment, int smoothnes=30);
	vector3df* spline4p(irr::f32, vector3df,vector3df,vector3df,vector3df); 
};

