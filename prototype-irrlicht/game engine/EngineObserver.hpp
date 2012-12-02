#pragma once
#include "irrlicht.h"
#include "btBulletDynamicsCommon.h"


/* "interface" for listeners */
class EngineObserver{
	public:
		virtual void onShapeNew(btCollisionShape*, ObjectRecord*){};
		virtual void onShapeUpdate(btCollisionShape*, const btTransform&){};
		virtual void onShapeDelete(btCollisionShape* ){};
};
