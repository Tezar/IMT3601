#pragma once
#include <irrlicht.h>

#include <string>
#include <stdio.h>
#include "btBulletDynamicsCommon.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace io;



enum E_OBJECT_TYPE{
	EOT_VEHICLE,
	EOT_SEGMENT,
	EOT_CHASSIS,
	EOT_WHEEL,
	EOT_BODY,	//general body
	EOT_BOX,	
};


enum E_SHAPE{
	ES_NONE,
	ES_BOX,
	ES_SPHERE,
	ES_CYLINDER,
};



class ObjectRecord
{
protected: 
	map<std::string, std::string> extra; 


	void readVec3d(const char *, btVector3&);
	void readShape(const char *, E_SHAPE&);

	void ObjectRecord::readType(const char *,  E_OBJECT_TYPE& );


public:
	ObjectRecord();
	~ObjectRecord();

	btCollisionShape* createShape();
	void parse(IrrXMLReader* xml,  IrrlichtDevice* device );


	const char * getExtra(const char * name);
	
	const char * getModel(){ return getExtra("model"); };
	const char * getTexture(){ return getExtra("texture"); };


	E_OBJECT_TYPE type;
	E_SHAPE shape;
	core::list<ObjectRecord*> children;
	btVector3 position;
	btVector3 rotation;
	btVector3 shapeDimensions;
	btScalar mass;
};

