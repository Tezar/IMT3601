#pragma once
#include "Vehicle.hpp"

#define MAX_VEHICLES 4

//!if you change this value it will mess up all unscaled physical constrains!
#define ENGINE_STEP 10


class Engine
{
	
public:
	Vehicle* vehicles[MAX_VEHICLES];
	int numVehicles;

	Engine(void);
	~Engine(void);


	void addVehicle(Vehicle*);
	
	/** consumes time to make simulation, returns any leftovers 
		@par int time to be consumed
		@return int time not consumed
	*/
	int step(int);

	/** resets state of engine to initial conditions */
	void reset();


};
