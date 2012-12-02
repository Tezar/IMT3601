#include <assert.h>
#include <windows.h>
#include <stdio.h>
#include <functional>
#include "Engine.hpp"
  
class EngineBodyState: public btMotionState {
public:
    EngineBodyState(Engine * e, irr::u32 _id, const btTransform &initialpos) {
        engine = e;
		id = _id;
        mPos1 = initialpos;
    }

    virtual ~EngineBodyState() {
    }

	virtual void getWorldTransform(btTransform &worldTrans) const {
        worldTrans = mPos1;
		
    }

    virtual void setWorldTransform(const btTransform &worldTrans) {
		engine->notifyShapeUpdate(btBody->getCollisionShape(), worldTrans);
		mPos1 = worldTrans;

    }

	void setBody(btRigidBody* body)
	{
		btBody = body;
	}

	btRigidBody* getBody()
	{
		return btBody;
	}

protected:
	irr::u32 id;
    Engine* engine;
	btRigidBody* btBody;
    btTransform mPos1;
};



  
class EngineVehicleState: public EngineBodyState {
public:
	EngineVehicleState(Engine * e, Vehicle* _vehicle, const btTransform &initialpos): EngineBodyState(e,0, initialpos) {
		vehicle = _vehicle;
	}
    virtual void setWorldTransform(const btTransform &worldTrans) {
		engine->notifyShapeUpdate(btBody->getCollisionShape(), worldTrans);
		mPos1 = worldTrans;



		for (int i=0;i<vehicle->pointer->getNumWheels();i++)
		{
			//synchronize the wheels with the (interpolated) chassis worldtransform
			vehicle->pointer->updateWheelTransform(i,true);
			//draw wheels (cylinders)
			engine->notifyShapeUpdate(vehicle->shapes[i], vehicle->pointer->getWheelInfo(i).m_worldTransform );
		}


    }


protected:
	Vehicle* vehicle;
};

