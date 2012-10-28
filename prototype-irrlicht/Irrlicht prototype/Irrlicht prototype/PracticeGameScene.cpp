#pragma once
#include "PracticeGameScene.hpp"
#include "GameManagerClass.hpp"
#include "Vehicle.hpp"
#include "Controller.hpp"

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
	engine->addVehicle( new Vehicle() );
	engine->addVehicle( new Vehicle() );
	
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	receiver = new Controller(/* ReferencingTheVehicle */);

	device->setEventReceiver(receiver);

	Controller inputDevice1, inputDevice2;

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
	//free this scene after exit
	return true;
}

