#pragma once


#include <irrlicht.h>
#include "Vehicle.hpp"
#include "EventManager.h"

using namespace irr;

//	GET THE EVENT HANDLER WORKING

class Controller : public CIrrDeviceStub
{
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

	char Forward;
	char Back;
	char Left;
	char Right;
	char Fire;

	Vehicle * ControllerVehicle;
//	VehicleReference;

public:
	virtual bool OnEvent(const SEvent& event);
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	Controller(Vehicle * vehicleReference);

	void ChangeKeySettings(int direction, char keyboardKey);

	/*************************************************************************
	 *	Make the Controller class detect if the input is coming from the	 *
	 *	keyboard, AI, or network and have the class behave accordingly.		 *
	 *************************************************************************/

};
