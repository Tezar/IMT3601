#include "GameManagerClass.hpp"


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

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
        GUI_ID_FILE_OPEN_BUTTON,
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

/*
This is the main method. We can now use main() on every platform.
//*/
//int main()
//{
//	video::E_DRIVER_TYPE driverType=irr::video::E_DRIVER_TYPE(1); //never put too "0"
//        if (driverType==video::EDT_COUNT)
//                return 1;
//
//        // create device and exit if creation failed
//
//        IrrlichtDevice * device = createDevice(driverType, core::dimension2d<u32>(640, 480));
//
//        if (device == 0)
//                return 1; // could not create selected driver.
//		device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
//        device->setResizable(true);
//
//        video::IVideoDriver* driver = device->getVideoDriver();
//        IGUIEnvironment* env = device->getGUIEnvironment();
//		IGUISkin* skin = env->getSkin();
//        IGUIFont* font = env->getFont("../../media/fonthaettenschweiler.bmp");
//        if (font)
//                skin->setFont(font);
//
//        skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
//		env->addButton(rect<s32>(200,100,460,100 + 72), 0, GUI_ID_START_BUTTON,
//                        L"Start Program", L"Starts the program");
//        env->addButton(rect<s32>(200,180,460,180 + 72), 0, GUI_ID_QUIT_BUTTON,
//                        L"Quit", L"terminates the current program");
//        env->addButton(rect<s32>(200,260,460,260 + 72), 0, GUI_ID_FILE_OPEN_BUTTON,
//                        L"File Open", L"Opens a file");
//		while(device->run() && driver)
//        if (device->isWindowActive())
//        {
//                driver->beginScene(true, true, SColor(0,200,200,200));
//
//                env->drawAll();
//        
//                driver->endScene();
//        }
//
//        device->drop();
//
//        return 0;
//}

/*
That's it. Compile and run.
**/
