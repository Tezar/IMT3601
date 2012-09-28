#pragma once
#include "scene.hpp"
#include "Singleton.hpp"
#include "GameManagerClass.hpp"

#include <irrlicht.h>
using namespace irr;


class MenuClass :
	public Scene
{

public:
	MenuClass(void);
	~MenuClass(void);

	void onEnter();
	int onFrame(int);
	bool onExit();
};


typedef Singleton<MenuClass> Menu;   // Global declaration