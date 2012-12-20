#pragma once


#include <irrlicht.h>
#include "Vehicle.hpp"
#include "EventManager.hpp"
#include "AudioManager.hpp"

using namespace irr;

//BUG: when acc key is pressed steering is not changed (ie you cannont accelerate and turn at same time) /Aleš 8.12. 21:33 FIXED
//REQUEST: add hand break (vehicle.breaking = true) /Aleš 8.12. 21:33 ADDED


class Controller : public IEventReceiver
{
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

	irr::EKEY_CODE Forward;
	irr::EKEY_CODE Back;
	irr::EKEY_CODE Left;
	irr::EKEY_CODE Right;
	irr::EKEY_CODE HandBreak;
	irr::EKEY_CODE Fire;

	AudioManagerClass * sounds; 
	Vehicle * ControllerVehicle;

public:
	virtual bool OnEvent(const SEvent& event);
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	Controller(Vehicle * vehicleReference, AudioManagerClass * soundManager, bool player2);

	void ChangeKeySettings(int direction, irr::EKEY_CODE keyboardKey);

};
