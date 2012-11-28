#pragma once
#include "Scene.hpp"
#include "Engine.hpp"
#include "GameRenderer.hpp"
#include "Controller.hpp"
#include "Network_class_client.h"
#include "StartMenuUi.h"

#include <irrlicht.h>
using namespace irr;

class MultiplayerGameScene :
	public Scene
{
	GameRenderer* renderer;
	Engine* engine;
	net::INetManager* netManager;
	net::SOutPacket packet;

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

