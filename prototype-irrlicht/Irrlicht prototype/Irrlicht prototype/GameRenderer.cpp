#include <assert.h>
#include "GameRenderer.hpp"
#include "GameManagerClass.hpp"

//todo: remove unused
using namespace core;
using namespace scene;
using namespace video;


IAnimatedMesh* GameRenderer::debug_arrowMesh = 0;

GameRenderer::GameRenderer(Engine* e)
{
	engine = e;
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
}

void GameRenderer::debug_createTrackArrows()
{
	ISceneManager* smgr = device->getSceneManager();

	if(!debug_arrowMesh){	//arrowMesh is static and shared amnog all instances...
		debug_arrowMesh = smgr->addArrowMesh( "Arrow",
                                video::SColor(255, 255, 0, 0),
                                video::SColor(255, 0, 255, 0),
                                16,16,
                                2.f, 1.3f,
                                0.1f, 0.6f
                                );
	}
}

void GameRenderer::debug_clearTrackArrows()
{
	if(debug_arrows == 0) return;


	debug_arrows = new list<IMeshSceneNode>();
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


