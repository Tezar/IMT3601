// Irrlicht prototype server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Network_class_server.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// Ask the user whether they want to be the server or a client.
	std::cout << "Client (c) or Server (s)?";
	char i;
	std::cin >> i;
	
	// If they typed 's' they are the server else they are the client.
	if(i == 's')
	{
		// Create a server and pass in a new instance of our callback class. The default
		// port that clients can connect to is set to 45000.
		MyNetCallback* netCallback = new MyNetCallback();
		net::INetManager* netManager = net::createIrrNetServer(netCallback);

		// Setting verbose to true makes irrNetLite spit out debug information to the console.
		netManager->setVerbose(true);
		
		// While the connection is active (Not failed), we update the netManager.
		// Note that since this is a server the connection will pretty much always
		// be flagged as active, unless some error occured whilst creating the server.
		// A value of 1000 is passed to update to make it hang for a second and wait for
		// packets to arrive. (Recommended for servers, so you don't busy-loop).
		while(netManager->getConnectionStatus() != net::EICS_FAILED)
			netManager->update(1000);
			
		// Don't forget to clean up!
		delete netManager;
		delete netCallback;
	}
	else
	{
		// Create an irrNet client, in this example we will just connect to the localhost
		// address ("127.0.0.1"), which basically means we are connecting to the same
		// computer the client is on. Note that we just pass a value of 0 as our
		// INetCallback, because the client in this example does no need to handle any
		// packets. You can safely pass a value of 0 if this is the case.
		net::INetManager* netManager = net::createIrrNetClient(0, "127.0.0.1");
		
		// Enable debug messages.
		netManager->setVerbose(true);

		// Here comes the fun part, while the client is connected we update the netManager
		// and ask it to wait 1 second (1000 milliseconds) for new packets to arrive before
		// returning. Since the client in this example doesn't actually receive any packets,
		// the only purpose of the update call is to leave a 1 second interval between each
		// packet we send.
		while(netManager->getConnectionStatus() != net::EICS_FAILED)
		{
			netManager->update(1000);

			// To send a packet, first you create an SOutPacket object.
			net::SOutPacket packet;
			
			// Then you can use the streaming operator << to add new data to it.
			packet << "Help I am stuck on a mountain!";
			
			// You can even chain the << operators like so, just like with ostream.
			packet << core::vector3df(50.0f, 30.0f, 20.0f) << 50.0f;
			
			// Compress the packet, not much to be said.
			packet.compressPacket();
			
			// Encrypt the packet. Note that here we are just using a simple key
			// that is shared among the client and the server. In more sophisticated
			// implementations you may want to generate a random key on the server for
			// each client and send that using a shared key, then use the new key for
			// further communication. Remember that the key should be 16 characters
			// long, and obviously the client and server must share the same key.
			packet.encryptPacket("hushthisissecret");
			
			// A simple call to "sendOutPacket" will send the packet to the server.
			netManager->sendOutPacket(packet);
		}
		
		// When the connection disconnects (Or fails), the loop will terminate.
		// Remember to delete the netManager so that all the low level networking
		// stuff is cleaned up properly.
		delete netManager;
	}
	
	// And we're done, return 0 and make like a tree.
	return 0;
}

