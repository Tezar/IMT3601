#include <irrlicht.h>
#include "UserInput.hpp"

using namespace irr;

/*****************************************************************************
 *	My thinking here is that we use this class to identify what type of      *
 *	controller the user is gonna use (keyboard, xbox 360 gamepad, etc) with  *
 *	an enum or something, and based on that enum value the correct functions *
 *	for that device are run.												 *
 *****************************************************************************/
class Controller : public UserInput
{
private:
	enum whatKindOfDeviceIsConnected {keyboard, gamepad};
	bool isAGamepadConnected;

public:
	Controller();
	Controller(int devType, bool gamepadConnected);
	/*************************************************************************
	 *	I don't yet know how gamepad detection works or how it's done,		 *
	 *	but I'm thinking that a constructor with a parameter can somehow be  *
	 *	used to set the enum and make the correct functions be called.		 *
	 *************************************************************************/
	~Controller();
};