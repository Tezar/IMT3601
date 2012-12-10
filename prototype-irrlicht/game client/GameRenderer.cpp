#include <assert.h>
#include "GameRenderer.hpp"
#include "GameManagerClass.hpp"

//todo: remove unused
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;



GameRenderer::GameRenderer(Engine* e)
{
	engine = e;
	engine->addObserver(this);
	debug_arrows = 0;
}

GameRenderer::~GameRenderer(void)
{
}



void GameRenderer::attach(IrrlichtDevice * attachTo)
{
	device = attachTo;
	ISceneManager* smgr = device->getSceneManager();
	IVideoDriver* driver = device->getVideoDriver();
	

    // create a particle system
	//todo: make list of vehicle nodes
	//createPointParticle(vehicleNodes[0],25,255,255);
	//	createPointParticle(vehicleNodes[1],255,255,25);
		
	cameraNode = smgr->addCameraSceneNode(0, vector3df(0,10,-10), vector3df(0,5,0));
	
	smgr->addLightSceneNode(cameraNode, core::vector3df(1,1,-1),
				video::SColorf(1.0f, 0.6f, 0.7f, 0.5f), 50.0f);
				
	 smgr->setAmbientLight(video::SColor(255,60,60,60));
}


void GameRenderer::detach()
{
	//todo:
}

void GameRenderer::update()
{
	/*
	for (int nVehicle = 0; nVehicle < engine->numVehicles; nVehicle++){
		vehicleNodes[nVehicle]->setPosition(engine->vehicles[nVehicle]->position);
	}*/

	cameraNode->setTarget(engine->averagePosition);
	//put camera on steady altitude, slighty offseted on X axis

	cameraNode->setPosition(calculateCameraPosition(engine->averagePosition));
}

vector3df GameRenderer::calculateCameraPosition(vector3df& averagePosition)
{
	//todo: calculate elevation so everyone is visible
	vector3df cameraPosition = averagePosition+core::vector3df(-1,0,-3) ;
	cameraPosition.Y = 15;
	return cameraPosition;
}


void GameRenderer::onShapeNew(btCollisionShape* shape, ObjectRecord* config)
{
	ISceneManager* smgr = device->getSceneManager();
	IVideoDriver* driver = device->getVideoDriver();

	IMeshSceneNode* node;
	ISceneNode* parent = 0;

	//compound shape is used to offset shape from body
	//only one child is used
	if( shape->isCompound() )
	{
		//we create parent node which will be then moved
		parent = smgr->addEmptySceneNode();
	}


	switch(config->type)
	{
		case EOT_BOX:
			node = smgr->addCubeSceneNode(1.f, parent);
			node->setScale(vector3df(config->shapeDimensions.x(),config->shapeDimensions.y(),config->shapeDimensions.z()));
			break;	//end case EOT_BOX

		default:
			IMesh* model = smgr->getMesh(config->getModel());
			node = smgr->addMeshSceneNode( model , parent);
	}

	const char * texturePath = config->getTexture();
	if(texturePath){
		ITexture* texture =  driver->getTexture(texturePath);

		node->setMaterialTexture( 0, texture);
	
		node->getMaterial(0).AmbientColor.set(255,255,255,255);
		node->getMaterial(0).DiffuseColor.set(255,255,255,255);
		node->getMaterial(0).SpecularColor.set(255,255,255,255);
		

		node->setMaterialType(EMT_SOLID);
	}


	const char * bumbPath = config->getExtra("bump");
	if(bumbPath){
		ITexture* normalMap =  driver->getTexture(bumbPath); 
		driver->makeNormalMapTexture(normalMap, 9.0f);
		node->setMaterialTexture(1, normalMap);

		node->setMaterialType(EMT_PARALLAX_MAP_SOLID);
	}


	node->addShadowVolumeSceneNode();
	node->setMaterialFlag(EMF_LIGHTING, true);


	//if this is compound shape we offset node inside the parent node
	//only first child is considered!
	if( shape->isCompound() )
	{
		btCompoundShape* compound = (btCompoundShape*) shape;

		irr::core::matrix4 matr;
		compound->getChildTransform(0).getOpenGLMatrix(matr.pointer());

		node->setPosition(  matr.getTranslation() );
		node->setRotation( matr.getRotationDegrees() );
	}

	shape->setUserPointer( (void*) (parent ? parent : node) );
}

void GameRenderer::onShapeUpdate(btCollisionShape* shape, const btTransform& transform)
{
	ISceneNode* node = (ISceneNode*) shape->getUserPointer( );

	irr::core::matrix4 matr;
	transform.getOpenGLMatrix(matr.pointer());
	

	node->setPosition(  matr.getTranslation() );
	node->setRotation( matr.getRotationDegrees() );
}

void GameRenderer::onShapeDelete(btCollisionShape* shape )
{
	ISceneNode* node = (ISceneNode*) shape->getUserPointer( );
	node->remove();
}



void GameRenderer::createPointParticle(IMeshSceneNode * vehicleNodes,int red,int green,int blue) {
    
	ISceneManager* smgr = device->getSceneManager();

	IParticleSystemSceneNode* pss =
		smgr->addParticleSystemSceneNode(false,vehicleNodes);

    IParticleEmitter* ems = pss->createPointEmitter(
                /*core::aabbox3d<f32>(-7,0,-7,7,1,7), // emitter size*/
                core::vector3df(0.0f,0.006f,0.0f),   // initial direction
                8,10,                             // emit rate
                video::SColor(0,0,0,0),       // darkest color
                video::SColor(0,red,green,blue),       // brightest color /red,green,blue
                800,2000,0,                         // min and max age, angle
                core::dimension2df(1.f,1.f),         // min size
                core::dimension2df(2.f,2.f));        // max size
	
	pss->setEmitter(ems); // this grabs the emitter
    ems->drop(); // so we can drop it here without deleting it
    IParticleAffector* pafs = pss->createFadeOutParticleAffector();

    pss->addAffector(pafs); // same goes for the affector
    pafs->drop();
	
    pss->setScale(core::vector3df(0.1,0.1,0.1)); // size of squares
	pss->setParticleSize(dimension2d<f32>((0.5f), (0.5f)));
    pss->setMaterialFlag(video::EMF_LIGHTING, false);
    pss->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    pss->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
}