#include "Vehicle.hpp"




Vehicle::Vehicle(void): alive(true)
{
	force = force_none;
	turning = turning_none;

	maxForce= 1;

	nextWaypoint = 0;

	steering = 0;
	steeringIncrement = 0.04f;
	steeringClamp = 0.3f;

	breaking = false;
	position.set(0,0,0);

}


Vehicle::~Vehicle(void)
{
	//todo:delete all shapes
}


void Vehicle::addShape(btCollisionShape* shape)
{
	shapes.push_back(shape);
}


void Vehicle::kill()
{
	force = force_none;
	turning = turning_none;
	updatePhysics();
	alive = false;
}

void Vehicle::revive()
{
	alive  = true;
}

void Vehicle::updatePhysics()
{
		
	if(!alive) return;

	int engineForce = 0;

	switch(force)
	{
		case force_forward:  engineForce = maxForce; break;
		case force_backward:  engineForce = -maxForce; break;
	}
		
	int breakForce = breaking ?  maxForce : 0;

	int wheelIndex = 0;
	pointer->applyEngineForce(engineForce, 0);
	pointer->applyEngineForce(engineForce, 1);


	pointer->setBrake(breakForce,2);
	pointer->setBrake(breakForce,3);




	switch(turning)
	{
		case turning_right:
			steering += steeringIncrement;
			if(steering > steeringClamp) steering = steeringClamp;
		break;
		case turning_left:
			steering -= steeringIncrement;
			if(steering < -steeringClamp) steering = -steeringClamp;
		break;
		case turning_none: //relaxation
			if(abs(steering) < (steeringIncrement*0.5)  ) break;	//skip if it's too small
			//go for zero
			steering += ((steering < 0) ? steeringIncrement : -steeringIncrement) *0.5;
	}

	wheelIndex = 0;
	pointer->setSteeringValue(steering,wheelIndex);
	wheelIndex = 1;
	pointer->setSteeringValue(steering,wheelIndex);

}