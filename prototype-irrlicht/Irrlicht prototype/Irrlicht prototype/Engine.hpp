#pragma once

#include "Vehicle.hpp"
#include "TrackUtil.hpp"
#include "TrackGenerator.hpp"

#include "btBulletDynamicsCommon.h"

#define MAX_VEHICLES 4

#define MAKE_VEHICLE_ID(x) (x | (1 << 31) )
#define IS_VEHICLE_ID(x) (x & (1 << 31) ) ? true : false
#define GET_VEHICLE_ID(x) (x & (~(1 << 31)) )

//!if you change this value it will mess up all unscaled physical constrains!
#define ENGINE_STEP 20



/* "interface" for listeners */
class EngineListener{
	public:
		virtual void onBodyMovement(irr::u32 id,const btTransform* transform){};
		virtual void onVehicleMovement(irr::u32 id,const btTransform* transform){};
		virtual void afterSegmentLoaded(TrackSegment* segment){};
		virtual void beforeSegmentUnLoaded(TrackSegment* segment){};

};


class Engine
{
	
public:
	Vehicle* vehicles[MAX_VEHICLES];
	TrackGenerator * track;

	int numVehicles;

	EngineListener* listener;

	Engine(void);
	~Engine(void);

	/* averaged position of all vehicles for use by camera and track generato */
	vector3df averagePosition;
	

	Vehicle* addVehicle(Vehicle*);
	
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


	btRigidBody* bodies_vehicles[MAX_VEHICLES];	//references for vehicle bodies

	//physics system
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;

};

