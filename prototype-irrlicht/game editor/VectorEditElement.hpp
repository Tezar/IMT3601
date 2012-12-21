#pragma once

#include <irrlicht.h>
#include "EditorEnvironment.hpp"
#include "btBulletDynamicsCommon.h"

using namespace irr;
using namespace gui;
using namespace core;

class VectorEditElement
{
protected:
	const vector3df& target;

	gui::IGUISpinBox* boX;
	gui::IGUISpinBox* boY;
	gui::IGUISpinBox* boZ;

public:
	VectorEditElement(gui::IGUIElement*, int x, int y, const vector3df&);
	~VectorEditElement(void);

	//void apply();
	//maybe apply only to node and then retract from id node?
	//void apply(const btVector3&);

	//refresh the values from the current state of vector
	void refresh();

	int getHeight(){ return 30; }
	int getOffset(){ return getHeight()*1.2; }

};

