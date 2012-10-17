#pragma once
#include "Vehicle.hpp"
#include "TrackUtil.hpp"
#include "TrackGenerator.hpp"

#define MAX_VEHICLES 4

//!if you change this value it will mess up all unscaled physical constrains!
#define ENGINE_STEP 10


class Engine
{
	
public:
	Vehicle* vehicles[MAX_VEHICLES];
	TrackGenerator * track;

	int numVehicles;

	Engine(void);
	~Engine(void);

	/* averaged position of all vehicles for use by camera and track generato */
	vector3df averagePosition;
	

	void addVehicle(Vehicle*);
	
	/** consumes time to make simulation, returns any leftovers 
		@par int time to be consumed
		@return int time not consumed
	*/
	int step(int);

	/** resets state of engine to initial conditions */
	void reset();


	std::list<TrackPoint*> getTrack();

protected:
	/** averages position of vehicles and updates member variable */
	inline void recalculatePosition();

	std::list<TrackPoint*> trackPoints;

};

