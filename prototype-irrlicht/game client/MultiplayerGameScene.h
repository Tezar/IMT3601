#pragma once
#include "Scene.hpp"
#include "Engine.hpp"
#include "GameRenderer.hpp"
#include "Controller.hpp"
#include "Network_class_client.h"
#include "StartMenuUi.h"
#include "MultiplayerGameScene.h"
#include "GameManagerClass.hpp"
#include "Vehicle.hpp"
#include "EventManager.hpp"
#include "StartMenuUi.h"
#include "MenuSceneClass.hpp"

#include <iostream>
#include <string>
#include <irrlicht.h>

using namespace irr;
using namespace std;

class MultiplayerGameScene :
	public Scene
{
	GameRenderer* renderer;
	Engine* engine;
	net::INetManager* netManager;
	MyNetCallback* netCallback;
	net::SOutPacket packet;
	stringc msg;
	

	//video::IVideoDriver* driver = device->getVideoDriver();
	//IGUIEnvironment* env = device->getGUIEnvironment();
	//IrrlichtDevice * device = GameManager::getInstance()->getDevice();

public:

	MultiplayerGameScene(void);
	~MultiplayerGameScene(void);

	SAppContext context;
	MyEventReceiver* receiver;
	//Controller* receiver;
	
	//void createLobby();
	void onEnter();
	int onFrame(int);
	bool onExit();
};

//typedef Singleton<MultiplayerGameScene> MultiplayerManager;   // Global declaration

