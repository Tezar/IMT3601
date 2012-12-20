#pragma once
#include "Scene.hpp"
#include "Engine.hpp"
#include "GameRenderer.hpp"
#include "Controller.hpp"
#include "AudioManager.hpp"
#include "AI.hpp"

#include <irrlicht.h>
using namespace irr;

class PracticeGameScene :
	public Scene
{
	GameRenderer* renderer;
	Engine* engine;
	AudioManagerClass* soundDevice;
	ArtificialIntelligence* AIvehicle1, *AIvehicle2;

public:
	PracticeGameScene(void);
	~PracticeGameScene(void);

	Controller* receiver;

	void createPointParticle(int x,int y,int z,int red,int green,int blue);

	void onEnter();
	int onFrame(int);
	bool onExit();
};

