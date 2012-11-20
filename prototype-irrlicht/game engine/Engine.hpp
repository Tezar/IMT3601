#pragma once
#include "irrlicht.h"

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



class Engine
{
	
public:
	Vehicle* vehicles[MAX_VEHICLES];
	TrackGenerator * track;

	int numVehicles;
	int currentSegment;

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

	//get list of segments
	core::list<TrackSegment*>* getSegments();

	

protected:
	/** averages position of vehicles and updates member variable */
	inline void recalculatePosition();


	IrrlichtDevice* getDevice();

	//pointer to device, could be local, in taht case we must drop it in the end
	IrrlichtDevice* localDevice;
	IrrlichtDevice* device;

	/* checks if there should be more segments loaded, based on change of previous closest segment */
	void checkLoadedSegments(); 
	/* loads segments*/
	void loadSegments(int min, int max);

	core::list<TrackSegment*> segments;


	btRigidBody* bodies_vehicles[MAX_VEHICLES];	//references for vehicle bodies

	//physics system
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;

};

