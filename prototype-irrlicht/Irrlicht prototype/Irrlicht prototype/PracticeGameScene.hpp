#pragma once
#include "Scene.hpp"
#include "Engine.hpp"
#include "GameRenderer.hpp"

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

	void onEnter();
	int onFrame(int);
	bool onExit();
};

