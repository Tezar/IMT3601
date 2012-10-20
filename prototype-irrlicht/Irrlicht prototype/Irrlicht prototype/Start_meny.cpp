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
        s32                             counter;
        IGUIListBox*    listbox;
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
											GameManager::getInstance()->run();
											return 0;
                                        }
                                        return true;

                                case GUI_ID_FILE_OPEN_BUTTON:
                                        Context.listbox->addItem(L"File open");
                                        env->addFileOpenDialog(L"Please choose a file.");
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