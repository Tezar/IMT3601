#include "PracticeGameScene.hpp"
#include "GameManagerClass.hpp"
#include "Vehicle.hpp"

//todo: remove unused
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;



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

	engine->reset();



	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	
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

