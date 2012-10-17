#include <assert.h>
#include <stdio.h>
#include "Engine.hpp"



Engine::Engine(void)
{
		numVehicles = 0;

		track = new TrackGenerator(69);	//seed with randomly picked number...
		
		averagePosition.set(0,0,0);
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


	recalculatePosition();

	return toDo;
}



void Engine::reset()
{
	for(list<TrackPoint*>::ConstIterator iterator = trackPoints.begin(); iterator != trackPoints.end();  iterator++)
	{
		delete (*iterator);	//delete trackpoint to prevent memory leaks
	}

	trackPoints.clear();


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

}


inline void Engine::recalculatePosition()
{
	static float posX;
	static float posY;

	posX = 0;
	posY = 0;

	for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
		Vehicle* v = vehicles[nVehicle];
		posX += v->position.X;
		posY += v->position.Y;
	}
	averagePosition.set(posX/numVehicles, posY/numVehicles,0);
}