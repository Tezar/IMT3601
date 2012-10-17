#pragma once
#include <irrlicht.h>
#include <vector>
#include "TrackUtil.hpp"
#include "TrackSegment.hpp"
#include "CongruentGenerator.hpp"

using namespace std;
using namespace core;



class TrackGenerator : CongruentGenerator
{
protected:
	irr::u32 originalSeed;

	//todo: change to list...
	vector<TrackSegment*> segmentCache;

	TrackSegment* getSegment(int);

public:
	TrackGenerator(irr::u32 seed);
	~TrackGenerator(void);

	
	/** function that returns point of track **/
	list<TrackPoint>* getTrackPoints(int segment, int smoothnes);
	vector3df* spline4p(irr::f32, vector3df,vector3df,vector3df,vector3df); 
};

