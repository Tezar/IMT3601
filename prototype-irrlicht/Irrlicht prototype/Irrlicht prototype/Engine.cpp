#include <assert.h>
#include <stdio.h>
#include "Engine.hpp"



Engine::Engine(void)
{
		numVehicles = 0;
}


Engine::~Engine(void)
{
}


void Engine::addVehicle(Vehicle * vehicle)
{
	assert(numVehicles < MAX_VEHICLES);

	vehicles[numVehicles] = vehicle;
	numVehicles++;
}


int Engine::step(int toDo)
{
	//todo:physics
	//todo:collisions

	while(toDo > ENGINE_STEP){
	

		//simulation!
		for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
			//todo: change to reflect behaviour, maybe implement it as strategy pattern to please Simon ? :-)
			Vehicle* v = vehicles[nVehicle];
			if(v->force == force_forward){
				v->position.X += f32(0.0001);
			}
		}

	
		toDo -= ENGINE_STEP;
	}



	return toDo;
}

void Engine::reset()
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
	for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
		vehicles[nVehicle]->position.set(nVehicle*5.0,0.0,0.0);
	}

}
