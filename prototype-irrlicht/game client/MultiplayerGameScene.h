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
	public Scene, IEventReceiver
{
	GameRenderer* renderer;
	Engine* engine;
	net::INetManager* netManager;
	MyNetCallback* netCallback;
	stringc msg;
	

public:
	
	MultiplayerGameScene(void);
	~MultiplayerGameScene(void);

	virtual bool OnEvent(const SEvent& event);

	SAppContext context;
	MyEventReceiver* receiver;

	void onEnter();
	int onFrame(int);
	bool onExit();
};


