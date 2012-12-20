// Irrlicht prototype server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Network_class_server.hpp"


int _tmain(int argc, _TCHAR* argv[])
{
	//main server part, most are handled by irrNetlite beind the scene


		// Create a server and pass in a new instance of our callback class. The default
		// port that clients can connect to is set to 45000.
		net::INetManager* netManager = net::createIrrNetServer(0);
		MyNetCallback* netCallback = new MyNetCallback(netManager);
		netManager->setNetCallback(netCallback);

		// Setting verbose to true makes irrNetLite spit out debug information to the console.
		netManager->setVerbose(true);

		while(netManager->getConnectionStatus() != net::EICS_FAILED)
			netManager->update(1000);
			
		//clean up
		delete netManager;
		delete netCallback;	

	return 0;
}

