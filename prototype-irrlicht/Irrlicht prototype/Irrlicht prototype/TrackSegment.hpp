#pragma once
#include <irrlicht.h>
#include "TrackUtil.hpp"
#include "CongruentGenerator.hpp"

#include "btBulletDynamicsCommon.h"

using namespace irr;


class TrackSegment : public CongruentGenerator
{

public:
	irr::u32 id;

	TrackSegment(void);
	TrackSegment(int);
	~TrackSegment(void);

	//generate track that will start at origin TrackPoint and will be smoothed by value
	void TrackSegment::generate(TrackPoint* origin=0, int smoothnes=10);

	//seperated control point generation so we can easily change behaviour in child object
	core::list<core::vector3df>* TrackSegment::createControlPoints();

	TrackPoint* getExitPoint();

	TrackPointList* getTrack();



	//physics representation btCollisionShape
	btCollisionShape* segmentShape;
	core::list<btRigidBody*>* segmentBodies;

protected:
	void init();

	core::list<btRigidBody*>* getBodies();

	TrackPoint exitPoint;
	TrackPointList trackPoints;
};

