#include <irrlicht.h>
#include <iostream>

#include "ObjectReader.hpp"
#include "ObjectRecord.hpp"
#include "GameObjectManager.hpp"
#include "EditorEnvironment.hpp"

using namespace irr;
using namespace gui;

#pragma comment(lib, "Irrlicht.lib")




enum eMouseMode
{
	EMM_SELECT,
	EMM_CAMERA,
	EMM_RULE42,
};


IrrlichtDevice *Device = 0;


scene::ICameraSceneNode * camera = 0;

//which node is highligted, so we can disable that
ISceneNode * highlighted = 0;


//which action we are going to execute after load dialog is cloed
eMouseMode mouseMode; 


void createToolBox()
{
	// remove tool box if already there
	IGUIEnvironment* env = Device->getGUIEnvironment();
	IGUIElement* root = env->getRootGUIElement();
	IGUIElement* e = root->getElementFromId(5000, true);
	if (e) e->remove();

	// create the toolbox window
	IGUIWindow* wnd = env->addWindow(core::rect<s32>(450,25,640,480),
		false, L"Toolset", 0, 5000);

	// create tab control and tabs
	IGUITabControl* tab = env->addTabControl(
		core::rect<s32>(2,20,640-452,480-7), wnd, true, true);
	IGUITab* t1 = tab->addTab(L"Scale");
	IGUITab* t2 = tab->addTab(L"Empty Tab");

	// add some edit boxes and a button to tab one
	env->addEditBox(L"1.0", core::rect<s32>(40,50,130,70), true, t1, 901);
	env->addEditBox(L"1.0", core::rect<s32>(40,80,130,100), true, t1, 902);
	env->addEditBox(L"1.0", core::rect<s32>(40,110,130,130), true, t1, 903);
	env->addButton(core::rect<s32>(10,150,100,190), t1, 1101, L"set");

}


class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_MOUSE_INPUT_EVENT)
		{
			//when right clicked enable camera
			switch(event.MouseInput.Event)
			{
			case EMIE_RMOUSE_PRESSED_DOWN:
				camera->setInputReceiverEnabled(true);
				Device->getCursorControl()->setVisible(false);
				break;
			case EMIE_RMOUSE_LEFT_UP:
				camera->setInputReceiverEnabled(false);
				Device->getCursorControl()->setVisible(true);
				break;
			case EMIE_LMOUSE_PRESSED_DOWN:{
				core::position2di cursor = core::position2di(event.MouseInput.X, event.MouseInput.Y);
				scene::ISceneCollisionManager *collisionManager = Device->getSceneManager()->getSceneCollisionManager();
				scene::ISceneNode *sceneNode = collisionManager->getSceneNodeFromScreenCoordinatesBB(cursor);

				//we hit nothing
				if(sceneNode == 0) break;
				//we hit something without id
				if(sceneNode->getID() == 0) break;

				//we already highligted this node
				if(highlighted == sceneNode ) break;
				
				int id = sceneNode->getID();
				//it's not managed node
				if(	id < 0) break;
				
				if(highlighted != 0) highlighted->setDebugDataVisible(EDS_OFF);
				highlighted = sceneNode;
				highlighted->setDebugDataVisible(EDS_BBOX | EDS_MESH_WIRE_OVERLAY | EDS_BBOX_BUFFERS | EDS_HALF_TRANSPARENCY );
				createToolBox();
				

				}
				break;
			default:
				break;
			}
		}
		else if (event.EventType == EET_GUI_EVENT)
		{
			return EditorEnvironment::getInstance()->handleEvent(event);
		}
		return false;
	}
};





int main()
{
	// create device and exit if creation failed
	MyEventReceiver receiver;
	Device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800, 600),
		16, false, true, false, &receiver);

	if (Device == 0)
		return 1;  // could not create selected driver.

	Device->setResizable(true);
	Device->setWindowCaption(L"GameEditor");

	GameObjectManager::getInstance()->setDevice(Device);
	EditorEnvironment::getInstance()->setDevice(Device);
	

	video::IVideoDriver* driver = Device->getVideoDriver();
	scene::ISceneManager* smgr = Device->getSceneManager();

	IGUIEnvironment* env = Device->getGUIEnvironment();	//for drawAll

	//lets create ui
	EditorEnvironment::getInstance()->populate();
	//setting for graphics
	smgr->getParameters()->setAttribute(scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);
	smgr->setAmbientLight(video::SColor(255,200,200,200));

	// add a camera scene node 
	camera = smgr->addCameraSceneNodeFPS(0,100.0F, 0.05F);
	camera->setTarget(core::vector3df(0,2,1));
	camera->setInputReceiverEnabled(false);

	mouseMode = EMM_SELECT;

	// draw everything
	while(Device->run() && driver)
		if (Device->isWindowActive())
		{
			driver->beginScene(true, true, video::SColor(150,50,50,50));
			smgr->drawAll();
			env->drawAll();
			driver->endScene();
		}
	Device->drop();
	return 0;
}
