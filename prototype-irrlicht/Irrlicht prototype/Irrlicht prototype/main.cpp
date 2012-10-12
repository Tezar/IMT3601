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

int main()
{
		GameManager::getInstance()->run();
        return 0;
}

/*
That's it. Compile and run.
**/
