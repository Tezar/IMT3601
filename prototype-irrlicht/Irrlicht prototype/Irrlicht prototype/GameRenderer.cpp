#include <assert.h>
#include "GameRenderer.hpp"
#include "GameManagerClass.hpp"

//todo: remove unused
using namespace core;
using namespace scene;
using namespace video;

//we have to define it here, or else compilator will fail (because of static nature of this var)
IMesh* GameRenderer::debug_arrowMesh = 0;

GameRenderer::GameRenderer(Engine* e)
{
	engine = e;
	debug_arrows = 0;
}

GameRenderer::~GameRenderer(void)
{
}



void GameRenderer::attach(IrrlichtDevice * attachTo)
{
	device = attachTo;
	ISceneManager* smgr = device->getSceneManager();
	
	//dont need asset manager, irrlich handles it automaticaly
	IAnimatedMesh* mesh = smgr->getMesh("../../media/low.obj");

	if (!mesh)
	{
		device->drop();
	}

	
	for (int nVehicle = 0; nVehicle < engine->numVehicles; nVehicle++){
		IMeshSceneNode* node = smgr->addMeshSceneNode( mesh );

		assert(node);
	
		node->setMaterialFlag(EMF_LIGHTING, false);

		vehicleNodes[nVehicle] = node;
	}

	cameraNode = smgr->addCameraSceneNode(0, vector3df(0,10,-10), vector3df(0,5,0));

	debug_createTrackArrows();

}

void GameRenderer::debug_createTrackArrows()
{
	debug_clearTrackArrows();	//first we clear all previous

	ISceneManager* smgr = device->getSceneManager();

	//secure mesh for us
	if(!debug_arrowMesh) 	//arrowMesh is static and shared amnog all instances...
	{
		debug_arrowMesh = smgr->addArrowMesh( "Arrow",
                                video::SColor(255, 255, 0, 0),
                                video::SColor(255, 0, 255, 0),
                                16,16,
                                2.f, 1.3f,
                                0.1f, 0.6f
                                );
	}

	std::list<TrackPoint*> track = engine->getTrack();
	IMeshSceneNode* node;
	

	for(std::list<TrackPoint*>::const_iterator iterator = track.begin(); iterator != track.end();  iterator++)
	{
		node = smgr->addMeshSceneNode(debug_arrowMesh);
		node->setPosition((*iterator)->position);
		node->setRotation(vector3df(0,0,270));
		debug_arrows->push_back(node);
	}



}

void GameRenderer::debug_clearTrackArrows()
{
	if(debug_arrows == 0){
		debug_arrows = new core::list<IMeshSceneNode*>();
		return;
	}

	for (core::list<IMeshSceneNode*>::ConstIterator iterator = debug_arrows->begin(), end = debug_arrows->end(); iterator != end; ++iterator) {
		(*iterator)->remove();
	}
	
	debug_arrows->clear();

	
}


void GameRenderer::detach()
{

}


void GameRenderer::update()
{

	for (int nVehicle = 0; nVehicle < engine->numVehicles; nVehicle++){
		vehicleNodes[nVehicle]->setPosition(engine->vehicles[nVehicle]->position);
	}

	cameraNode->setTarget(engine->averagePosition);
	
}


