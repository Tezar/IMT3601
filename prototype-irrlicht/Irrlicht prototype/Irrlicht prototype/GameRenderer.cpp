#include <assert.h>
#include "GameRenderer.hpp"
#include "GameManagerClass.hpp"

//todo: remove unused
using namespace core;
using namespace scene;
using namespace video;

GameRenderer::GameRenderer(Engine* e)
{
	engine = e;
}

GameRenderer::~GameRenderer(void)
{
}

void GameRenderer::attach(IrrlichtDevice *)
{
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
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


