#pragma once
#include "GameManagerClass.hpp"


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
        IrrlichtDevice *device;
        s32	counter;
        IGUIListBox*    listbox;
};

// Define some values that we'll use to identify individual GUI controls.
enum
{
        GUI_ID_QUIT_BUTTON = 101,
        GUI_ID_START_BUTTON,
        GUI_ID_SETTINGS_BUTTON,
		GUI_ID_GAME_ENGINE_BUTTON,
		GUI_ID_AUDIO_BUTTON,
		GUI_ID_HOTKEY_BUTTON,
};

class MyEventReceiver : public IEventReceiver
{
public:
        MyEventReceiver(SAppContext & context) : Context(context) { }

        virtual bool OnEvent(const SEvent& event)
        {
                if (event.EventType == EET_GUI_EVENT)
                {
                        s32 id = event.GUIEvent.Caller->getID();
                        IGUIEnvironment* env = Context.device->getGUIEnvironment();

                        switch(event.GUIEvent.EventType)
                        {
						case EGET_BUTTON_CLICKED:
                                switch(id)
                                {
                                case GUI_ID_QUIT_BUTTON:
                                        Context.device->closeDevice();
                                        return true;

                                case GUI_ID_START_BUTTON:
                                        {
											GameManager::getInstance()->changeState(practiceGame);
											return 0;
                                        }
                                        return true;

                                case GUI_ID_SETTINGS_BUTTON:
									{
                                        IGUIWindow* window = env->addWindow(
                                                rect<s32>(100, 50, 550, 400),
                                                false,
												L"Settings");

										env->addButton(rect<s32>(50, 20 + 20 + 0, 400, 100 + 0), window, GUI_ID_GAME_ENGINE_BUTTON,
										L"Game settings", L"Opens the game settings window");

										env->addButton(rect<s32>(50, 20 + 20 + 80, 400, 100 + 80), window, GUI_ID_AUDIO_BUTTON,
										L"Audio settings", L"Opens the audio settings window");

										env->addButton(rect<s32>(50, 20 + 20 + 160, 400, 100 + 160), window, GUI_ID_HOTKEY_BUTTON,
										L"Hotkey menu", L"Opens the Hotkey menu window");

                                        //env->addStaticText(L"Please close me",
                                        //        rect<s32>(35,35,140,50),
                                        //        false, // border?
                                        //        true, // wordwrap?
                                        //        window);
									}
										return true;

                                default:
                                        return false;
                                }
                                break;

                        default:
                                break;
                        }
                }

                return false;
        }

private:
        SAppContext & Context;
};