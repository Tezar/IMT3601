#pragma once
#include <utility>
#include <irrlicht.h>
#include <string>
#include <stdio.h>
#include "btBulletDynamicsCommon.h"

using namespace irr;
using namespace core;
using namespace io;

using namespace std;

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

typedef map<std::string, core::list<ObjectRecord*>> ObjectCacheMap;
typedef std::pair<const char *, core::list<ObjectRecord*> > configCachePair;

class ObjectReader
{
public:
	/* create reader with base directory */
	ObjectReader(const char *);
	~ObjectReader(void);

	/* get object from cache or read it if necessarily */
	list<ObjectRecord*>* getObjects(const char *);
	void setBaseDir(const char * dir);

protected:
	std::string baseDir;

	/* read object from file*/ 
	list<ObjectRecord*>* readObjects(const char *);

	ObjectRecord* parseVehicle(IrrXMLReader*);

	void readVec3d(const char *, btVector3&);
	void readShape(const char *, E_SHAPE&);

	//core::list<configCachePair> cache;
	ObjectCacheMap cache;
};

