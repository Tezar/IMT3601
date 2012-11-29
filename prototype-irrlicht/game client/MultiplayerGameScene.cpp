#pragma once
#include "MultiplayerGameScene.h"
#include "Network_class_client.h"
#include "GameManagerClass.hpp"
#include "Vehicle.hpp"
#include "Controller.hpp"
#include "EventManager.hpp"
#include "StartMenuUi.h"
#include "MenuSceneClass.hpp"

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
    IrrlichtDevice * device = GameManager::getInstance()->getDevice();

	receiver = new MyEventReceiver(context);


	
	EventManager::getInstance()->addEventReceiver(receiver);
//	device->setEventReceiver(receiver);

        video::IVideoDriver* driver = device->getVideoDriver();
        IGUIEnvironment* env = device->getGUIEnvironment();
		IGUISkin* skin = env->getSkin();
		IGUIFont* font = env->getFont("../media/bigfont.png");
        if (font)
                skin->setFont(font);
		env->addStaticText(L"Active games:", rect<s32>(100,100,700,100 + 72), true);
		IGUIListBox* listbox = env->addListBox(rect<s32>(100,100 + 80,700,100 + 160 + 72));

		context.device = device;
		context.counter = 0;
		context.listbox = listbox;

		context.listbox->addItem(L"Text");
		
		for (u32 i=0; i<EGDC_COUNT ; ++i)
			{
				SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
				col.setAlpha(200);
				env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
			}

		env->addButton(rect<s32>(100,100 + 240,360,100 + 240 + 72), 0, GUI_ID_MULTY_JOIN_BUTTON,
                        L"Join", L"Joins the game");
		env->addButton(rect<s32>(360 + 16,100 + 240,700,100 + 240 + 72), 0, GUI_ID_MULTY_CREATE_BUTTON,
                        L"Create", L"Creates a game");
		env->addButton(rect<s32>(100,100 + 320,700,100 + 320 + 72), 0, GUI_ID_MULTY_BACK_BUTTON,
                        L"Back to start menu", L"goes back to the start menu");

	//Network
		//MyNetCallback* netCallback = new MyNetCallback();
		netCallback = new MyNetCallback();
		netManager = net::createIrrNetClient(netCallback, "127.0.0.1");
		//netManager->setNetCallback(netCallback);
		
	// Enable debug messages.
		netManager->setVerbose(true);

		if(netManager->getConnectionStatus() != net::EICS_FAILED){
			
			//netManager->update();
			// Then you can use the streaming operator << to add new data to it.
			packet << "blue";
			
			// You can even chain the << operators like so, just like with ostream.
			//packet << core::vector3df(50.0f, 30.0f, 20.0f) << 50.0f;
			
			//compressing and encrypting disabled atm because of a stack problem
			// Compress the packet, not much to be said.
			//packet.compressPacket();
			
			//packet.encryptPacket("hushthisissecret");
			// A simple call to "sendOutPacket" will send the packet to the server.
			netManager->sendOutPacket(packet);
			netManager->update();
			
		}

}

int MultiplayerGameScene::onFrame(int toDo){

	//toDo = engine->step(toDo);

	//renderer->update();

	//netManager->sendOutPacket(packet);
	//netCallback->getStr(netStr);
	//if(netCallback->str != "0"){

		context.listbox->clear();
		//context.listbox->addItem(netCallback->str);
	//info.setText( irr::core::stringw( CollMan->getSceneNodeFromScreenCoordinatesBB(blah)->getName() ).c_str() );
		context.listbox->addItem(stringw(netCallback->str).c_str());	
	//}
	netManager->update();
	return 0;
	/*return toDo;*/
}


bool MultiplayerGameScene::onExit()
{
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	//device->setEventReceiver(0);
	device->getGUIEnvironment()->clear();
	EventManager::getInstance()->removeEventReceiver(receiver);
	//free this scene after exit
	delete netManager;
	return true;
}

