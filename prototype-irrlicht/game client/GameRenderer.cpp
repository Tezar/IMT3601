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

	smgr->addLightSceneNode(0, core::vector3df(0,0,0),
				video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);

	smgr->setAmbientLight(video::SColorf(0.9,0.9,0.9,1));
}

void GameRenderer::debug_createTrackArrows()
{
	debug_clearTrackArrows();	//first we clear all previous

	ISceneManager* smgr = device->getSceneManager();

	IMeshSceneNode* node;
	IMeshSceneNode* previousNode = 0;


	core::list<TrackSegment*>* segments = engine->getSegments();
	int i=0;
	for(core::list<TrackSegment*>::ConstIterator segment_iterator = segments->begin(); segment_iterator != segments->end(); segment_iterator++)
	{
		//memmory leak but its only for debugging so dont worry for now...
		IMesh* arrowMesh = smgr->addArrowMesh( stringc("arrow")+core::stringc(i),
                                video::SColor(255, 30, 0, 0),
                                video::SColor(255, 200*(1+i), 100*i, 150*i),
                                16,16,
                                1.f, 0.6f,
                                0.05f, 0.2f
                                );

		i++;

		TrackPointList * track = (*segment_iterator)->getTrack();

		for(TrackPointList::ConstIterator iterator = track->begin(); iterator != track->end();  iterator++)
		{
			node = smgr->addMeshSceneNode(arrowMesh);
			node->setPosition((*iterator)->position);
			node->setRotation(vector3df(((*iterator)->direction+90),0,90));
			node->setMaterialFlag(video::EMF_LIGHTING, false);

			debug_arrows->push_back(node);

		} //end trackpoint loop
	}	//end segment loop
} //end method

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
	/*
	for (int nVehicle = 0; nVehicle < engine->numVehicles; nVehicle++){
		vehicleNodes[nVehicle]->setPosition(engine->vehicles[nVehicle]->position);
	}*/

	cameraNode->setTarget(engine->averagePosition);
	//put camera on steady altitude, slighty offseted on X axis
	vector3df cameraPosition = engine->averagePosition+core::vector3df(-10,0,-5) ;
	cameraPosition.Y = -5;
	cameraNode->setPosition(cameraPosition);
}


void GameRenderer::onBodyNew(btRigidBody* body, ObjectRecord* config)
{
	ISceneManager* smgr = device->getSceneManager();
	IVideoDriver* driver = device->getVideoDriver();

	ISceneNode* node;

	switch(config->type)
	{
	
	case EOT_BOX:
		{

		//node =  smgr->addEmptySceneNode();
			
		node = smgr->addCubeSceneNode(1.f);
		node->setScale(vector3df(config->shapeDimensions.x(),config->shapeDimensions.y(),config->shapeDimensions.z()));
		//node->setPosition(vector3df(config->shapeDimensions.x(),config->shapeDimensions.y(),config->shapeDimensions.z())*(-0.5));

		} break;	//end case EOT_BOX

	default:

		IMesh* model = smgr->getMesh(config->model);
		node = smgr->addMeshSceneNode( model );

		if(config->texture != 0){
			node->setMaterialTexture( 0, driver->getTexture(config->texture) );
		}
	}

	node->setMaterialFlag(EMF_LIGHTING, true);
	node->getMaterial(0).SpecularColor.set(0,0,1,1);

	

	body->setUserPointer( (void*) node );
}

void GameRenderer::onBodyUpdate(btRigidBody* body, const btTransform& transform)
{
	ISceneNode* node = (ISceneNode*) body->getUserPointer( );

	irr::core::matrix4 matr;
	transform.getOpenGLMatrix(matr.pointer());

	node->setPosition( matr.getTranslation() );
	node->setRotation( matr.getRotationDegrees() );
}

void GameRenderer::onBodyDelete(btRigidBody* body )
{
	ISceneNode* node = (ISceneNode*) body->getUserPointer( );
	node->remove();
}


/*
void GameRenderer::onVehicleMovement(irr::u32 id,Vehicle* vehicle)
{
	vehicleNodes[id]->setPosition(vehicle->position);
	//todo:rotation
}


void GameRenderer::afterSegmentLoaded(TrackSegment * segment) {
	
	debug_createTrackArrows();

	ISceneManager* smgr = device->getSceneManager();

	segment->injectTrackNode(device);

}
*/
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