#pragma once


#include <irrlicht.h>
#include "Vehicle.hpp"
#include "EventManager.hpp"
#include "AudioManager.hpp"

using namespace irr;

//BUG: when acc key is pressed steering is not changed (ie you cannont accelerate and turn at same time) /Aleš 8.12. 21:33
//REQUEST: add hand break (vehicle.breaking = true) /Aleš 8.12. 21:33


class Controller : public IEventReceiver
{
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

	char Forward;
	char Back;
	char Left;
	char Right;
	char Fire;

	AudioManagerClass * sounds; //Trying to use this won't let me use any functions...
	Vehicle * ControllerVehicle;

public:
	virtual bool OnEvent(const SEvent& event);
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	Controller(Vehicle * vehicleReference, AudioManagerClass * soundManager);

	void ChangeKeySettings(int direction, char keyboardKey);

	/*************************************************************************
	 *	Make the Controller class detect if the input is coming from the	 *
	 *	keyboard, AI, or network and have the class behave accordingly.		 *
	 *************************************************************************/

};
