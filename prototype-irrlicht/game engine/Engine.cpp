#include <assert.h>
#include <windows.h>
#include <stdio.h>
#include <functional>
#include "Engine.hpp"
#include "EngineBodyState.hpp"

Engine::Engine(void)
{
	numVehicles = 0;

	leadproduct = 1337;
	leadNextWaypoint = 1337;

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

	//todo: delete bodies, shapes, motionstates...

}


Vehicle* Engine::addVehicle(ObjectRecord* record)
{
	assert( record != 0);
	assert( record->type == EOT_VEHICLE );
	assert(numVehicles < MAX_VEHICLES);


	btScalar centerOfMassOffset = 0.5f;


	Vehicle * vehicle = new Vehicle();

	int currentVehicle = numVehicles++;
	vehicles[currentVehicle] = vehicle;

	//tuning 
	btRaycastVehicle::btVehicleTuning vehicleTuning;
	vehicleTuning.m_maxSuspensionForce = 1000;
	

	btRaycastVehicle* rayVehicle = 0;

	for(core::list<ObjectRecord*>::ConstIterator it = record->children.begin(); it != record->children.end();it++)
	{
		ObjectRecord* object = (*it);
		
		switch( object->type ){
		case EOT_CHASSIS:{
			
			//we shape our world
			btCollisionShape* shape = object->createShape();
			assert(shape != 0);


			btCompoundShape* compound = new btCompoundShape();
			btTransform localTrans;
			localTrans.setIdentity();
			//localTrans effectively shifts the center of mass with respect to the chassis
			localTrans.setOrigin(btVector3(0,centerOfMassOffset,0));

			compound->addChildShape(localTrans,shape);



			//for reporting back the position
			//special state, it will update wheel positions and notify liteners about them as well
			EngineBodyState* motionState = new  EngineVehicleState(this, vehicle, btTransform(btQuaternion(0,0,0,1),object->position));
			
			//physics stuff
			btScalar mass = 1;
			btVector3 inertia(0,0,0);
			shape->calculateLocalInertia(mass,inertia);

			//our construction info
			btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,compound,inertia);
			//construct
			btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);
			//loopback link
			motionState->setBody(rigidBody);

			//add our body to the world and deactivate deactivation
			rigidBody->setActivationState(DISABLE_DEACTIVATION);
			dynamicsWorld->addRigidBody(rigidBody);

			
			//store reference for our chassis inside the vehicle
			vehicle->chassis = rigidBody; 

			//ve create our vehicle from our body
			btVehicleRaycaster* vehicleRayCaster = new btDefaultVehicleRaycaster(dynamicsWorld);
			rayVehicle = new btRaycastVehicle(vehicleTuning,rigidBody,vehicleRayCaster);

			//pointer to our vehicle
			vehicle->pointer = rayVehicle;


			//now, this is crucial, rayVehicle is form of constrain and needs to be added to the world
			dynamicsWorld->addVehicle(rayVehicle);

			//all vehicles starts as not the lead car
			vehicle->leadVehicle = false;

			//is this necessary?
			rayVehicle->setCoordinateSystem(0,1,2);

			notifyShapeNew(compound, object );
			
			}
			break;
		case EOT_WHEEL:
			{

				//we shape our world, and it is for our eyes only
				btCollisionShape* shape = object->createShape();
				assert(shape != 0);

				vehicle->addShape(shape);


				//when we want to add wheels, we have to have defined vehicle
				assert(rayVehicle != 0); 
				//object->position
				btWheelInfo& wheel =  rayVehicle->addWheel( btVector3(object->position.x(),centerOfMassOffset, object->position.z() ),	//position of wheel
																	  btVector3(0,-1,0),	//orientation of wheel
																	  btVector3 (-1,0,0),	//orientation  axes
																	  object->position.y(),	//suspension length 
																	  object->shapeDimensions.x(),	//wheel radius
																	  vehicleTuning,	//tuning params
																	  false // isFrontWheel
																	  );

				float	gVehicleSteering = 0.f;
				float	steeringIncrement = 0.04f;
				float	steeringClamp = 0.3f;
				float	wheelRadius = 5.f;
				float	wheelWidth = 4.f;
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
	while(toDo > ENGINE_STEP)
	{
		i++;
		dynamicsWorld->stepSimulation(ENGINE_STEP/1000.0,10);
		toDo -= ENGINE_STEP;

		for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++)
		{
			vehicles[nVehicle]->updatePhysics();
		}
			
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

	btVector3 pos;
	pos.setZero();
	btTransform trans;

	btScalar offset = -numVehicles*0.5;
	
	for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
		Vehicle* v = vehicles[nVehicle];
		
		trans.setIdentity();
		pos.setX(offset+2*nVehicle);
		trans.setOrigin(pos);
		v->chassis->setWorldTransform(trans);
	}

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

		v->position.set(pos.x(), pos.y(), pos.z());


		checkWaypoint(v);

	}
	averagePosition.set(posX/numVehicles, posY/numVehicles, posZ/numVehicles);
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
			case EOT_WAYPOINT:
				waypoints.push_back( object->position );

				break;
			default:
				//unknown
				assert(false);
		} //end switch
	} //end iterating children

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

void Engine::checkWaypoint(Vehicle* vehicle)
{
	btVector3 vector = waypoints[vehicle->nextWaypoint];
	// n
	btVector3 nextVector = waypoints[(vehicle->nextWaypoint + 1) % waypoints.size()];
	// n+1
	vector = nextVector - vector;
	// First vector
	btVector3 pos = btVector3(vehicle->position.X, vehicle->position.Y, vehicle->position.Z);

	float product = vector.dot(pos - waypoints[vehicle->nextWaypoint]);
	// positiv = before, negative = behind

	if(product > 0)
		vehicle->nextWaypoint = (vehicle->nextWaypoint + 1) % waypoints.size();

	//if its the first vehicle of the race then it sets the glabal leadNextWaypoint
	//to the first waypoint
	if(leadNextWaypoint == 1337 && leadproduct == 1337){
		leadNextWaypoint = vehicle->nextWaypoint;
		leadproduct = product;
	}

	if(vehicle->nextWaypoint == leadNextWaypoint && 
		product > leadproduct)
		vehicle->leadVehicle = true; // wrong way to do this, if someone loses the lead they ares til marked as lead

	//todo if procuct and nextwaypoint is to far behind, kill the car.
}