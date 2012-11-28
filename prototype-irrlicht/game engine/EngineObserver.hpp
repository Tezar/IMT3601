#pragma once
#include "irrlicht.h"
#include "btBulletDynamicsCommon.h"


/* "interface" for listeners */
class EngineObserver{
	public:
		virtual void onBodyNew(btRigidBody*, ObjectRecord*){};
		virtual void onBodyUpdate(btRigidBody*, const btTransform&){};
		virtual void onBodyDelete(btRigidBody* ){};
};
