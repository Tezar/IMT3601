#pragma once


#include <irrlicht.h>
#include <Engine.hpp>
#include "Vehicle.hpp"
#include "AudioManager.hpp"

using namespace irr;

class ArtificialIntelligence
{
private:
	int i;
	float currentPosition_x;
	float currentPosition_y;
	float previousPosition_x;
	float previousPosition_y;
	float distanceToNextWaypoint_x;
	float distanceToNextWaypoint_y;

	core::array<btVector3> waypoints;
	btVector3 LastWaypointVisited;
	btVector3 NextWaypoint;

	Vehicle * AIvehicle;
	AudioManagerClass * sounds;
	Engine * engine;




public:
	ArtificialIntelligence(Vehicle * vehicleReference, AudioManagerClass * soundManager, Engine * e);

	void AssignWaypoints();
	void GoToNextWaypoint();
	void TraverseWaypoints();
};