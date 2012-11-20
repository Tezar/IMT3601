#pragma once
/*
* dedicated server only, handles flow of game (lobby > game > after lobby, maybe by FS automata), holds connections, handles chats, running engine instance and recieving events from it
*/
class GameSession
{
public:
	GameSession(void);
	~GameSession(void);
};

