#include "UserInput.hpp"

using namespace irr;

bool UserInput::OnEvent(const SEvent& event)
{
	//	Remember whether each key is down or up.
	if (event.EventType == EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	return false;
}

bool UserInput::IsKeyDown(EKEY_CODE keyCode) const
{											//	Checks if key is being
	return KeyIsDown[keyCode];				//	held down.
}

UserInput::UserInput()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; i++)
		KeyIsDown[i] = false;
}



/************************************************************
 *  UNSURE WHERE TO PUT THIS SO I JUST MAKE IT HERE FOR NOW *
 ************************************************************/

void DontKnowWhereToPutThisSoIPutItHere()
{
	UserInput inputDevice;

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