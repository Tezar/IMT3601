#include "AudioManager.hpp"
#include "GameRenderer.hpp"

AudioManagerClass::AudioManagerClass()
{
	audioDevice = irrklang::createIrrKlangDevice();
//	audioDevice->setListenerPosition(engine->averagePosition+core::vector3df(0,0,-5), irrklang::vec3df(0,-1,1))
}

void AudioManagerClass::UpdateListenerPosition(Engine * engine)
{
	audioDevice->setListenerPosition(engine->averagePosition+core::vector3df(0,0,-5), irrklang::vec3df(0,-1,1));
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