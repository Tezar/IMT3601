#pragma once
#include <irrlicht.h>
#include <Singleton.hpp>

#include "ObjectReader.hpp"
#include "ObjectRecord.hpp"


using namespace irr;
using namespace gui;



class GameObjectManagerClass
{
protected:
	IrrlichtDevice *device;
	unsigned int counter;

	unsigned int nextId(){ return counter++; };

public:
	GameObjectManagerClass(IrrlichtDevice * = 0);

	void clear();
	void load(ObjectRecord* object);

	//todo:
	//load object
	//remove objects
	//save objects
	//get object by id

	~GameObjectManagerClass(void);

	void setDevice(IrrlichtDevice* d){ device = d;};
	IrrlichtDevice* getDevice(){ return device;};
};


typedef Singleton<GameObjectManagerClass> GameObjectManager;   // Global declaration 