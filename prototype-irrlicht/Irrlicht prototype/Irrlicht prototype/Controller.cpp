#include "controller.hpp"
#include "Vehicle.hpp"

using namespace irr;

bool Controller::OnEvent(const SEvent& event)
{
	//	Remember whether each key is down or up.
	if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;


		if (IsKeyDown(KEY_KEY_W))
			ControllerVehicle->force = force_forward;

		else if (IsKeyDown(KEY_KEY_A))
			ControllerVehicle->turning = turning_left;

		else if (IsKeyDown(KEY_KEY_S))
			ControllerVehicle->force = force_backward;

		else if (IsKeyDown(KEY_KEY_D))
			ControllerVehicle->turning = turning_right;

		//else if (IsKeyDown(Fire))
		//	RequestingPermissionToLaunchNukes;

		//else if (IsKeyDown(KEY_ESCAPE))
		//	OpenMenu;

		else
		{
			ControllerVehicle->force = force_none;
			ControllerVehicle->turning = turning_none;
		}
	}
	

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

Controller::Controller(Vehicle * vehicleReference)
{
	ControllerVehicle = vehicleReference;

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