#pragma once
#include <irrlicht.h>
#include "Singleton.hpp"

using namespace irr;

/*****************************************************************************
 *	This eventmanager was made by user chromdragon from the irrlicht forums, *
 *	http://irrlicht.sourceforge.net/forum//viewtopic.php?t=11785.			 *
 *****************************************************************************/

class CIrrDeviceStubclass : public IEventReceiver
{
private:
	core::array<IEventReceiver*> ReceiverList;

public:
	void addEventReceiver(IEventReceiver *receiver);
	void removeEventReceiver(IEventReceiver *receiver);

	virtual bool OnEvent(const SEvent& event);

//	void postEventFromUser(SEvent event);
};

typedef Singleton<CIrrDeviceStubclass> EventManager;   // Global declaration