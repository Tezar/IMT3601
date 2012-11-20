#pragma once
#include "MultiplayerGameScene.h"
#include "Network_class_client.h"
#include "GameManagerClass.hpp"
#include "Vehicle.hpp"
#include "Controller.hpp"
#include "EventManager.hpp"

//todo: remove unused
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

using namespace io;
using namespace irr;


MultiplayerGameScene::MultiplayerGameScene(void)
{
}


MultiplayerGameScene::~MultiplayerGameScene(void)
{
}



void MultiplayerGameScene::onEnter()
{
	engine = new Engine();
	Vehicle * vehicle1 = engine->addVehicle( new Vehicle() );
	//engine->addVehicle( new Vehicle() );
	
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	receiver = new Controller(vehicle1);
	
	EventManager::getInstance()->addEventReceiver(receiver);	//	Adds a new event receiver to the list, for the controller.

//	device->setEventReceiver(receiver);

	engine->reset();
	
	renderer = new GameRenderer(engine);
	renderer->attach(device);


	//Network
		netManager = net::createIrrNetClient(0, "127.0.0.1");
		
		// Enable debug messages.
		netManager->setVerbose(true);

			//netManager->update(1000);

}

int MultiplayerGameScene::onFrame(int toDo){

	toDo = engine->step(toDo);
			if(netManager->getConnectionStatus() != net::EICS_FAILED){
			// To send a packet, first you create an SOutPacket object.
			net::SOutPacket packet;
			
			// Then you can use the streaming operator << to add new data to it.
			packet << "Help I am stuck on a mountain!";
			
			// You can even chain the << operators like so, just like with ostream.
			packet << core::vector3df(50.0f, 30.0f, 20.0f) << 50.0f;
			
			// Compress the packet, not much to be said.
			packet.compressPacket();
			
			packet.encryptPacket("hushthisissecret");
			// A simple call to "sendOutPacket" will send the packet to the server.
			netManager->sendOutPacket(packet);
			}
	renderer->update();
	
	return toDo;
}


bool MultiplayerGameScene::onExit()
{
	EventManager::getInstance()->removeEventReceiver(receiver);
	//free this scene after exit
	delete netManager;
	return true;
}

