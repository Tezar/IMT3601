#include <assert.h>
#include <windows.h>
#include <stdio.h>
#include <functional>
#include "Engine.hpp"



Engine::Engine(void)
{
		numVehicles = 0;

		track = new TrackGenerator(69696969);	//seed with randomly picked number...
		

		averagePosition.set(0,0,0);
}


Engine::~Engine(void)
{
	delete track;
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


void Engine::reset()
{
	//add point at the end
	segments.push_back( track->getSegment(0) );

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

}


inline void Engine::recalculatePosition()
{
	static float posX;
	static float posZ;

	posX = 0;
	posZ = 0;

	for (int nVehicle = 0; nVehicle < numVehicles; nVehicle++){
		Vehicle* v = vehicles[nVehicle];
		posX += v->position.X;
		posZ += v->position.Z;
	}
	averagePosition.set(posX/numVehicles, 0, posZ/numVehicles);
}

core::list<TrackSegment*>* Engine::getSegments(){
	return &segments;
}