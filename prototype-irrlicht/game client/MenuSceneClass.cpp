/*
parts based on irrlich example01
*/
#include "MenuSceneClass.hpp"
#include "GameManagerClass.hpp"
#include "StartMenuUi.h"
#include "EventManager.h"

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
	
	EventManager::getInstance()->addEventReceiver(receiver);
//	device->setEventReceiver(receiver);

        video::IVideoDriver* driver = device->getVideoDriver();
        IGUIEnvironment* env = device->getGUIEnvironment();
		IGUISkin* skin = env->getSkin();
		IGUIFont* font = env->getFont("../media/bigfont.png");
        if (font)
                skin->setFont(font);
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


		env->addButton(rect<s32>(100,100,700,100 + 72), 0, GUI_ID_SINGLE_BUTTON,
                        L"Start Single player", L"Starts the single player");
		env->addButton(rect<s32>(100,100 + 80,700,100 + 80 + 72), 0, GUI_ID_MULTY_BUTTON,
                        L"Start Multy Player", L"Starts the multy player");
        env->addButton(rect<s32>(100,100 + 160,700,100 + 160 + 72), 0, GUI_ID_SETTINGS_BUTTON,
                        L"Settings", L"Opens the settings window");
        env->addButton(rect<s32>(100,100 + 240,700,100 + 240 + 72), 0, GUI_ID_QUIT_BUTTON,
                        L"Quit", L"Quits the program");	

		//env->addButton(rect<s32>(100,340,700,340 + 72), 0, GUI_ID_TEST_BUTTON,
  //                      L"Test partic", L"Tests particle generator");

}

int MenuSceneClass::onFrame(int toDo){
	//in other scenes there should be things like letting engine process things and so on

	//consume everything
	return 0;
}


bool MenuSceneClass::onExit()
{
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	EventManager::getInstance()->removeEventReceiver(receiver);
//	device->setEventReceiver(0);
	device->getGUIEnvironment()->clear();
	delete receiver;
	return false;
}

