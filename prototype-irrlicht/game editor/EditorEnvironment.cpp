#include "EditorEnvironment.hpp"


EditorEnvironmentClass::EditorEnvironmentClass()
{
}

void EditorEnvironmentClass::populate(){
	IGUIEnvironment* env = device->getGUIEnvironment();
	video::IVideoDriver* driver = device->getVideoDriver();

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
}


EditorEnvironmentClass::~EditorEnvironmentClass(void)
{
}


bool EditorEnvironmentClass::handleEvent(const SEvent& event)
{
	if (event.EventType != EET_GUI_EVENT) return false;

	s32 id = event.GUIEvent.Caller->getID();
	IGUIEnvironment* env = device->getGUIEnvironment();

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
				showLoadSceneDialog();
				break;
			case GUI_ID_QUIT: // File -> Quit
				device->closeDevice();
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
			showLoadSceneDialog();
			break;
		case GUI_ID_SHOW_TOOLBOX:
			//createToolBox();
			break;
		}
		break;
	}
	
	return false;
}


void EditorEnvironmentClass::showLoadSceneDialog()
{
	IGUIEnvironment* env = device->getGUIEnvironment();
	openAction =  EOF_LOAD_SCENE;
	env->addFileOpenDialog(L"Please select a model file to open", true, 0, -1, false, "../config/");
}



void EditorEnvironmentClass::loadScene(core::stringc path)
{
	ObjectReader reader(0, device);
	ObjectRecord* object = reader.readObjectFromFile(path);

	if(object->type != EOT_SEGMENT)
	{
		showInfoBox(core::stringw("unsupported format"), core::stringw("error"));
		return;
	}

	//GameObjectManager::getInstance()->clear();
	GameObjectManager::getInstance()->load(object);

}



void EditorEnvironmentClass::showInfoBox(core::stringw msg, const core::stringw title)
{
	device->getGUIEnvironment()->addMessageBox(
		title.c_str(), msg.c_str());
}