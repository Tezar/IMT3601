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

/*
This is the main method. We can now use main() on every platform.
*/
int main()
{
	GameManager::getInstance()->run();
	return 0;	
}

/*
That's it. Compile and run.
**/
