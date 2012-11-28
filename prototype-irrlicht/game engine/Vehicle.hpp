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


public:
	Vehicle(void);
	~Vehicle(void);

	
	btRigidBody* chassis;

	//list of powered bodies
	core::list<btRigidBody*> powered;

	//list of turnable bodies
	core::list<btRigidBody*> turnable;


	core::list<btCollisionShape*> shapes;

	void addShape(btCollisionShape*);

	//currently applied force
	vehicle_force_t force;
	
	//currently applied turning
	vehicle_turning_t turning;

	vector3df position;


	







};

