#pragma once
#include <assert.h>
#include <windows.h>
#include <stdio.h>
#include <functional>
#include "Engine.hpp"
#include "EngineBodyState.hpp"
#include <cmath>

using namespace std;
using namespace irr;

Engine::Engine(void)
{
	//some values start points
	numVehicles = 0;
	averagePosition.set(0,0,0);
	main_rot_angle = 0;
	leadproduct = 1337;
	dead_vehicles = 0;

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

	vehicle->score = 5;

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

	return toDo;
}


void Engine::reset(btVector3* spawnPoint, btVector3* nextWaypoint)
{
	//todo:
	/*	placeVehicles( point 1 , point 2)
	
			point2
				    |
					|
				*  *  *  *
			point1
			* = vehicle
	*/
	//make the translocateor
	btTransform trans;

	//variables needed for the matchs
	float angle = 0;
	btVector3* basepoint1 = &waypoints[0];
	btVector3* basepoint2 = &waypoints[1];
	
	if(spawnPoint != nextWaypoint){
		btVector3 vector = btVector3(nextWaypoint->x(),nextWaypoint->y(),nextWaypoint->z()) - btVector3(spawnPoint->x(),spawnPoint->y(),spawnPoint->z());
		btVector3 baseVector = btVector3(basepoint2->x(),basepoint2->y(),basepoint2->z()) - btVector3(basepoint1->x(),basepoint1->y(),basepoint1->z());

		vector.normalize();
		baseVector.normalize();
		//calculates the angle i need to turn the cars, so they are facing the net waypoint
		//by using the angle the point is from the base line
		float dot = vector.dot(baseVector);
		angle = acos(dot);
			
		/*     vector   /
					   /)angle
					  / _) _ baseVector
		*/
	}

	//spacing made so cars spawn next to each other on the given vector
	float spacing = 2;
	btScalar offset = -numVehicles*0.5*spacing;


	for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
		Vehicle* v = vehicles[nVehicle];
		//sets the new spawn point and rotates each car
		trans.setIdentity();

		if(spawnPoint == nextWaypoint){
			trans.setOrigin(btVector3(spawnPoint->x()+offset+spacing*nVehicle,spawnPoint->y(),spawnPoint->z()));
		}else{
			if(angle > 2){
				//when the waypoints is on the other side of the base vector, they need to be turned
				trans.setRotation(btQuaternion(btVector3(0, 1, 0), (-angle)));
			}else{
				trans.setRotation(btQuaternion(btVector3(0, 1, 0), (angle)));
			}
			trans.setOrigin(btVector3(spawnPoint->x()+offset+spacing*nVehicle,spawnPoint->y(),spawnPoint->z()));
		}
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

		if(!v->isAlive()) continue;

		btTransform trans;

		v->chassis->getMotionState()->getWorldTransform(trans);
		
		btVector3 pos = trans.getOrigin();

		posX += pos.x();
		posY += pos.y();
		posZ += pos.z();

		v->position.set(pos.x(), pos.y(), pos.z());


		gameplayCheck(v);

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

void Engine::addObserver(EngineObserver* o)
{
	observers.push_back(o);
}


void Engine::removeObserver(EngineObserver* o)
{
	//todo:
}

void Engine::gameplayCheck(Vehicle* vehicle)
{
	//normaly this will be atleast 2 more induvidual functions for
	//a easyer look, but they mostly calculate and use the same variable
	//so was easyer in testing just to have all under one

	//calculates the vector between the Next waypoint and the one after that
	//then finds the vector that is perpendecular to that vector
	//then using the cars posision finds if the car is
	//infront or behind this vector (its in the waypoint)

	//we do it this way so that you can drive way on the left/right side of the point
	//and take short cuts inside the game
	btVector3 vector = waypoints[vehicle->nextWaypoint];
	btVector3 nextVector = waypoints[(vehicle->nextWaypoint + 1) % waypoints.size()];
	vector = nextVector - vector;
	btVector3 pos = btVector3(vehicle->position.X, vehicle->position.Y, vehicle->position.Z);

	float product = vector.dot(pos - waypoints[vehicle->nextWaypoint]);

	//if its the first vehicle of the race then it sets the glabal leadcar
	//to current leader. we use a global so it can be accsesed inside all our functions
	//no matter what car we are curently working on
	if(leadproduct == 1337 && product != 0){
		vehicle->leadVehicle = true;
		leadproduct = product;
		leadvector = pos - waypoints[vehicle->nextWaypoint];
		leadcar = vehicle;
	}

	// positiv = after, negative = before
	if(product > 0)
	{
		//waypoint pased, so it gets its waypoint updated
		vehicle->nextWaypoint = (vehicle->nextWaypoint + 1) % waypoints.size();
	}

	if((vehicle->nextWaypoint == leadcar->nextWaypoint && product > leadproduct) 
		|| (vehicle->nextWaypoint > leadcar->nextWaypoint)
		|| (vehicle->nextWaypoint == 0 && leadcar->nextWaypoint == (waypoints.size() - 1)))
	{
		//checks to see if this vehicle passed the current leadcar
		vehicle->leadVehicle = true;
		leadproduct = product;
		leadcar = vehicle;
	}else{
		vehicle->leadVehicle = false;
		//if this falls to far behind, its killed
		if(vehicle->position.getDistanceFrom(leadcar->position) > 10){
			vehicle->kill();
			dead_vehicles++;
			//when all vehicles other than the lead are dead
			//points are given out
			if(dead_vehicles == 1) //make 1 if you want to test with just 2 cars
								   //normaly = 3
				givePoint();
				dead_vehicles = 0;
		}
	}

}

void Engine::givePoint()
{
	//point of the game is to get too 10 points
	for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
		Vehicle* v = vehicles[nVehicle];
		//all cars gets checked, if this is dead, it loses a point
		if(!v->isAlive()){
			if(v->score >= 1){v->score = v->score - 1;}else{v->score = 0;}
			v->revive();
			v->nextWaypoint = leadcar->nextWaypoint;
		}else{
			//if its stil alive, it most be the leader and so it gets a point
			v->score = v->score + 1;
			v->nextWaypoint = leadcar->nextWaypoint;
			if(v->score >= 10)
				//if the current leader hitts 10 points, the game is over
				game_over();
		}
	}
	//resets all cars back to the last passed waypoint of the leading car
	if(leadcar->nextWaypoint == 0){
		reset(&waypoints[waypoints.size() - 1], &waypoints[0]);
	}else{
		reset(&waypoints[leadcar->nextWaypoint - 1], &waypoints[leadcar->nextWaypoint]);
	}
}

void Engine::game_over()
{
	//blowup;
}