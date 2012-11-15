#pragma once
#include "Singleton.hpp"
#include "Scene.hpp"

#include <irrlicht.h>
using namespace irr;

enum states_t
	{
		menu,
		practiceGame
	};

class GameManagerClass
{
	/* stores current scene */
	Scene *currentScene;

	/* stores active device for rendering */
	IrrlichtDevice* device;

public:
	GameManagerClass(void);
	~GameManagerClass(void);

	/** @return int error code, 0 if ok */
	int run();

	Scene * changeState(states_t);
	

	//getters

	IrrlichtDevice * getDevice(void){ return device; }

};

typedef Singleton<GameManagerClass> GameManager;   // Global declaration

