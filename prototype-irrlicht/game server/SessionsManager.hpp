#include "Singleton.hpp"
#pragma once
/*only, allows listing lobbies and it’s responsible for creating new ones*/
class SessionsManagerClass
{
public:
	SessionsManagerClass(void);
	~SessionsManagerClass(void);
};

typedef Singleton<SessionsManagerClass> SessionsManager;   // Global declaration