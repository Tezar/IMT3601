#pragma once
#include <irrlicht.h>
using namespace irr;
using namespace core;



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

public:
	//currently applied force
	vehicle_force_t force;
	
	//currently applied turning
	vehicle_turning_t turning;

	vector3df position;

	Vehicle(void);
	~Vehicle(void);
};

