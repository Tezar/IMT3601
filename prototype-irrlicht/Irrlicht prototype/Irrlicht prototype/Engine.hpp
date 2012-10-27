#pragma once


#include "Vehicle.hpp"
#include "TrackUtil.hpp"
#include "TrackGenerator.hpp"

#include "btBulletDynamicsCommon.h"

#define MAX_VEHICLES 4

//!if you change this value it will mess up all unscaled physical constrains!
#define ENGINE_STEP 10


class Engine
{
	
public:
	Vehicle* vehicles[MAX_VEHICLES];
	TrackGenerator * track;

	int numVehicles;

	Engine(void);
	~Engine(void);

	/* averaged position of all vehicles for use by camera and track generato */
	vector3df averagePosition;
	

	void addVehicle(Vehicle*);
	
	/** consumes time to make simulation, returns any leftovers 
		@par int time to be consumed
		@return int time not consumed
	*/
	int step(int);

	/** resets state of engine to initial conditions */
	void reset();

	core::list<TrackSegment*>* getSegments();

protected:
	/** averages position of vehicles and updates member variable */
	inline void recalculatePosition();

	core::list<TrackSegment*> segments;

	//physics system
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;

};

