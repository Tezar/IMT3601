#pragma once
#include <irrlicht.h>


using namespace irr;

/*****************************************************************************
 *	This eventmanager was made by user chromdragon from the irrlicht forums, *
 *	http://irrlicht.sourceforge.net/forum//viewtopic.php?t=11785.			 *
 *****************************************************************************/

class CIrrDeviceStub : public IEventReceiver
{
private:
	core::array<IEventReceiver*> ReceiverList;

public:
	void addEventReceiver(IEventReceiver *receiver);
	void removeEventReceiver(IEventReceiver *receiver);

//	void postEventFromUser(SEvent event);
};