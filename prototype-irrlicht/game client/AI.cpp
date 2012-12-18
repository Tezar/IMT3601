#include <Singleton.hpp>
#include <Engine.hpp>
#include "AI.hpp"
#include <cmath>

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
	
//	vehicleRotation = ((ISceneNode*)( AIvehicle->chassis->getUserPointer() ))->getRotation().Y;

	irr::core::matrix4 matr;
	btTransform trans;

	AIvehicle->chassis->getMotionState()->getWorldTransform(trans);
	trans.getOpenGLMatrix(matr.pointer());
	vehicleRotation = (matr.getRotationDegrees().Y/180)*PI;

 

	if(currentWaypointNr <= waypoints.size())
	{
		//if((distanceToNextWaypoint_x <= 3.0f) && (distanceToNextWaypoint_x >= -3.0f) &&
		//   (distanceToNextWaypoint_z <= 3.0f) && (distanceToNextWaypoint_z >= -3.0f))
		//{
		//	AssignWaypoints();
		//}
		NextWaypoint = waypoints[AIvehicle->nextWaypoint];

		currentPosition_x = AIvehicle->position.X;
		currentPosition_z = AIvehicle->position.Z;
		distanceToNextWaypoint_x = currentPosition_x - NextWaypoint.x();
		distanceToNextWaypoint_z = currentPosition_z - NextWaypoint.z();
		previousDistanceToNextWaypoint_x = previousPosition_x - NextWaypoint.x();
		previousDistanceToNextWaypoint_z = previousPosition_z - NextWaypoint.z();

		direction = atan2(distanceToNextWaypoint_x, distanceToNextWaypoint_z);
		
		float diff = vehicleRotation - direction;

		if(abs(diff) > 0.1)
		{
			if( diff >  0)
			{
				AIvehicle->turning = turning_right;
			}else
			{
				AIvehicle->turning = turning_left;
			}
		}else
			AIvehicle->turning = turning_none;


//		if(previousDistanceToNextWaypoint_x < 0)
//		{
//			if(previousDistanceToNextWaypoint_x < distanceToNextWaypoint_x)
//			{
//		//		if(AIvehicle->turning != turning_right)
//					AIvehicle->turning = turning_left;
//			}
//			else
//				AIvehicle->turning = turning_none;
//		}
//		else if(previousDistanceToNextWaypoint_x > 0)
//		{
//			if(previousDistanceToNextWaypoint_x < distanceToNextWaypoint_x)
//			{
//		//		if(AIvehicle->turning != turning_left)
//					AIvehicle->turning = turning_right;
//			}
//			else
//				AIvehicle->turning = turning_none;
//		}
//
//		if(previousDistanceToNextWaypoint_z < 0)
//		{
//			if(previousDistanceToNextWaypoint_z < distanceToNextWaypoint_z)
//			{
//		//		if(AIvehicle->turning != turning_right)
//					AIvehicle->turning = turning_left;
//			}
//			else
//				AIvehicle->turning = turning_none;
//		}
//		else if(previousDistanceToNextWaypoint_z > 0)
//		{
//			if(previousDistanceToNextWaypoint_z < distanceToNextWaypoint_z)
//			{
//		//		if(AIvehicle->turning != turning_left)
//					AIvehicle->turning = turning_right;
//			}
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
		previousPosition_z = currentPosition_z;
	}
	else
	{
		AIvehicle->force = force_none;
		AIvehicle->turning = turning_none;
		AIvehicle->breaking = true;
	}
}