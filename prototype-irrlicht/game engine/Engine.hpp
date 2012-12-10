#pragma once
#include "irrlicht.h"

#include "Vehicle.hpp"
#include "ObjectReader.hpp"
#include "TrackUtil.hpp"
#include "TrackGenerator.hpp"
#include "EngineObserver.hpp "


#include "btBulletDynamicsCommon.h"

using namespace irr;
using namespace io;

#define MAX_VEHICLES 4

#define ENGINE_NOTIFY(what) \
	for(core::list<EngineObserver*>::ConstIterator it = observers.begin(); it != observers.end(); it++) \
	{																									\
		(*it)->what;																					\
	}


//!if you change this value it will mess up all unscaled physical constrains!
#define ENGINE_STEP 20



class Engine
{
	
public:
	Vehicle* vehicles[MAX_VEHICLES];
	TrackGenerator * track;

	int numVehicles;
	int currentSegment;

	
	Engine(void);
	~Engine(void);

	/* averaged position of all vehicles for use by camera and track generato */
	vector3df averagePosition;
	

	Vehicle* Engine::addVehicle(ObjectRecord* record);
	
	void addObserver(EngineObserver*);
	void removeObserver(EngineObserver*);

	/** consumes time to make simulation, returns any leftovers 
		@par int time to be consumed
		@return int time not consumed
	*/
	int step(int);

	/** resets state of engine to initial conditions */
	void reset();

	//get list of segments
	core::list<TrackSegment*>* getSegments();


	
	//rigid body is needed for extracting transform matrix for first update of static body
	void notifyShapeNew(btCollisionShape*, ObjectRecord*, btRigidBody* = 0 );
	void notifyShapeUpdate(btCollisionShape*, const btTransform& );

	/* load single segment based on record */
	void Engine::loadSegment(ObjectRecord* record);

protected:
	core::list<EngineObserver*> observers;

	/** averages position of vehicles and updates member variable */
	inline void recalculatePosition();

	core::array<btVector3> waypoints;

	IrrlichtDevice* getDevice();

	//pointer to device, could be local, in taht case we must drop it in the end
	IrrlichtDevice* localDevice;
	IrrlichtDevice* device;

	/* checks if there should be more segments loaded, based on change of previous closest segment */
	void checkLoadedSegments(); 
	/* loads segments*/
	void loadSegments(int min, int max);
	
	void checkWaypoint(Vehicle* vehicle);

	core::list<TrackSegment*> segments;



	//physics system
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;

};

