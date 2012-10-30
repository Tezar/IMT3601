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
	engine->listener = this;
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
	
	//dont need asset manager, irrlich handles it automaticaly
	IAnimatedMesh* CarMesh = smgr->getMesh("../../media/Car - Main Body.obj");
	IAnimatedMesh* WheelMesh = smgr->getMesh("../../media/Wheel.obj");

	if (!CarMesh || !WheelMesh)
	{
		device->drop();
	}
	
	
	for (int nVehicle = 0; nVehicle < engine->numVehicles; nVehicle++){
		IMeshSceneNode* node = smgr->addMeshSceneNode( CarMesh );

		for (int VehicleWheels = 0; VehicleWheels < 4; VehicleWheels++)
		{
			IMeshSceneNode* node = smgr->addMeshSceneNode( WheelMesh );

			assert(node);
	
			node->setMaterialFlag(EMF_LIGHTING, false);
			node->setMaterialTexture( 0, driver->getTexture("../../media/Car - Wheel Texture.bmp") );
		}

		//	Add 4 wheels in correct positions and make them stick to the car.

		assert(node);
	
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialTexture( 0, driver->getTexture("../../media/Car - Main Body Texture.bmp") );

		vehicleNodes[nVehicle] = node;
	}
	
		        // create a particle system

        IParticleSystemSceneNode* ps =
                smgr->addParticleSystemSceneNode(false,vehicleNodes[0]);

        IParticleEmitter* em = ps->createBoxEmitter(
                core::aabbox3d<f32>(-7,0,-7,7,1,7), // emitter size
                core::vector3df(0.0f,0.006f,0.0f),   // initial direction
                8,10,                             // emit rate
                video::SColor(0,0,0,0),       // darkest color
                video::SColor(0,25,255,255),       // brightest color
                800,2000,0,                         // min and max age, angle
                core::dimension2df(1.f,1.f),         // min size
                core::dimension2df(2.f,2.f));        // max size

        ps->setEmitter(em); // this grabs the emitter
        em->drop(); // so we can drop it here without deleting it

        IParticleAffector* paf = ps->createFadeOutParticleAffector();

        ps->addAffector(paf); // same goes for the affector
        paf->drop();

        ps->setScale(core::vector3df(0.1,0.1,0.1));
        ps->setMaterialFlag(video::EMF_LIGHTING, false);
        ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        ps->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);

        IParticleSystemSceneNode* pss =
                smgr->addParticleSystemSceneNode(false,vehicleNodes[1]);

        IParticleEmitter* ems = pss->createBoxEmitter(
                core::aabbox3d<f32>(-7,0,-7,7,1,7), // emitter size
                core::vector3df(0.0f,0.006f,0.0f),   // initial direction
                8,10,                             // emit rate
                video::SColor(0,0,0,0),       // darkest color
                video::SColor(0,25,255,255),       // brightest color
                800,2000,0,                         // min and max age, angle
                core::dimension2df(1.f,1.f),         // min size
                core::dimension2df(2.f,2.f));        // max size

        pss->setEmitter(ems); // this grabs the emitter
        ems->drop(); // so we can drop it here without deleting it

        IParticleAffector* pafs = pss->createFadeOutParticleAffector();

        pss->addAffector(pafs); // same goes for the affector
        pafs->drop();

        pss->setScale(core::vector3df(0.1,0.1,0.1));
        pss->setMaterialFlag(video::EMF_LIGHTING, false);
        pss->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
        pss->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);


	cameraNode = smgr->addCameraSceneNode(0, vector3df(0,10,-10), vector3df(0,5,0));

	debug_createTrackArrows();

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
		
		IMesh* arrowMesh = smgr->addArrowMesh( stringc("arrow")+core::stringc(i),
                                video::SColor(255, 30, 0, 0),
                                video::SColor(255, 200*(1+i), 100*i, 150*i),
                                16,16,
                                2.f, 1.3f,
                                0.1f, 0.6f
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
	cameraNode->setPosition(engine->averagePosition+core::vector3df(-10,20,-10) );
}

void GameRenderer::onBodyMovement(irr::u32 id,const btTransform* transform){

	if( IS_VEHICLE_ID(id)){
		btVector3 pos = transform->getOrigin();
		vector3df posVector = vector3df(pos.x(), pos.y(), pos.z());
		int vid = GET_VEHICLE_ID(id);
		vehicleNodes[vid]->setPosition(posVector);
	}
}
