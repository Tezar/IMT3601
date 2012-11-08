#pragma once
#include <irrlicht.h>
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
	scene::IMeshSceneNode* vehicleNode;

public:
	//currently applied force
	vehicle_force_t force;
	
	//currently applied turning
	vehicle_turning_t turning;

	vector3df position;

	scene::IMeshSceneNode* injectNode(IrrlichtDevice* device=0);
	

	Vehicle(void);
	~Vehicle(void);
};

