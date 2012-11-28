/*
Welcome to the simple, introductory tutorial for irrNetLite. This will show you the
very basics of setting up a client and server, and sending and receiving packets.
Because irrNetLite is so easy to use, I think you will not find many actual lines of
code in this example, rather most of it is documentation.

For much more sophisticated use of irrNetLite, I recommend taking a look in the 
examples subdirectory.
*/

// Include the main irrNet.h header for irrNetLite.
#pragma once
#include <irrNet.h>
#include <iostream>
#include "StartMenuUi.h"

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
//#pragma comment(lib, "irrNetLite.lib")
#pragma comment(lib, "ws2_32.lib")

// You must derive a class from INetCallback and override the
// "handlePacket" method. When a packet is received it will be
// passed to this function, and you may dissect it as you wish.
// If this is the server you may retrieve the player ID using
// packet.getPlayerId().
class MyNetCallback : public net::INetCallback
{
public:
	virtual void handlePacket(net::SInPacket& packet)
	{
		//// irrNetLite encryption is very easy to use! Just pass
		//// a 16-byte (128-bit) string to encryptPacket/decryptPacket
		//// to encrypt/decrypt a packet respectively. Do not try to
		//// decrypt an un-encrypted packet or read from an encrypted
		//// packet without decrypting it first or bad things will happen!
		//packet.decryptPacket("hushthisissecret");
		//
		//// irrNetLite compression is even easier! The ZLib library is used
		//// here, just call compressPacket/decompressPacket to 
		//// compress/decompress a packet. Again, do not try to decompress
		//// an un-compressed packet or read from a compressed packet without
		//// decompressing it! Another thing to keep in mind is that you should
		//// decompress and decrypt in the correct order. If you compressed a file
		//// and then encrypted it when it was sent, you must decrypt it first
		//// before trying to decompress it, same goes for the other order.
		//packet.deCompressPacket();
		//
		//// Extracting info from a received packet is simple. You can treat
		//// the packet as an input stream, the >> operator is overloaded
		//// and works for most built in types. The string class in irrNetLite
		//// is a custom implementation not unlike the std::string. You can
		//// also send and receive strings as "char*". Note that the "char*"
		//// and stringc are interchangeable, you can send a stringc and
		//// receive a char*, or vice-versa.
		core::stringc str;
		packet >> str;
		context.listbox

		//// Support for a simple 3-dimensional vector class is there too. Both
		//// vector3df and core::stringc are borrowed from Irrlicht and included
		//// here for convenience.
		//core::vector3df vec;
		//packet >> vec;
		//
		//// Here we are obtaining the last value from the packet. f32 is just a
		//// typedef for float.
		//f32 height;
		//packet >> height;
		//
		//// Print the values to the console.
		//std::cout << "Message: " << str.c_str();
		//std::cout << " Position: " << vec.X << " " << vec.Y << " " << vec.Z;
		//std::cout << " Height: " << height << " ft";
		//std::cout << std::endl;

	}
};