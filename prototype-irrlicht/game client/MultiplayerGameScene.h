#pragma once
#include "Scene.hpp"
#include "Engine.hpp"
#include "GameRenderer.hpp"
#include "Controller.hpp"
#include "Network_class_client.h"

#include <irrlicht.h>
using namespace irr;

class MultiplayerGameScene :
	public Scene
{
	GameRenderer* renderer;
	Engine* engine;
	net::INetManager* netManager;

public:
	MultiplayerGameScene(void);
	~MultiplayerGameScene(void);

	Controller* receiver;

	void onEnter();
	int onFrame(int);
	bool onExit();
};

