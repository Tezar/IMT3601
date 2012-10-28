#include "controller.hpp"
#include "Vehicle.hpp"

using namespace irr;

bool Controller::OnEvent(const SEvent& event)
{
	//	Remember whether each key is down or up.
	if (event.EventType == EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;


	//	Only need to make the referencing vehicle from engine.

//	if (IsKeyDown(KEY_KEY_W))
//		VehicleReference->force = force_forward;
//
//	else if (IsKeyDown(KEY_KEY_A))
//		VehicleReference->turning = turning_left;
//
//	else if (IsKeyDown(KEY_KEY_S))
//		VehicleReference->force = force_backward;
//
//	else if (IsKeyDown(KEY_KEY_D))
//		VehicleReference->turning = turning_right;
//
//	else if (IsKeyDown(Fire))
//		RequestingPermissionToLaunchNukes;
//
//	else if (IsKeyDown(KEY_ESCAPE))
//		OpenMenu;
//
//	else
//	{
//		VehicleReference->force = force_none;
//		VehicleReference->turning = turning_none;
//	}

	return false;
}

/*****************************************************************************
 *	Probably need to add a check to see whether the key being held down is	 *
 *	on a keyboard or from the network or AI and adjust accoringly.			 *
 *****************************************************************************/

bool Controller::IsKeyDown(EKEY_CODE keyCode) const
{											//	Checks if key is being
	return KeyIsDown[keyCode];				//	held down.
}

Controller::Controller(/* ReferencingTheVehicle */)
{
//	ReferencingTheVehicle = VehicleReference;

	Forward = KEY_KEY_W;
	Back	= KEY_KEY_S;
	Left	= KEY_KEY_A;
	Right	= KEY_KEY_W;
	Fire	= KEY_SPACE;

	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; i++)
		KeyIsDown[i] = false;
}

void Controller::ChangeKeySettings(int direction, char keyboardKey)
{
	switch(direction)
	{
		case 0: Forward = keyboardKey;	break;
		case 1: Back	= keyboardKey;	break;
		case 2: Left	= keyboardKey;	break;
		case 3: Right	= keyboardKey;	break;
		case 4: Fire	= keyboardKey;	break;

		default: break;
	}
}


/*****************************************************************************
 *	Have to somehow make the vehicles slow down while the forward button	 *
 *	isn't being held down, and slow down at a faster rate while the reverse  *
 *	button is being held down. The first part could be achieved through      *
 *	physics settings or maybe having a current speed variable in the vehicle *
 *	class(maybe not a good idea since it would have to be updated constantly)*
 *	The default state can be to slow down to a stop.						 *
 *																			 *
 *	Maybe we can use a switch instead?										 *
 *****************************************************************************/
void DontKnowWhereToPutThisSoIPutItHere()
{
	Controller inputDevice;



	if (inputDevice.IsKeyDown(KEY_KEY_W) || inputDevice.IsKeyDown(KEY_UP))
	{
		/* Increase acceleration */
	}
	else if (inputDevice.IsKeyDown(KEY_KEY_S) || inputDevice.IsKeyDown(KEY_DOWN))
	{
		/* Decelerate/reverse */
	}


	if (inputDevice.IsKeyDown(KEY_KEY_A) || inputDevice.IsKeyDown(KEY_LEFT))
	{
		/* Turn counter-clockwise until button is let go */
	}
	else if (inputDevice.IsKeyDown(KEY_KEY_D) || inputDevice.IsKeyDown(KEY_RIGHT))
	{
		/* Turn clockwise until button is let go */
	}


	if (inputDevice.IsKeyDown(KEY_CONTROL) || inputDevice.IsKeyDown(KEY_SPACE))
	{
		/* Fire rocket */
	}
}