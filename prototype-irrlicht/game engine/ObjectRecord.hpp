#pragma once
#include <irrlicht.h>
#include <stdio.h>
#include "btBulletDynamicsCommon.h"

using namespace irr;
using namespace core;
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
public:
	ObjectRecord(){
		shape = ES_NONE;
		shapeDimensions.setValue(1,1,1);
		position.setZero();
		rotation.setZero();
		mass = 0;
	}
	~ObjectRecord(){
		//todo: iterate and delete children
		
	};


	btCollisionShape* createShape()
	{
		switch(shape)
		{
		case ES_BOX:
			return new btBoxShape( shapeDimensions *0.5 );
		case ES_CYLINDER:
			return new btCylinderShapeX( shapeDimensions  );
		default:
		case ES_NONE:
			return 0;
		}
		
	}

	io::path model;
	io::path texture;
	
	E_OBJECT_TYPE type;
	E_SHAPE shape;
	core::list<ObjectRecord*> children;
	btVector3 position;
	btVector3 rotation;
	btVector3 shapeDimensions;
	btVector3 extra;
	btScalar mass;

	

};