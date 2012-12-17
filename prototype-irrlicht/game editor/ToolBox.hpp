#include <irrlicht.h>
#include <iostream>

#include "ObjectReader.hpp"
#include "ObjectRecord.hpp"
#include "GameObjectManager.hpp"
#include "EditorEnvironment.hpp"

using namespace irr;
using namespace gui;

#pragma once
class ToolBox
{
protected:
	ISceneNode* node;
public:
	ToolBox(ISceneNode*);
	~ToolBox(void);
};

