#pragma once
#include <irrlicht.h>
#include <Singleton.hpp>

#include "ObjectReader.hpp"
#include "ObjectRecord.hpp"


using namespace irr;
using namespace gui;


using namespace std;


typedef map<int, ObjectRecord*> nodeDict;


class GameObjectManagerClass
{
protected:
	IrrlichtDevice *device;
	unsigned int counter;

	unsigned int nextId(){ return counter++; };

	//master object which is loaded righ now
	ObjectRecord* masterRecord;

	nodeDict nodesRecord;

public:
	GameObjectManagerClass(IrrlichtDevice * = 0);

	void clear();
	void load(ObjectRecord* object);

	ObjectRecord* getById(int);

	//todo:
	//remove objects
	//save objects
	

	~GameObjectManagerClass(void);

	void setDevice(IrrlichtDevice* d){ device = d;};
	IrrlichtDevice* getDevice(){ return device;};
};


typedef Singleton<GameObjectManagerClass> GameObjectManager;   // Global declaration 