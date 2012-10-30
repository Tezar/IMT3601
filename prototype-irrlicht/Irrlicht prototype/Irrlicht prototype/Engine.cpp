#include <assert.h>
#include <windows.h>
#include <stdio.h>
#include <functional>
#include "Engine.hpp"


class EngineBodyState: public btMotionState {
public:
    EngineBodyState(Engine * e, irr::u32 _id, const btTransform &initialpos) {
        engine = e;
		id = _id;
        mPos1 = initialpos;
    }

    virtual ~EngineBodyState() {
    }

	virtual void getWorldTransform(btTransform &worldTrans) const {
        worldTrans = mPos1;
    }

    virtual void setWorldTransform(const btTransform &worldTrans) {
		if(engine->listener == NULL)
				return; // we silently return as there is no handler to notify

		engine->listener->onBodyMovement(id, &worldTrans);
		/*
        btQuaternion rot = worldTrans.getRotation();
        mVisibleobj->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
        btVector3 pos = worldTrans.getOrigin();
        mVisibleobj->setPosition(pos.x(), pos.y(), pos.z());
		*/
    }

protected:
	irr::u32 id;
    Engine* engine;
    btTransform mPos1;
};


class EngineVehicleState: public btMotionState {
public:
    EngineVehicleState(Engine * e,irr::u32 _id, Vehicle* _vehicle, const btTransform &initialpos) {
        engine = e;
		vehicle = _vehicle;
		id = _id;
        mPos1 = initialpos;
    }

    virtual ~EngineVehicleState() {
    }

	virtual void getWorldTransform(btTransform &worldTrans) const {
        worldTrans = mPos1;
    }

    virtual void setWorldTransform(const btTransform &worldTrans) {
		if(engine->listener == NULL)
				return; // we silently return as there is no handler to notify

		
		btVector3 pos = worldTrans.getOrigin();
		vehicle->position.set(pos.x(), pos.y(), pos.z());

		engine->listener->onVehicleMovement(id, vehicle );
    }

protected:
	Vehicle* vehicle;
	irr::u32 id;
    Engine* engine;
    btTransform mPos1;
};




Engine::Engine(void)
{
	numVehicles = 0;

	track = new TrackGenerator(69696969);	//seed with randomly picked number...
	averagePosition.set(0,0,0);

	listener = NULL;


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


Vehicle* Engine::addVehicle(Vehicle * vehicle)
{
	assert(numVehicles < MAX_VEHICLES);
	int currentVehicle = numVehicles++;
	vehicles[currentVehicle] = vehicle;


	//memmory leak
    btCollisionShape* fallShape = new btSphereShape(1);

	//MAKE_VEHICLE_ID(currentVehicle)
	btMotionState* fallMotionState = new  EngineVehicleState(this, currentVehicle, vehicle, btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
    btScalar mass = 1+10*currentVehicle;
    btVector3 fallInertia(0,0,0);
    fallShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);

	bodies_vehicles[currentVehicle] = fallRigidBody;

	dynamicsWorld->addRigidBody(fallRigidBody);

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
		/*
		//simulation!
		for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
			
			
			//todo: change to reflect behaviour, maybe implement it as strategy pattern to please Simon ? :-)
			Vehicle* v = vehicles[nVehicle];
			if(v->force == force_forward){
				v->position.X += f32(0.00);
				v->position.Z += f32(0.01);
			}
		}*/
		toDo -= ENGINE_STEP;
	}
	

	recalculatePosition();

	return toDo;
}


void Engine::reset()
{
	//add point at the end
	segments.push_back( track->getSegment(0) );
	segments.push_back( track->getSegment(1) );
	segments.push_back( track->getSegment(2) );
	segments.push_back( track->getSegment(3) );

	//trackPoints.splice(trackPoints.end(), track->getTrackPoints(1,5));
	//trackPoints.splice(trackPoints.end(), track->getTrackPoints(2,5));
	//todo:
	/*	placeVehicles( point 1 , point 2)
	
			point2
					|
					|
				*  *  *  *
			point1
			* = vehicle
	*/
	for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++)
	{
		vehicles[nVehicle]->position.set( nVehicle*5.0 ,0.0 ,0.0 );
	}


	// Build the broadphase
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
 
    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
    // The actual physics solver
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
 
    // The world.
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));
 
    // Do_everything_else_here
 
 
    // Clean up behind ourselves like good little programmers
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;

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
		posX += v->position.X;
		posY += v->position.Y;
		posZ += v->position.Z;
	}
	averagePosition.set(posX/numVehicles, posY/numVehicles, posZ/numVehicles);
}

core::list<TrackSegment*>* Engine::getSegments(){
	return &segments;
}