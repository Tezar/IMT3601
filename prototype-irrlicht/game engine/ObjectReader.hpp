#pragma once
#include <utility>
#include <irrlicht.h>
#include <string>
#include <stdio.h>

using namespace irr;
using namespace core;
using namespace io;

using namespace std;

enum E_OBJECT_TYPE{
	EOT_BOX,
	EOT_SPHERE,
	EOT_MESH,

	EOT_VEHICLE,
	EOT_CHASSIS,
	EOT_WHEEL,
	
};


class ObjectRecord
{
public:
	ObjectRecord(){
		physics = true; collisionBox = 0;
	
	}
	~ObjectRecord(){
		if(collisionBox) delete collisionBox; 
	};

	io::path model;
	io::path texture;
	
	E_OBJECT_TYPE type;
	bool physics;

	core::list<ObjectRecord*> children;
	aabbox3df* collisionBox;
	vector3df position;
	vector3df rotation;
	vector3df scale;
	vector3df extra;
	

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
	list<ObjectRecord*> getObjects(const char *);
	void setBaseDir(const char * dir);

protected:
	std::string baseDir;

	/* read object from file*/ 
	list<ObjectRecord*> readObjects(const char *);

	ObjectRecord* parseVehicle(IrrXMLReader*);

	void readVec3d(const char * data, vector3df target);

	//core::list<configCachePair> cache;
	ObjectCacheMap cache;
};

