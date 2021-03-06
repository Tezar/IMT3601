#pragma once
#include <irrlicht.h>
#include "btBulletDynamicsCommon.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;



enum vehicle_force_t
	{
		force_none, 
		force_forward,
		force_backward
	};

enum vehicle_turning_t
	{
		turning_none, 
		turning_left,
		turning_right, 
	};


class Vehicle
{
protected:
	int maxForce;
	float steering;

	float steeringIncrement;
	float steeringClamp;
	
	bool alive;

public:
	Vehicle(void);
	~Vehicle(void);

	int nextWaypoint;
	int score;
	
	bool leadVehicle;

	btRaycastVehicle* pointer;
	
	btRigidBody* chassis;

	//list of powered bodies
	core::list<btRigidBody*> powered;

	//list of turnable bodies
	core::list<btRigidBody*> turnable;

	void kill();
	void revive();
	bool isAlive(){ return alive; };
	bool isLead(){ return leadVehicle; };

	void updatePhysics();

	core::array<btCollisionShape*> shapes;

	void addShape(btCollisionShape*);

	//currently applied force
	vehicle_force_t force;
	
	//currently applied turning
	vehicle_turning_t turning;

	bool breaking;

	vector3df position;


	







};

