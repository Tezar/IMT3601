#pragma once
#include <irrlicht.h>
#include <iostream>
#include <Singleton.hpp>

#include "Toolbox.hpp"
#include "ObjectReader.hpp"
#include "ObjectRecord.hpp"
#include "GameObjectManager.hpp"

using namespace irr;
using namespace gui;


enum
{
	GUI_ID_LOAD_FILE,
	GUI_ID_QUIT,

	GUI_ID_SHOW_TOOLBOX,

	GUI_TOOLBOX_WINDOWS_ID,
	GUI_TOOLBOX_SET,

	//make sure there is always enough space for each items
	GUI_TOOLBOX_ITEMS=6969,
};


enum eFileAction
{
	EOF_LOAD_SCENE,
	EOF_LOAD_MODEL,
	EOF_LOAD_TEXTURE,
};

class EditorEnvironmentClass
{
protected:
	IrrlichtDevice *device;

	//which action we are going to execute after load dialog is closed
	eFileAction openAction; 
	ToolBox* currentToolbox;
public:
	EditorEnvironmentClass();
	~EditorEnvironmentClass(void);

	bool handleEvent(const SEvent&);

	//creates all the gui elements
	void populate();

	void showLoadSceneDialog();

	void loadScene(core::stringc path);

	

	void showInfoBox(core::stringw msg, const core::stringw title);
	void createToolBox(ISceneNode *);

	IGUIEnvironment* getGUI();

	void setDevice(IrrlichtDevice* d){ device = d;};
	IrrlichtDevice* getDevice(){ return device;};
};



typedef Singleton<EditorEnvironmentClass> EditorEnvironment;   // Global declaration 