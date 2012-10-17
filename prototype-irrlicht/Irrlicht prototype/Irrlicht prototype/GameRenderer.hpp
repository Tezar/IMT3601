#pragma once
#include <irrlicht.h>
using namespace irr;
using namespace scene;

#include "Engine.hpp"


class GameRenderer
{
private:
	//engine which we are going to render
	Engine* engine;
	IrrlichtDevice* device;

	//array to hold nodes of vehicles
	IMeshSceneNode* vehicleNodes[MAX_VEHICLES];

	//reference to our camera
	ICameraSceneNode* cameraNode;


	//for debugging purposes only
	
	//mesh for our arrow
	static IAnimatedMesh* debug_arrowMesh;
	list<IMeshSceneNode>* debug_arrows;

public:
	/** @par Engine reference to engine which we are going to render **/
	GameRenderer(Engine*);
	~GameRenderer(void);

	/** @par Device to which we should add stuff like nodes and gui*/
	void attach(IrrlichtDevice* );
	/** remove anything we have done to device*/
	void detach();

	void debug_createTrackArrows();
	void debug_clearTrackArrows();

	void update();
};
