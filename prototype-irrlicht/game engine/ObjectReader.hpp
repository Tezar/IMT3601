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

	/* get object from cache or read it if necessarily */
	ObjectRecord* getObject(const char *);
	void setBaseDir(const char * dir);

protected:
	std::string baseDir;
	IrrlichtDevice* device;

	/* read object from file*/ 
	ObjectRecord* readObject(const char *);

	ObjectRecord* parseVehicle(IrrXMLReader*);
	ObjectRecord* parseSegment(IrrXMLReader*);

	//core::list<configCachePair> cache;
	ObjectCacheMap cache;
};

