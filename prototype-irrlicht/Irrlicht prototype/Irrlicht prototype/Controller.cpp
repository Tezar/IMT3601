#include "Controller.hpp"

using namespace irr;

Controller::Controller()
{
	/* Stuff happens */
}

Controller::Controller(int devType, bool gamepadConnected)
{
	if (gamepadConnected)
	{
		//whatKindOfDeviceIsConnected = devType;			// Why redline?
	}

}

Controller::~Controller()
{
	/* Does stuff happen? */
}