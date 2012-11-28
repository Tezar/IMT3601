#pragma once
#include <utility>
#include <irrlicht.h>
#include <string>
#include <stdio.h>
#include "btBulletDynamicsCommon.h"

#include "ObjectRecord.hpp"

using namespace irr;
using namespace core;
using namespace io;

using namespace std;


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

