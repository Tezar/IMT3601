#pragma once
#include "irrlicht.h"
#include "btBulletDynamicsCommon.h"


/* "interface" for listeners */
class EngineObserver{
	public:
		virtual void onBodyNew(irr::u32 id,const btTransform* transform){};
		virtual void onBodyUpdate(irr::u32 id,const btTransform* transform){};
		virtual void onBodyDelete(irr::u32 id,const btTransform* transform){};
};
