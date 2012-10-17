#include "controller.hpp"

using namespace irr;

bool Controller::OnEvent(const SEvent& event)
{
	//	Remember whether each key is down or up.
	if (event.EventType == EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

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

Controller::Controller()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; i++)
		KeyIsDown[i] = false;
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