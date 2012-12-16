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

	engine->loadSegment( GameManager::getInstance()->getReader()->getObject("boxes") );

	engine->addVehicle( GameManager::getInstance()->getReader()->getObject("vehicle")  );
	engine->addVehicle( GameManager::getInstance()->getReader()->getObject("vehicle")  );
	Vehicle * vehicle1 = engine->addVehicle( GameManager::getInstance()->getReader()->getObject("vehicle")  );
	Vehicle * vehicle2 = engine->addVehicle( GameManager::getInstance()->getReader()->getObject("vehicle")  );

	
	receiver = new Controller(vehicle1, soundDevice, false);

	EventManager::getInstance()->addEventReceiver(receiver);

	receiver = new Controller(vehicle2, soundDevice, true);
	
	EventManager::getInstance()->addEventReceiver(receiver);	//	Adds a new event receiver to the list, for the controller.

	createPointParticle(0,0,0,255,255,25);
	//createPointParticle(1,0,0,255,255,25);
	//createPointParticle(2,0,1,255,255,25);

	

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

/*void GameRenderer::createPointParticle(IMeshSceneNode * vehicleNodes,int red,int green,int blue) {*/
void PracticeGameScene::createPointParticle(int one,int two,int three,int red,int green,int blue) {
    
	IrrlichtDevice *device = GameManager::getInstance()->getDevice();

	ISceneManager* smgr = device->getSceneManager();

	IParticleSystemSceneNode* pss =
		//smgr->addParticleSystemSceneNode(false,vehicleNodes);
		smgr->addParticleSystemSceneNode(false);

    IParticleEmitter* ems = pss->createBoxEmitter(
                core::aabbox3d<f32>(-7,0,-7,7,1,7), // emitter size
                core::vector3df(0.0f,0.06f,0.0f),   // initial direction
                8,100,                             // emit rate
                video::SColor(0,255,255,255),       // darkest color
                video::SColor(0,red,green,blue),       // brightest color /red,green,blue
                800,2000,0,                         // min and max age, angle
                core::dimension2df(10.f,10.f),         // min size
                core::dimension2df(20.f,20.f));        // max size
	
	pss->setEmitter(ems); // this grabs the emitter
    ems->drop(); // so we can drop it here without deleting it
    IParticleAffector* pafs = pss->createFadeOutParticleAffector();

    pss->addAffector(pafs); // same goes for the affector
    pafs->drop();
	
	pss->setPosition(core::vector3df(0,0,0));
    pss->setScale(core::vector3df(2,2,2)); // size of squares
	pss->setParticleSize(dimension2d<f32>((0.5f), (0.5f)));
    pss->setMaterialFlag(video::EMF_LIGHTING, false);
    pss->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	pss->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}