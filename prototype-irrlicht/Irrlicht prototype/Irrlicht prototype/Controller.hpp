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
	enum deviceType {keyboard, gamepad};

public:
	Controller();
};