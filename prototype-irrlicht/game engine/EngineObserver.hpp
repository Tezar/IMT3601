#pragma once
#include "irrlicht.h"
#include "btBulletDynamicsCommon.h"


/* "interface" for listeners */
class EngineObserver{
	public:
		virtual void onBodyMovement(irr::u32 id,const btTransform* transform){};
		virtual void onVehicleMovement(irr::u32 id,Vehicle*){};
		virtual void afterSegmentLoaded(TrackSegment* segment){};
		virtual void beforeSegmentUnLoaded(TrackSegment* segment){};
};
