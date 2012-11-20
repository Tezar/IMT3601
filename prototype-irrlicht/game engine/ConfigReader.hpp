#pragma once
#include <utility>
#include <irrlicht.h>
using namespace irr;
using namespace core;

using namespace std;


enum E_OBJECT_TYPE{
	EOT_BOX,
	EOT_SPHERE,
	EOT_MESH,
};

class ObjectRecord
{
public:
	ObjectRecord(){ mesh = 0; texture = 0; physics = false; collisionBox = 0; }
	~ObjectRecord(){ if(collisionBox) delete collisionBox; };

	char * mesh;
	char * texture;
	
	E_OBJECT_TYPE type;
	aabbox3df* collisionBox;
	vector3df position;
	vector3df rotation;
	vector3df scale;
	bool physics;

};

class ObjectReader
{
public:
	/* create reader with base directory */
	ObjectReader(const	char *);
	~ObjectReader(void);

	list<ObjectRecord>* getObjects(const char *);


protected:
	list<std::pair<const char *, list<ObjectRecord> > > cache;
	 
	



};

