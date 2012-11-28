#pragma once
#include <irrlicht.h>
#include <stdio.h>
#include "btBulletDynamicsCommon.h"

using namespace irr;
using namespace core;
using namespace io;


enum E_OBJECT_TYPE{
	EOT_VEHICLE,
	EOT_CHASSIS,
	EOT_WHEEL,
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
		collisionBox = 0;
		position.setZero();
		rotation.setZero();
	}
	~ObjectRecord(){
		if(collisionBox) delete collisionBox; 
		//todo: iterate and delete children
		
	};


	btCollisionShape* createShape()
	{
		return new btBoxShape(  btVector3(1,1,1) );
	}

	io::path model;
	io::path texture;
	
	E_OBJECT_TYPE type;
	E_SHAPE shape;
	aabbox3df* collisionBox;
	core::list<ObjectRecord*> children;
	btVector3 position;
	btVector3 rotation;
	btVector3 scale;
	btVector3 extra;
	

};