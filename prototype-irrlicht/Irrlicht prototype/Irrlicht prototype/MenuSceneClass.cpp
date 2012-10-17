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

    IrrlichtDevice * device = GameManager::getInstance()->getDevice();

	
	context.device = device;
	context.counter = 0;
	context.listbox = 0;

	receiver = new MyEventReceiver(context);
	
	device->setEventReceiver(receiver);

        video::IVideoDriver* driver = device->getVideoDriver();
        IGUIEnvironment* env = device->getGUIEnvironment();
		IGUISkin* skin = env->getSkin();

        skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
		env->addButton(rect<s32>(200,100,460,100 + 72), 0, GUI_ID_START_BUTTON,
                        L"Start Program", L"Starts the program");
        env->addButton(rect<s32>(200,180,460,180 + 72), 0, GUI_ID_SETTINGS_BUTTON,
                        L"Settings", L"Opens the settings window");
        env->addButton(rect<s32>(200,260,460,260 + 72), 0, GUI_ID_QUIT_BUTTON,
                        L"Quit", L"Quits the program");

}

int MenuSceneClass::onFrame(int toDo){
	//in other scenes there should be things like letting engine process things and so on

	//consume everything
	return 0;
}


bool MenuSceneClass::onExit()
{
	delete receiver;
	return false;
}

