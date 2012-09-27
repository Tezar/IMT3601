#include "GameManagerClass.hpp"


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
