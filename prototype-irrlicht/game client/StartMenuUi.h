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
		GUI_ID_SINGLE_BUTTON,
		GUI_ID_MULTY_BUTTON,
		GUI_ID_MULTY_JOIN_BUTTON,
		GUI_ID_MULTY_CREATE_BUTTON,
		GUI_ID_MULTY_BACK_BUTTON,
        GUI_ID_SETTINGS_BUTTON,
		GUI_ID_GAME_ENGINE_BUTTON,
		GUI_ID_AUDIO_BUTTON,
		GUI_ID_HOTKEY_BUTTON,
		GUI_ID_TEST_BUTTON,
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

						//Switch to look for what ui element got clicked
                        switch(event.GUIEvent.EventType)
                        {
						case EGET_BUTTON_CLICKED:
                                switch(id)
                                {
									//kills the program
                                case GUI_ID_QUIT_BUTTON:
                                        Context.device->closeDevice();
                                        return true;

                                case GUI_ID_SINGLE_BUTTON:
                                        {
											//starts the singleplayer mode
											GameManager::getInstance()->changeState(practiceGame);
											return 0;
                                        }
                                        return true;

								case GUI_ID_MULTY_BUTTON:
										{
											//Opens our multiplayer window, were you can see created lobbies
											GameManager::getInstance()->changeState(multiPlayerGame);
											return 0;
										}
										return true;

                                case GUI_ID_SETTINGS_BUTTON:
									{
										//opens a new window, and created new buttons there.
                                        IGUIWindow* settingsWindow = env->addWindow(
                                                rect<s32>(100, 50, 550, 400),
                                                false,
												L"Settings");

										env->addButton(rect<s32>(50, 20 + 20 + 0, 400, 100 + 0), settingsWindow, GUI_ID_GAME_ENGINE_BUTTON,
										L"Game settings", L"Opens the game settings window");

										env->addButton(rect<s32>(50, 20 + 20 + 80, 400, 100 + 80), settingsWindow, GUI_ID_AUDIO_BUTTON,
										L"Audio settings", L"Opens the audio settings window");

										env->addButton(rect<s32>(50, 20 + 20 + 160, 400, 100 + 160), settingsWindow, GUI_ID_HOTKEY_BUTTON,
										L"Hotkey menu", L"Opens the Hotkey menu window");

									}
										return true;

								case GUI_ID_GAME_ENGINE_BUTTON:
									{
										//Video setings, not implemented
                                        IGUIWindow* gameEnginWindow = env->addWindow(
                                                rect<s32>(100, 50, 550, 400),
                                                false,
												L"Game Engine Settings");
									}
										return true;

								case GUI_ID_AUDIO_BUTTON:
									{
										//Audio settings, not implemented
                                        IGUIWindow* audiosWindow = env->addWindow(
                                                rect<s32>(100, 50, 550, 400),
                                                false,
												L"Audio Settings");
									}
										return true;

								case GUI_ID_HOTKEY_BUTTON:
									{
										//keybindings settings, not implemented
                                        IGUIWindow* hotkeyWindow = env->addWindow(
                                                rect<s32>(100, 50, 550, 400),
                                                false,
												L"Hotkey Config");
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