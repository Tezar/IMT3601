//we used a framework for Irrlicj called irrNetLige to help us with the networking

// Include the main irrNet.h header for irrNetLite.
#include <irrNet.h>
#include <iostream>

using namespace irr;

// These pragmas are for MSVC users, they ease the linking of librarys.
// "ws2_32.lib" is part of the Windows Platform SDK and must be linked
// in when compiling on windows. On linux/mac machines, these pragmas
// will simply be ignored, and the linking to irrNetLite static lib
// should be performed by a makefile.
#pragma comment(lib, "irrNetLite.lib")
#pragma comment(lib, "ws2_32.lib")

//main network call back for the server
class MyNetCallback : public net::INetCallback
{
private:
	net::INetManager* netManager;
	f32 ant_game;

public:
	MyNetCallback(net::INetManager* netManagerIn) : netManager(netManagerIn) {}
	

	virtual void handlePacket(net::SInPacket& packet)
	{
		//when a packety is recived
		core::stringc str;
		net::SOutPacket opacket;
		//sees if any games are created
		if(ant_game > 0){}else{ant_game = 0;}
		//takes the first line of the packed
		packet >> str;
		if (str == "blue"){
			//blue means that the current client is a first time client
			if(ant_game == 0){
				//if there are no lobbyes, it gets told that
				if(netManager->getConnectionStatus() != net::EICS_FAILED){
					opacket << "No active games!";
					netManager->sendOutPacket(opacket);
					netManager->update();
				}
			}else{
				//if there are some, the name of the lobbys and the nr of them are sent back
				if(netManager->getConnectionStatus() != net::EICS_FAILED){
					opacket << ant_game;
					for(f32 i = 0; ant_game > i; i++){
						opacket << i;
						netManager->sendOutPacket(opacket);
						netManager->update();
					}
				}
			}
		}else{
			if(ant_game != 0){++ant_game;}else{ant_game = 1;}
			//first line tells the user, what the server now sees the client
			//as, so its its client nr
			opacket << "1";
			if(netManager->getConnectionStatus() != net::EICS_FAILED){
				//all the games gets sent
				opacket << ant_game;
				for(int i = 0; ant_game > i; i++){
					opacket << i;
					netManager->sendOutPacket(opacket);
					netManager->update();
				}
			}
		}


	}
};