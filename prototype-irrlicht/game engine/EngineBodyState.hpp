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

