#pragma once

#include <irrlicht.h>
#include <irrKlang.h>
#include "Singleton.hpp"
#include "Engine.hpp"


#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

enum E_sounds 
	{
		E_BackgroundSong,
		E_IncreaseSpeed,
		E_DecreaseSpeed,
		E_Breaking,
		E_Crashing,
		E_TestSound
	};

class AudioManagerClass
{
private:
	irrklang::ISoundSource * BackgroundSong;
	irrklang::ISoundSource * IncreaseSpeed;
	irrklang::ISoundSource * DecreaseSpeed;
	irrklang::ISoundSource * Breaking;
	irrklang::ISoundSource * Crashing;

	irrklang::ISoundSource * TestSound;

	irrklang::ISoundEngine * audioDevice;

public:
	AudioManagerClass();
	~AudioManagerClass();

	void AddAllSoundSources();

	void UpdateListenerPosition(Engine * engine);
	void BackgroundMusic();
	void PlaySound(E_sounds, irrklang::vec3df position);



	irrklang::ISoundEngine * getEngine(void){ return audioDevice; }
};

typedef Singleton<AudioManagerClass> AudioManager;   // Global declaration