#pragma once


#include <irrlicht.h>
#include <Engine.hpp>
#include "Vehicle.hpp"
#include "AudioManager.hpp"

using namespace irr;

class ArtificialIntelligence
{
protected:
	int currentWaypointNr;
	float direction;
	float vehicleRotation;
	float currentPosition_x;
	float currentPosition_z;
//	float previousPosition_x;
//	float previousPosition_z;
	float distanceToNextWaypoint_x;
	float distanceToNextWaypoint_z;
//	float previousDistanceToNextWaypoint_x;
//	float previousDistanceToNextWaypoint_z;

	core::array<btVector3> waypoints;
//	btVector3 LastWaypointVisited;
	btVector3 NextWaypoint;

	Vehicle * AIvehicle;
	AudioManagerClass * sounds;
	Engine * engine;




public:
	ArtificialIntelligence(Vehicle * vehicleReference, AudioManagerClass * soundManager, Engine * e);

//	void AssignWaypoints();
//	void GoToNextWaypoint();
	void TraverseWaypoints();
};