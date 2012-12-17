#pragma once

#include <irrlicht.h>
#include <iostream>

#include "ObjectReader.hpp"
#include "ObjectRecord.hpp"
#include "GameObjectManager.hpp"

using namespace irr;
using namespace gui;



class ToolBox
{
protected:
	ISceneNode* node;

	//creates all that fancy stuff
	void populate();

public:
	ToolBox(ISceneNode*);
	~ToolBox(void);

	void apply();
};

