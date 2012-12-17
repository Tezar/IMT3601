#include <Singleton.hpp>
#include <Engine.hpp>
#include "AI.hpp"

using namespace irr;

ArtificialIntelligence::ArtificialIntelligence(Vehicle * vehicleReference, AudioManagerClass * soundManager, Engine * e)
{
	i = 0;

	engine = e;
	AIvehicle = vehicleReference;
	sounds = soundManager;

	waypoints = engine->getWaypoints();

	AssignWaypoints();

	AIvehicle->force = force_forward;
}

void ArtificialIntelligence::AssignWaypoints()
{
	if(i >= waypoints.size()-1)
		i = 0;
	
	if(i == 0)
	{
		NextWaypoint = waypoints[i];
		i++;
	}
	else
	{
		NextWaypoint = waypoints[i];
		LastWaypointVisited = waypoints[i-1];
		i++;
	}
}

void ArtificialIntelligence::GoToNextWaypoint()
{
	
	//AIvehicle->force = force_forward;
}

void ArtificialIntelligence::TraverseWaypoints()
{

	if(i <= waypoints.size())
	{
		if((distanceToNextWaypoint_x <= 0.4) && (distanceToNextWaypoint_x >= -0.4) &&
		   (distanceToNextWaypoint_y <= 0.4) && (distanceToNextWaypoint_y >= +0.4))
		{
			AssignWaypoints();
		}

//		btVector3 waypoint = waypoints[i];
		currentPosition_x = AIvehicle->position.X;
		currentPosition_y = AIvehicle->position.Y;
		distanceToNextWaypoint_x = currentPosition_x - NextWaypoint.x();
		distanceToNextWaypoint_y = currentPosition_y - NextWaypoint.y();

		if((previousPosition_x-NextWaypoint.x()) < distanceToNextWaypoint_x)
		{
			if((previousPosition_y-NextWaypoint.y()) < distanceToNextWaypoint_y)
				AIvehicle->turning = turning_right;
			else
				AIvehicle->turning = turning_none;
		}
		
		else if((previousPosition_y-NextWaypoint.y()) < distanceToNextWaypoint_y)
		{
			if((previousPosition_x-NextWaypoint.x()) < distanceToNextWaypoint_x)
				AIvehicle->turning = turning_left;
			else
				AIvehicle->turning = turning_none;
		}
		
		
		previousPosition_x = currentPosition_x;
		previousPosition_y = currentPosition_y;
	}
	else
		AIvehicle->breaking = true;
}