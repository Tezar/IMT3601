#pragma once
#include <utility>
#include <irrlicht.h>
#include <string>
#include <stdio.h>
#include "btBulletDynamicsCommon.h"

#include "ObjectRecord.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace io;

using namespace std;


typedef map<std::string, ObjectRecord*> ObjectCacheMap;

class ObjectReader
{
public:
	/* create reader with base directory */
	ObjectReader(const char *, IrrlichtDevice* );
	~ObjectReader(void);

	/* get object from cache or read it from file if necessarily */
	ObjectRecord* getObject(const char *);

	/* read object from file if given absolute path*/ 
	ObjectRecord* readObjectFromFile(core::stringc);


	void setBaseDir(const char * dir);

protected:
	core::stringc baseDir;
	IrrlichtDevice* device;

	/* read object from file*/ 
	ObjectRecord* readObject(core::stringc);


	ObjectRecord* parseVehicle(IrrXMLReader*);
	ObjectRecord* parseSegment(IrrXMLReader*);

	//core::list<configCachePair> cache;
	ObjectCacheMap cache;
};

