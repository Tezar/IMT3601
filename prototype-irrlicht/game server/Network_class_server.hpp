/*
Welcome to the simple, introductory tutorial for irrNetLite. This will show you the
very basics of setting up a client and server, and sending and receiving packets.
Because irrNetLite is so easy to use, I think you will not find many actual lines of
code in this example, rather most of it is documentation.

For much more sophisticated use of irrNetLite, I recommend taking a look in the 
examples subdirectory.
*/

// Include the main irrNet.h header for irrNetLite.
#include <irrNet.h>
#include <iostream>

// irrNetLite resides within the irr::net:: namespace, therefore,
// we use "using namespace irr" here to simplify things.
// Alternatively you can add "using namespace net" after
// this so that net:: doesn't have to be used either.
using namespace irr;

// These pragmas are for MSVC users, they ease the linking of librarys.
// "ws2_32.lib" is part of the Windows Platform SDK and must be linked
// in when compiling on windows. On linux/mac machines, these pragmas
// will simply be ignored, and the linking to irrNetLite static lib
// should be performed by a makefile.
#pragma comment(lib, "irrNetLite.lib")
#pragma comment(lib, "ws2_32.lib")

// You must derive a class from INetCallback and override the
// "handlePacket" method. When a packet is received it will be
// passed to this function, and you may dissect it as you wish.
// If this is the server you may retrieve the player ID using
// packet.getPlayerId().
class MyNetCallback : public net::INetCallback
{
private:
	net::INetManager* netManager;
	int ant_game;

public:
	MyNetCallback(net::INetManager* netManagerIn) : netManager(netManagerIn) {}

	virtual void handlePacket(net::SInPacket& packet)
	{
		ant_game = 0;
		core::stringc str;
		packet >> str;
		net::SOutPacket opacket;
		if (str == "blue"){
			if(ant_game == 0){
				if(netManager->getConnectionStatus() != net::EICS_FAILED){
					//outPacket << "No active games!";
					opacket << "blue";
					netManager->sendOutPacket(opacket);
					netManager->update();
				}
			}else{
				if(netManager->getConnectionStatus() != net::EICS_FAILED){
					for(int i = 0; ant_game > i; i++){
						opacket << i;
						netManager->sendOutPacket(opacket);
						netManager->update();
					}
				}
			}
		}


	}
};