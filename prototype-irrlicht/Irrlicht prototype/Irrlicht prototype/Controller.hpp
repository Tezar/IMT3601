#pragma once

#include <irrlicht.h>
using namespace irr;

class Controller : public IEventReceiver
{
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

	char Forward;
	char Back;
	char Left;
	char Right;
	char Fire;

//	VehicleReference;

public:
	virtual bool OnEvent(const SEvent& event);
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	Controller(/* ReferencingTheVehicle */);

	void ChangeKeySettings(int direction, char keyboardKey);

	/*************************************************************************
	 *	Make the Controller class detect if the input is coming from the	 *
	 *	keyboard, AI, or network and have the class behave accordingly.		 *
	 *************************************************************************/

};
