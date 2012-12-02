#include <assert.h>
#include <windows.h>
#include <stdio.h>
#include <functional>
#include "Engine.hpp"
#include "EngineBodyState.hpp"

Engine::Engine(void)
{
	numVehicles = 0;

	track = new TrackGenerator(69696969);	//seed with randomly picked number...
	averagePosition.set(0,0,0);

	// Build the broadphase
    broadphase = new btDbvtBroadphase();
 
    // Set up the collision configuration and dispatcher
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
    // The actual physics solver
    solver = new btSequentialImpulseConstraintSolver;
 
    // The world.
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));

}


Engine::~Engine(void)
{
	delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;

	delete track;
}


Vehicle* Engine::addVehicle(ObjectRecord* record)
{
	assert( record != 0);
	assert( record->type == EOT_VEHICLE );
	assert(numVehicles < MAX_VEHICLES);

	Vehicle * vehicle = new Vehicle();

	int currentVehicle = numVehicles++;
	vehicles[currentVehicle] = vehicle;

	//tuning 
	btRaycastVehicle::btVehicleTuning vehicleTuning;

	btRaycastVehicle* rayVehicle = 0;

	for(core::list<ObjectRecord*>::ConstIterator it = record->children.begin(); it != record->children.end();it++)
	{
		ObjectRecord* object = (*it);
		
		switch( object->type ){
		case EOT_CHASSIS:{
			
			//we shape our world
			btCollisionShape* shape = object->createShape();
			assert(shape != 0);


			//for monitoring
			EngineBodyState* motionState = new  EngineVehicleState(this, vehicle, btTransform(btQuaternion(0,0,0,1),object->position));
			//physics stuff
			btScalar mass = 1+10*currentVehicle;
			btVector3 inertia(0,0,0);
			shape->calculateLocalInertia(mass,inertia);

			btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,shape,inertia);
			//construct
			btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);
			//loopback link
			motionState->setBody(rigidBody);
			
			//store reference for our chassis inside the vehicle
			vehicle->chassis = rigidBody; 

			//ve create our vehicle from our body
			btVehicleRaycaster* vehicleRayCaster = new btDefaultVehicleRaycaster(dynamicsWorld);
			rayVehicle = new btRaycastVehicle(vehicleTuning,rigidBody,vehicleRayCaster);

			vehicle->pointer = rayVehicle;

			//add our body to the world and deactivate deactivation
			rigidBody->setActivationState(DISABLE_DEACTIVATION);
			dynamicsWorld->addRigidBody(rigidBody);

			//is this necessary?
			rayVehicle->setCoordinateSystem(0,1,2);

			notifyShapeNew(shape, object );
			
			}
			break;
		case EOT_WHEEL:
			{
				//when we want to add wheels, we have to have defined vehicle
				assert(rayVehicle != 0); 
				//object->position
				btWheelInfo& wheel =  rayVehicle->addWheel( object->position , btVector3(0,-1,0),btVector3 (-1,0,0), 0.5, 6, vehicleTuning,false);

				float	gVehicleSteering = 0.f;
				float	steeringIncrement = 0.04f;
				float	steeringClamp = 0.3f;
				float	wheelRadius = 0.5f;
				float	wheelWidth = 0.4f;
				float	wheelFriction = 1000;//BT_LARGE_FLOAT;
				float	suspensionStiffness = 20.f;
				float	suspensionDamping = 2.3f;
				float	suspensionCompression = 4.4f;
				float	rollInfluence = 0.1f;//1.0f;

				wheel.m_suspensionStiffness = suspensionStiffness;
				wheel.m_wheelsDampingRelaxation = suspensionDamping;
				wheel.m_wheelsDampingCompression = suspensionCompression;
				wheel.m_frictionSlip = wheelFriction;
				wheel.m_rollInfluence = rollInfluence;

				//we shape our world, and it is for our eyes only
				btCollisionShape* shape = object->createShape();
				assert(shape != 0);

				vehicle->addShape(shape);
			
				notifyShapeNew(shape, object);
			
			}
			break;
		default:
			assert(false);
			break;
		}
	}

	vehicle->pointer->resetSuspension();
	for (int i=0;i<vehicle->pointer->getNumWheels();i++)
	{
		//synchronize the wheels with the (interpolated) chassis worldtransform
		vehicle->pointer->updateWheelTransform(i,true);
	}

	return vehicle;
}


int Engine::step(int toDo)
{
	//todo:physics
	//todo:collisions
	int i = 0;
	while(toDo > ENGINE_STEP){
		i++;
		dynamicsWorld->stepSimulation(ENGINE_STEP/1000.0,10);
		toDo -= ENGINE_STEP;
	}
	
	recalculatePosition();
	//that can be done not so often, maybe 0.5s?
	//checkLoadedSegments();

	return toDo;
}


void Engine::reset()
{
	currentSegment = -1;

	//todo:
	/*	placeVehicles( point 1 , point 2)
	
			point2
					|
					|
				*  *  *  *
			point1
			* = vehicle
	*/

	//memmory leaks!!!
	
	/*
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,0.1,0.1),1);
	btDefaultMotionState* groundMotionState =
                new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-3,0)));

	btRigidBody::btRigidBodyConstructionInfo
                groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));

	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);
	*/
}


inline void Engine::recalculatePosition()
{
	static float posX;
	static float posY;
	static float posZ;

	posX = 0;
	posY = 0;
	posZ = 0;

	for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
		Vehicle* v = vehicles[nVehicle];
		btTransform trans;

		v->chassis->getMotionState()->getWorldTransform(trans);
		
		btVector3 pos = trans.getOrigin();

		posX += pos.x();
		posY += pos.y();
		posZ += pos.z();
	}
	averagePosition.set(posX/numVehicles, posY/numVehicles, posZ/numVehicles);
}




void Engine::checkLoadedSegments()
{
	int segment = -1; //segments vehicles are in

	vector3df planarAveragedPosition = vector3df(averagePosition);
	planarAveragedPosition.Y = 0; //we ignore elevation for this calculation

	for(core::list<TrackSegment*>::ConstIterator segment_iterator = segments.begin(); segment_iterator != segments.end(); segment_iterator++)
	{
		TrackPointList * track = (*segment_iterator)->getTrack();

		for(TrackPointList::ConstIterator iterator = track->begin(); iterator != track->end();  iterator++)
		{
			irr::f32 dist =	planarAveragedPosition.getDistanceFrom( (*iterator)->position);
			if(dist < 5.f)
			{
				segment = (*segment_iterator)->id;
				break;
			}
		} //end trackpoint loop

		if(segment >= 0) break;	//we have found our segment
	}	//end segment loop

	if( (segment != currentSegment) || currentSegment < 0)
	{
		loadSegments(segment-1, segment+3);
		currentSegment = segment;
	}
}

void Engine::loadSegments(int min, int max)
{
	min = min < 0 ? 0 : min;
	assert(max > min);
	
	std::list<int> toBeLoaded;

	//add all segments to be loaded
	for(int i = min; i <= max; i++) toBeLoaded.push_back(i);

	//iterate thru loaded segments and remove them from toBeLoaded list, or from game when they are out of region
	for(core::list<TrackSegment*>::ConstIterator segment_iterator = segments.begin(); segment_iterator != segments.end(); segment_iterator++)
	{
		int id = (*segment_iterator)->id;

		if( id >= min && id <= max)
		{
			toBeLoaded.remove(id);
		}else
		{
			//inform listener that segment is about to be unloaded
			//todo remove it from list
		}
	}

	//load all loadables
	for(std::list<int>::const_iterator iterator = toBeLoaded.begin(); iterator != toBeLoaded.end(); iterator++)
	{
		//add point at the end
		TrackSegment* segment = track->getSegment( (*iterator) ) ;
		segments.push_back( segment );

		core::list<btRigidBody*>* bodies = segment->getTrackBodies();

		//load all bodies from segment into engine
		for(core::list<btRigidBody*>::ConstIterator iterator = bodies->begin(); iterator != bodies->end(); iterator++)
		{
			dynamicsWorld->addRigidBody((*iterator));
		}

		/*
		//inform listener that segment is loaded
		if(listener != NULL) listener->afterSegmentLoaded(segment);
		*/
	}
	
}


void Engine::loadSegment(ObjectRecord* record)
{
	assert( record != 0 );
	assert( record->type == EOT_SEGMENT );

	for(core::list<ObjectRecord*>::ConstIterator it = record->children.begin(); it != record->children.end();it++)
	{
		ObjectRecord* object = (*it);
		
		switch( object->type ){
			case EOT_BOX:
				{
				//memmory leak
				btCollisionShape* shape = object->createShape();
				assert(shape != 0); 
				//for monitoring
				EngineBodyState* motionState = new  EngineBodyState(this, 0, btTransform(btQuaternion(0,0,0,1),object->position));
				//physics stuff
				btVector3 inertia(0,0,0);
				btScalar mass = object->mass;
				shape->calculateLocalInertia(mass,inertia);

				btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,shape,inertia);
				//construct
				btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);
				//loopback link
				motionState->setBody(rigidBody);
				dynamicsWorld->addRigidBody(rigidBody);
				notifyShapeNew(shape, object, mass ? 0 : rigidBody);

				} break; //end EOT_BOX
			default:
				assert(false);
		} //end switch
	} //end iterating children

}

core::list<TrackSegment*>* Engine::getSegments(){
	return &segments;
}

void Engine::notifyShapeNew(btCollisionShape* shape, ObjectRecord* record, btRigidBody* body)
{
	ENGINE_NOTIFY(onShapeNew(shape, record));

	//static object don't raise ShapeUpdate, so we force the first one upon the creation so the node can be placed to appropriate positon
	if(body != 0)
	{
		btTransform t;
		body->getMotionState()->getWorldTransform(t) ;
		ENGINE_NOTIFY(onShapeUpdate(shape, t));	
	}

}


void Engine::notifyShapeUpdate(btCollisionShape* shape, const btTransform &transform)
{
	ENGINE_NOTIFY(onShapeUpdate(shape, transform));	
}

/*
void Engine::notifyVehicleUpdate(const btTransform){
	
}
*/


void Engine::addObserver(EngineObserver* o)
{
	observers.push_back(o);
}


void Engine::removeObserver(EngineObserver* o)
{
	//todo:
}
