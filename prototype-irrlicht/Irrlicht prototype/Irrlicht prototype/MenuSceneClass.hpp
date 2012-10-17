#pragma once
#include "scene.hpp"
#include "Singleton.hpp"
#include "GameManagerClass.hpp"
#include "StartMenuUi.h"

#include <irrlicht.h>
using namespace irr;


class MenuSceneClass :
	public Scene
{

public:
	MenuSceneClass(void);
	~MenuSceneClass(void);

	SAppContext context;
	MyEventReceiver* receiver;


	void onEnter();
	int onFrame(int);
	bool onExit();
};


typedef Singleton<MenuSceneClass> MenuScene;   // Global declaration