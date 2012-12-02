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


	
//	EventManager::getInstance()->addEventReceiver(receiver);
	EventManager::getInstance()->addEventReceiver(this);

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
		net::SOutPacket packet;
		if(netManager->getConnectionStatus() != net::EICS_FAILED){
			
			packet << "blue";

			netManager->sendOutPacket(packet);
			netManager->update();
			
		}

}

int MultiplayerGameScene::onFrame(int toDo){
	
	if(netCallback->ant_game > 0){
		context.listbox->clear();
		for(int i = 1; netCallback->ant_game >= i; ++i){
			context.listbox->addItem(stringw(netCallback->games[i-1]).c_str());
		}
	}else{
		context.listbox->clear();
		context.listbox->addItem(stringw(netCallback->str).c_str());
	}

	netManager->update();
	return 0;
}


bool MultiplayerGameScene::onExit()
{
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	device->getGUIEnvironment()->clear();
	EventManager::getInstance()->removeEventReceiver(receiver);

	delete netManager;
	return true;
}

bool MultiplayerGameScene::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_GUI_EVENT){
		s32 id = event.GUIEvent.Caller->getID();
			switch(event.GUIEvent.EventType){
				case EGET_BUTTON_CLICKED:
					switch(id){
						case GUI_ID_MULTY_CREATE_BUTTON:
							{
								net::SOutPacket lobbypacket;
								lobbypacket << "Not blue";

								netManager->sendOutPacket(lobbypacket);
								netManager->update();
								return 0;
							}
								return true;
								
						default:
							return false;
					}
					break;

				default:
					break;
			}
	}
	return false;
}

//void MultiplayerGameScene::createLobby()
//{
//	packet << "Not blue";
//
//	netManager->sendOutPacket(packet);
//	netManager->update();
//}
