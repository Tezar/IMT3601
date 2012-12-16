#include <irrlicht.h>
#include <iostream>

#include "ObjectReader.hpp"
#include "ObjectRecord.hpp"

using namespace irr;
using namespace gui;

#pragma comment(lib, "Irrlicht.lib")

enum
{
	GUI_ID_LOAD_FILE,
	GUI_ID_QUIT,

	GUI_ID_SHOW_TOOLBOX,
};

enum eFileAction
{
	EOF_LOAD_SCENE,
	EOF_LOAD_MODEL,
	EOF_LOAD_TEXTURE,
};

IrrlichtDevice *Device = 0;
core::stringc StartUpModelFile;
core::stringw MessageText;
core::stringw Caption;
scene::IAnimatedMeshSceneNode* Model = 0;
scene::ISceneNode* SkyBox = 0;

scene::ICameraSceneNode * camera = 0;

eFileAction openAction; 


void showInfoBox(core::stringw msg, const core::stringw title)
{
	Device->getGUIEnvironment()->addMessageBox(
		title.c_str(), msg.c_str());
}

//load object itself
void loadObject(ObjectRecord* object)
{
	ISceneManager* smgr = Device->getSceneManager();
	video::IVideoDriver* driver = Device->getVideoDriver();
	ISceneNode * node;
	
	if( object->type != EOT_SEGMENT)
	{

		switch(object->type)
		{
			case EOT_BOX:
				node = smgr->addCubeSceneNode(1.f);
				node->setScale(vector3df(object->shapeDimensions.x(),object->shapeDimensions.y(),object->shapeDimensions.z()));
				break;	//end case EOT_BOX

			default:
				IMesh* model = smgr->getMesh(object->getModel());
				node = smgr->addMeshSceneNode( model );
		}

		const char * texturePath = object->getTexture();
		if(texturePath){
			video::ITexture* texture =  driver->getTexture(texturePath);

			node->setMaterialTexture( 0, texture);
	
			node->getMaterial(0).AmbientColor.set(255,255,255,255);
			node->getMaterial(0).DiffuseColor.set(255,255,255,255);
			node->getMaterial(0).SpecularColor.set(255,255,255,255);
		

			node->setMaterialType(video::EMT_SOLID);
		}
	}

	int size = object->children.size();
	if(size > 0){
		for(core::list<ObjectRecord*>::ConstIterator it = object->children.begin(); it != object->children.end();it++)
		{
			ObjectRecord* child = (*it);
			loadObject(child);
		}
	}
}

void loadScene(core::stringc path)
{
	ObjectReader reader(0, Device);
	ObjectRecord* object = reader.readObjectFromFile(path);

	if(object->type != EOT_SEGMENT)
	{
		showInfoBox(core::stringw("unsupported format"), core::stringw("error"));
		return;
	}


	loadObject(object);

}


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
				break;
			case EMIE_RMOUSE_LEFT_UP:
				camera->setInputReceiverEnabled(false);
				break;
			default:
				break;
			}
		}
		else if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Device->getGUIEnvironment();
			switch(event.GUIEvent.EventType)
			{
			case EGET_MENU_ITEM_SELECTED:
				{
					// a menu item was clicked
					IGUIContextMenu* menu = (IGUIContextMenu*)event.GUIEvent.Caller;
					s32 id = menu->getItemCommandId(menu->getSelectedItem());
					
					switch(id)
					{
					case GUI_ID_LOAD_FILE: // File -> Open Model
						openAction =  EOF_LOAD_SCENE;
						env->addFileOpenDialog(L"Please select a model file to open");
						break;
					case GUI_ID_QUIT: // File -> Quit
						Device->closeDevice();
						break;
					}
					break;
				}
			case EGET_FILE_SELECTED:
				{
					switch(openAction)
					{
					case EOF_LOAD_SCENE:
						{
							IGUIFileOpenDialog* dialog = (IGUIFileOpenDialog*)event.GUIEvent.Caller;
							loadScene(core::stringc(dialog->getFileName()).c_str());

						}
						break;
					default:

						break;
					}

					break;
				}
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case GUI_ID_LOAD_FILE:
					env->addFileOpenDialog(L"Please select a model file to open");
					break;
				case GUI_ID_SHOW_TOOLBOX:
					createToolBox();
					break;
				}
				break;
			}
		}
		return false;
	}
};





int main()
{
	// create device and exit if creation failed

	MyEventReceiver receiver;
	Device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800, 600),
		16, false, false, false, &receiver);

	if (Device == 0)
		return 1;  // could not create selected driver.

	Device->setResizable(true);
	Device->setWindowCaption(L"Irrlicht Engine - Loading...");

	video::IVideoDriver* driver = Device->getVideoDriver();
	IGUIEnvironment* env = Device->getGUIEnvironment();
	scene::ISceneManager* smgr = Device->getSceneManager();

	// create menu
	gui::IGUIContextMenu* menu = env->addMenu();
	menu->addItem(L"File", -1, true, true);

	gui::IGUIContextMenu* submenu;
	submenu = menu->getSubMenu(0);
	submenu->addItem(L"Open Model File...", GUI_ID_LOAD_FILE);
	submenu->addSeparator();
	submenu->addItem(L"Quit", GUI_ID_QUIT);

	// create toolbar
	gui::IGUIToolBar* bar = env->addToolBar();
	bar->addButton(GUI_ID_LOAD_FILE, 0,0, driver->getTexture("../media/editor/open.png"));

	// disable alpha
	for (s32 i=0; i<gui::EGDC_COUNT ; ++i)
	{
		video::SColor col = env->getSkin()->getColor((gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(255);
		env->getSkin()->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
	}

	// add a tabcontrol
	//createToolBox();


	// create fps text 
	IGUIStaticText* fpstext =
		env->addStaticText(L"", core::rect<s32>(210,26,270,41), true);

	// set window caption
	Caption += " - [";
	Caption += driver->getName();
	Caption += "]";
	Device->setWindowCaption(Caption.c_str());


	smgr->setAmbientLight(video::SColor(255,200,200,200));

	// add a camera scene node 
	camera = smgr->addCameraSceneNodeFPS(0,100.0F, 0.2F);
	camera->setTarget(core::vector3df(0,2,1));

	smgr->addCubeSceneNode()->setPosition(core::vector3df(10,0,0));
	
	// draw everything
	while(Device->run() && driver)
		if (Device->isWindowActive())
		{
			driver->beginScene(true, true, video::SColor(150,50,50,50));
			smgr->drawAll();
			env->drawAll();
		
			driver->endScene();

			core::stringw str = L"FPS: ";
			str += driver->getFPS();
			fpstext->setText(str.c_str());
		}
	Device->drop();
	return 0;
}
