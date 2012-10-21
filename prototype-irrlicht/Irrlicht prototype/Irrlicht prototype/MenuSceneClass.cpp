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


MenuSceneClass::MenuSceneClass(void)
{
}

MenuSceneClass::~MenuSceneClass(void)
{
}


void MenuSceneClass::onEnter()
{
	
    IrrlichtDevice * device = GameManager::getInstance()->getDevice();

	receiver = new MyEventReceiver(context);
	
	device->setEventReceiver(receiver);

        video::IVideoDriver* driver = device->getVideoDriver();
        IGUIEnvironment* env = device->getGUIEnvironment();
		IGUISkin* skin = env->getSkin();
		//IGUIListBox * listbox = env->addListBox(rect<s32>(50, 140, 250, 210));

		context.device = device;
		context.counter = 0;
		//context.listbox = listbox;

		
		for (u32 i=0; i<EGDC_COUNT ; ++i)
			{
				SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
				col.setAlpha(200);
				env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
			}


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
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	device->setEventReceiver(0);
	device->getGUIEnvironment()->clear();
	delete receiver;
	return false;
}

