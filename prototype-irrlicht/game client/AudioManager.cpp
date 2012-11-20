#include "AudioManager.hpp"

AudioManagerClass::AudioManagerClass()
{
	audioDevice = irrklang::createIrrKlangDevice();
}

//void AudioManagerClass::CreateAudioManager()
//{
//	
//}

void AudioManagerClass::BackgroundMusic()
{
	irrklang::ISound * backgroundMusic = 
		audioDevice->play3D("../media/Doctor Who - This Is Gallifrey, Our Childhood, Our Home.mp3",
		irrklang::vec3df(0,0,0), true, false, true);
}

void AudioManagerClass::PlaySound()
{

}

AudioManagerClass::~AudioManagerClass()
{
	audioDevice->drop();
}