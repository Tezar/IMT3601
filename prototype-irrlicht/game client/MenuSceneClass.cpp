/*
parts based on irrlich example01
*/
#pragma once
#include "MenuSceneClass.hpp"
#include "GameManagerClass.hpp"
#include "StartMenuUi.h"
#include "EventManager.hpp"

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
    video::IVideoDriver* driver = device->getVideoDriver();
	
	//GUI elements
    IGUIEnvironment* env = device->getGUIEnvironment();
	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("../media/bigfont.png");
    if (font)
            skin->setFont(font);
	context.device = device;
	context.counter = 0;

		
	for (u32 i=0; i<EGDC_COUNT ; ++i)
		{
			SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
			col.setAlpha(200);
			env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
		}

	//Adds all the start buttons
	env->addButton(rect<s32>(100,100,700,100 + 72), 0, GUI_ID_SINGLE_BUTTON,
                    L"Start Single player", L"Starts the single player");
	env->addButton(rect<s32>(100,100 + 80,700,100 + 80 + 72), 0, GUI_ID_MULTY_BUTTON,
                    L"Start Multy Player", L"Starts the multy player");
    env->addButton(rect<s32>(100,100 + 160,700,100 + 160 + 72), 0, GUI_ID_SETTINGS_BUTTON,
                    L"Settings", L"Opens the settings window");
    env->addButton(rect<s32>(100,100 + 240,700,100 + 240 + 72), 0, GUI_ID_QUIT_BUTTON,
                    L"Quit", L"Quits the program");	

}

int MenuSceneClass::onFrame(int toDo){

	return 0;
}


bool MenuSceneClass::onExit()
{
	//removes all used devises
	IrrlichtDevice * device = GameManager::getInstance()->getDevice();
	EventManager::getInstance()->removeEventReceiver(receiver);
	device->getGUIEnvironment()->clear();
	delete receiver;
	return false;
}

