/*
parts based on irrlich example01
*/
#include "MenuSceneClass.hpp"
#include "GameManagerClass.hpp"
#include "StartMenuUi.h"

//todo: remove unused
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace irr;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

MenuSceneClass::MenuSceneClass(void)
{
}

MenuSceneClass::~MenuSceneClass(void)
{
}


void MenuSceneClass::onEnter()
{
	//video::E_DRIVER_TYPE driverType=irr::video::E_DRIVER_TYPE(1); //never put too "0"
        /*if (driverType==video::EDT_COUNT)
                return 1;*/

        // create device and exit if creation failed

        IrrlichtDevice * device = GameManager::getInstance()->getDevice();

        video::IVideoDriver* driver = device->getVideoDriver();
        IGUIEnvironment* env = device->getGUIEnvironment();
		IGUISkin* skin = env->getSkin();

        skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
		env->addButton(rect<s32>(200,100,460,100 + 72), 0, GUI_ID_START_BUTTON,
                        L"Start Program", L"Starts the program");
        env->addButton(rect<s32>(200,180,460,180 + 72), 0, GUI_ID_QUIT_BUTTON,
                        L"Quit", L"terminates the current program");
        env->addButton(rect<s32>(200,260,460,260 + 72), 0, GUI_ID_FILE_OPEN_BUTTON,
                        L"File Open", L"Opens a file");


		//while(device->run() && driver)
  //      if (device->isWindowActive())
  //      {
  //              driver->beginScene(true, true, SColor(0,200,200,200));

  //              env->drawAll();
  //      
  //              driver->endScene();
  //      }

  //      device->drop();

        /*return 0;*/
}

int MenuSceneClass::onFrame(int toDo){
	//in other scenes there should be things like letting engine process things and so on

	//consume everything
	return 0;
}


bool MenuSceneClass::onExit()
{
	return false;
}

