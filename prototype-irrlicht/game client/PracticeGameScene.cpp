#pragma once
#include <irrKlang.h>
#include "PracticeGameScene.hpp"
#include "GameManagerClass.hpp"
#include "Vehicle.hpp"
#include "Controller.hpp"
#include "EventManager.hpp"

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
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();


	engine = new Engine();


	//we have to create engine so soon, because otherwise the renderer cant react to creation of new bodies by inserting them to the scene
	renderer = new GameRenderer(engine);
	renderer->attach(device);

	soundDevice = AudioManager::getInstance();
	soundDevice->BackgroundMusic();

	Vehicle * vehicle1 = engine->addVehicle( (*GameManager::getInstance()->getReader()->getObjects("vehicle")->begin()) );
	
	
	receiver = new Controller(vehicle1);
	
	EventManager::getInstance()->addEventReceiver(receiver);	//	Adds a new event receiver to the list, for the controller.

	

//	device->setEventReceiver(receiver);

	engine->reset();
	
	
	
}

int PracticeGameScene::onFrame(int toDo){

	toDo = engine->step(toDo);

	renderer->update();
	
	soundDevice->UpdateListenerPosition(engine);

	return toDo;
}


bool PracticeGameScene::onExit()
{
	EventManager::getInstance()->removeEventReceiver(receiver);
	
	//free this scene after exit
	return true;
}

