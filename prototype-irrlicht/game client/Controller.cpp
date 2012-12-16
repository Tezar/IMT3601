#include "controller.hpp"
#include "Vehicle.hpp"
#include "EventManager.hpp"

using namespace irr;

bool Controller::OnEvent(const SEvent& event)
{
	//	Remember whether each key is down or up.
	if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;


		if (IsKeyDown(Forward))
		{
			ControllerVehicle->force = force_forward;
			sounds->PlaySound(E_TestSound, irrklang::vec3df(0,-1,1));
		}
		else if (IsKeyDown(Back))
			ControllerVehicle->force = force_backward;
		else
			ControllerVehicle->force = force_none;



		if (IsKeyDown(Left))
			ControllerVehicle->turning = turning_left;
		else if (IsKeyDown(Right))
			ControllerVehicle->turning = turning_right;
		else
			ControllerVehicle->turning = turning_none;


		
		if (IsKeyDown(HandBreak))
			ControllerVehicle->breaking = true;
		else
			ControllerVehicle->breaking = false;

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

Controller::Controller(Vehicle * vehicleReference, AudioManagerClass * soundManager, bool player2)
{
	ControllerVehicle = vehicleReference;
	sounds = soundManager;

	if (player2)
	{
		Forward		= KEY_UP;
		Back		= KEY_DOWN;
		Left		= KEY_LEFT;
		Right		= KEY_RIGHT;
		HandBreak	= KEY_NUMPAD0;
		Fire		= KEY_RCONTROL;
	}

	else
	{
		Forward		= KEY_KEY_W;
		Back		= KEY_KEY_S;
		Left		= KEY_KEY_A;
		Right		= KEY_KEY_D;
		HandBreak	= KEY_SPACE;
		Fire		= KEY_LCONTROL;
	}

	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; i++)
		KeyIsDown[i] = false;
}

void Controller::ChangeKeySettings(int direction, irr::EKEY_CODE keyboardKey)
{
	switch(direction)
	{
		case 0: Forward		= keyboardKey;	break;
		case 1: Back		= keyboardKey;	break;
		case 2: Left		= keyboardKey;	break;
		case 3: Right		= keyboardKey;	break;
		case 4: HandBreak	= keyboardKey;	break;
		case 5: Fire		= keyboardKey;	break;

		default: break;
	}
}