#pragma once
#include "MultiplayerGameScene.h"
#include "Network_class_client.h"
#include "GameManagerClass.hpp"
#include "Vehicle.hpp"
#include "Controller.hpp"
#include "EventManager.hpp"
#include "StartMenuUi.h"
#include "MenuSceneClass.hpp"


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

	EventManager::getInstance()->addEventReceiver(this);
	video::IVideoDriver* driver = device->getVideoDriver();
	//GUI elements
    IGUIEnvironment* env = device->getGUIEnvironment();
	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("../media/bigfont.png");
    if (font)
            skin->setFont(font);
	env->addStaticText(L"Active games:", rect<s32>(100,100,700,100 + 72), true);
	//adds a listbox
	IGUIListBox* listbox = env->addListBox(rect<s32>(100,100 + 80,700,100 + 160 + 72));
	context.device = device;
	context.counter = 0;
	context.listbox = listbox;

	//test to see if its resiving packets
	context.listbox->addItem(L"No incoming text");
		
	for (u32 i=0; i<EGDC_COUNT ; ++i)
		{
			SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
			col.setAlpha(200);
			env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
		}
	//adds all the buttons
	env->addButton(rect<s32>(100,100 + 240,360,100 + 240 + 72), 0, GUI_ID_MULTY_JOIN_BUTTON,
                    L"Join", L"Joins the game");
	env->addButton(rect<s32>(360 + 16,100 + 240,700,100 + 240 + 72), 0, GUI_ID_MULTY_CREATE_BUTTON,
                    L"Create", L"Creates a game");
	env->addButton(rect<s32>(100,100 + 320,700,100 + 320 + 72), 0, GUI_ID_MULTY_BACK_BUTTON,
                    L"Back to start menu", L"goes back to the start menu");

	//Devices used for networking
	netCallback = new MyNetCallback();
	netManager = net::createIrrNetClient(netCallback, "127.0.0.1");
	netManager->setVerbose(true);

	//makes an packet
	net::SOutPacket packet;
	if(netManager->getConnectionStatus() != net::EICS_FAILED){			
		//if there is an connection, this message will let the server know
		//that a new client is connected and needs all the "new-client" information
		packet << "blue";
		netManager->sendOutPacket(packet);
		//adds the packed to the stack and update sends the whole stack
		netManager->update();
	}

}

int MultiplayerGameScene::onFrame(int toDo){
	//on every frame it checks if any new games have been made
	//and if so, adds them to the list.
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
	//removes all used devises
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	device->getGUIEnvironment()->clear();
	EventManager::getInstance()->removeEventReceiver(receiver);

	delete netManager;
	return true;
}

bool MultiplayerGameScene::OnEvent(const SEvent& event)
{
	//made a personal event reciver for multiplayer
	//so we dont have to add the networking part
	//to the normal GUI
	if (event.EventType == EET_GUI_EVENT){
		s32 id = event.GUIEvent.Caller->getID();
			switch(event.GUIEvent.EventType){
				case EGET_BUTTON_CLICKED:
					switch(id){
						case GUI_ID_MULTY_CREATE_BUTTON:
							{
								//when you want to create a lobby
								//lets the server know what you want
								net::SOutPacket lobbypacket;
								lobbypacket << "Not blue";

								netManager->sendOutPacket(lobbypacket);
								netManager->update();
								return 0;
							}
								return true;

						case GUI_ID_MULTY_BACK_BUTTON:
							{
								//changes back to the main menu
								//broken atm
								//GameManager::getInstance()->changeState(menu);
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