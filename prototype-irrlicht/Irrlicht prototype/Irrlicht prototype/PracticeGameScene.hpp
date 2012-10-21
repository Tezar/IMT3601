#pragma once
#include "Scene.hpp"
#include "Engine.hpp"
#include "GameRenderer.hpp"
#include "Controller.hpp"

#include <irrlicht.h>
using namespace irr;

class PracticeGameScene :
	public Scene
{
	GameRenderer* renderer;
	Engine* engine;

public:
	PracticeGameScene(void);
	~PracticeGameScene(void);

	Controller* receiver;

	void onEnter();
	int onFrame(int);
	bool onExit();
};

