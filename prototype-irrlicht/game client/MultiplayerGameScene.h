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

#include <irrlicht.h>
using namespace irr;

class MultiplayerGameScene :
	public Scene
{
	GameRenderer* renderer;
	Engine* engine;
	net::INetManager* netManager;
	net::INetManager* serverManager;
	MyNetCallback* netCallback;
	net::SOutPacket packet;
	core::stringw netStr;

	//video::IVideoDriver* driver = device->getVideoDriver();
	//IGUIEnvironment* env = device->getGUIEnvironment();
	//IrrlichtDevice * device = GameManager::getInstance()->getDevice();

public:

	MultiplayerGameScene(void);
	~MultiplayerGameScene(void);

	SAppContext context;
	MyEventReceiver* receiver;
	//Controller* receiver;

	void onEnter();
	int onFrame(int);
	bool onExit();
};

