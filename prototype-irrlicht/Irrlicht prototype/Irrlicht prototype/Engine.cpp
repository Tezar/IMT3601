#include <assert.h>
#include <windows.h>
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
	int i = 0;
	while(toDo > ENGINE_STEP){
		i++;

		//simulation!
		for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
			
			//todo: change to reflect behaviour, maybe implement it as strategy pattern to please Simon ? :-)
			Vehicle* v = vehicles[nVehicle];
			if(v->force == force_forward){
				v->position.X += f32(0.01);
			}
		}
		toDo -= ENGINE_STEP;
	}
	i;

	recalculatePosition();

	return toDo;
}


std::list<TrackPoint*> Engine::getTrack(){
	return trackPoints;
}


void Engine::reset()
{
	for(std::list<TrackPoint*>::const_iterator iterator = trackPoints.begin(); iterator != trackPoints.end();  iterator++)
	{
		delete (*iterator);	//delete trackpoint to prevent memory leaks
	}

	trackPoints.clear();



	//add point at the end
	trackPoints.splice( trackPoints.end() , track->getTrackPoints(0,5) );


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