#pragma once
#include "PracticeGameScene.hpp"
#include "GameManagerClass.hpp"
#include "Vehicle.hpp"
#include "Controller.hpp"
#include "EventManager.h"

//todo: remove unused
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

using namespace io;
using namespace irr;


PracticeGameScene::PracticeGameScene(void)
{
}


PracticeGameScene::~PracticeGameScene(void)
{
}



void PracticeGameScene::onEnter()
{
	engine = new Engine();
	Vehicle * vehicle1 = engine->addVehicle( new Vehicle() );
	//engine->addVehicle( new Vehicle() );
	
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	receiver = new Controller(vehicle1);
	
	EventManager::getInstance()->addEventReceiver(receiver);	//	Adds a new event receiver to the list, for the controller.

//	device->setEventReceiver(receiver);

	engine->reset();
	
	renderer = new GameRenderer(engine);
	renderer->attach(device);
}

int PracticeGameScene::onFrame(int toDo){

	toDo = engine->step(toDo);

	renderer->update();
	
	return toDo;
}


bool PracticeGameScene::onExit()
{
	EventManager::getInstance()->removeEventReceiver(receiver);
	//free this scene after exit
	return true;
}

