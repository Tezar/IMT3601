#include <irrlicht.h>
#include <irrKlang.h>
#include "Singleton.hpp"


#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class AudioManagerClass
{
private:
	irrklang::ISoundEngine * audioDevice;

public:
	AudioManagerClass();
	~AudioManagerClass();

//	void CreateAudioManager();
	void BackgroundMusic();
	void PlaySound();

	irrklang::ISoundEngine * getEngine(void){ return audioDevice; }
};

typedef Singleton<AudioManagerClass> AudioManager;   // Global declaration