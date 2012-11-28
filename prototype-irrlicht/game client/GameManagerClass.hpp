#pragma once
#include "Singleton.hpp"
#include "ObjectReader.hpp"
#include "Scene.hpp"

#include <irrlicht.h>
using namespace irr;
using namespace core;

enum states_t
	{
		menu,
		practiceGame,
		multiPlayerGame
	};

class GameManagerClass
{
protected:
	/* stores current scene */
	Scene *currentScene;

	/* stores active device for rendering */
	IrrlichtDevice* device;
	ObjectReader *  objectReader;

public:
	GameManagerClass(void);
	~GameManagerClass(void);

	/** @return int error code, 0 if ok */
	int run();

	Scene * changeState(states_t);
	

	//getters

	IrrlichtDevice * getDevice(void){ return device; }

	ObjectReader * getReader(void){ return objectReader; }



};

typedef Singleton<GameManagerClass> GameManager;   // Global declaration

