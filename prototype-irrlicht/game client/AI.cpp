#include <Singleton.hpp>
#include <Engine.hpp>
#include "AI.hpp"

using namespace irr;

ArtificialIntelligence::ArtificialIntelligence(Vehicle * vehicleReference, AudioManagerClass * soundManager, Engine * e)
{
	currentWaypointNr = 0;

	engine = e;
	AIvehicle = vehicleReference;
	sounds = soundManager;

	waypoints = engine->getWaypoints();

	AssignWaypoints();

	AIvehicle->force = force_forward;
}

void ArtificialIntelligence::AssignWaypoints()
{
	if(currentWaypointNr >= waypoints.size()-1)
		currentWaypointNr = 0;
	
	if(currentWaypointNr == 0)
	{
		NextWaypoint = waypoints[currentWaypointNr];
		currentWaypointNr++;
	}
	else
	{
		NextWaypoint = waypoints[currentWaypointNr];
		LastWaypointVisited = waypoints[currentWaypointNr-1];
		currentWaypointNr++;
	}
}

void ArtificialIntelligence::GoToNextWaypoint()
{
	
	//AIvehicle->force = force_forward;
}

void ArtificialIntelligence::TraverseWaypoints()
{

	if(currentWaypointNr <= waypoints.size())
	{
		if((distanceToNextWaypoint_x <= 0.1f) && (distanceToNextWaypoint_x >= -0.1f) &&
		   (distanceToNextWaypoint_y <= 0.1f) && (distanceToNextWaypoint_y >= -0.1f))
		{
			AssignWaypoints();
		}


		currentPosition_x = AIvehicle->position.X;
		currentPosition_y = AIvehicle->position.Y;
		distanceToNextWaypoint_x = currentPosition_x - NextWaypoint.x();
		distanceToNextWaypoint_y = currentPosition_y - NextWaypoint.y();
		previousDistanceToNextWaypoint_x = previousPosition_x - NextWaypoint.x();
		previousDistanceToNextWaypoint_y = previousPosition_y - NextWaypoint.y();


		if(previousDistanceToNextWaypoint_x < 0)
		{
			if(previousDistanceToNextWaypoint_y < 0)
			{
				if(previousDistanceToNextWaypoint_y < distanceToNextWaypoint_y)
					AIvehicle->turning = turning_left;
				else
					AIvehicle->turning = turning_none;
			}
			else if(previousDistanceToNextWaypoint_y > 0)
			{
				if(previousDistanceToNextWaypoint_y < distanceToNextWaypoint_y)
					AIvehicle->turning = turning_right;
				else
					AIvehicle->turning = turning_none;
			}
			/*if(previousDistanceToNextWaypoint_x < distanceToNextWaypoint_x)
				AIvehicle->turning = turning_left;
			else
				AIvehicle->turning = turning_none;*/
		}
		else if(previousDistanceToNextWaypoint_x > 0)
		{
			if(previousDistanceToNextWaypoint_y < 0)
			{
				if(previousDistanceToNextWaypoint_y < distanceToNextWaypoint_y)
					AIvehicle->turning = turning_left;
				else
					AIvehicle->turning = turning_none;
			}
			else if(previousDistanceToNextWaypoint_y > 0)
			{
				if(previousDistanceToNextWaypoint_y < distanceToNextWaypoint_y)
					AIvehicle->turning = turning_right;
				else
					AIvehicle->turning = turning_none;
			}
			/*if(previousDistanceToNextWaypoint_x < distanceToNextWaypoint_x)
				AIvehicle->turning = turning_right;
			else
				AIvehicle->turning = turning_none;*/
		}


//		if(previousDistanceToNextWaypoint_y < 0)
//		{
//			if(previousDistanceToNextWaypoint_y < distanceToNextWaypoint_y)
//				AIvehicle->turning = turning_left;
//			else
//				AIvehicle->turning = turning_none;
//		}
//		else if(previousDistanceToNextWaypoint_y > 0)
//		{
//			if(previousDistanceToNextWaypoint_y < distanceToNextWaypoint_y)
//				AIvehicle->turning = turning_right;
//			else
//				AIvehicle->turning = turning_none;
//		}

//		if((previousPosition_x-NextWaypoint.x()) < distanceToNextWaypoint_x)
//		{
//			if((previousPosition_y-NextWaypoint.y()) < distanceToNextWaypoint_y)
//				AIvehicle->turning = turning_left;
//			else if((previousPosition_y-NextWaypoint.y()) > distanceToNextWaypoint_y)
//				AIvehicle->turning = turning_right;
//			/*else
//				AIvehicle->turning = turning_right;*/
//		}
//		//else
//		//	AIvehicle->turning = turning_none;
//
//		else if((previousPosition_y-NextWaypoint.y()) < distanceToNextWaypoint_y)
//		{
//			if((previousPosition_x-NextWaypoint.x()) < distanceToNextWaypoint_x)
//				AIvehicle->turning = turning_right;
//			else if((previousPosition_x-NextWaypoint.x()) > distanceToNextWaypoint_x)
//				AIvehicle->turning = turning_left;
//			/*else
//				AIvehicle->turning = turning_left;*/
//		}
//		else
//			AIvehicle->turning = turning_none;

		
		
//		if((previousPosition_y-NextWaypoint.y()) < distanceToNextWaypoint_y ||
//		   (previousPosition_y-NextWaypoint.y()) > distanceToNextWaypoint_y)
//		{
//			if((previousPosition_x-NextWaypoint.x()) < distanceToNextWaypoint_x)
//				AIvehicle->turning = turning_left;
//			else if((previousPosition_x-NextWaypoint.x()) > distanceToNextWaypoint_x)
//				AIvehicle->turning = turning_right;
//			else
//				AIvehicle->turning = turning_none;
//		}
		
		
		previousPosition_x = currentPosition_x;
		previousPosition_y = currentPosition_y;
	}
	else
	{
		AIvehicle->force = force_none;
		AIvehicle->turning = turning_none;
		AIvehicle->breaking = true;
	}
}