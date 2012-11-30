#include "AudioManager.hpp"
#include "GameRenderer.hpp"

AudioManagerClass::AudioManagerClass()
{
	audioDevice = irrklang::createIrrKlangDevice();
//	audioDevice->setListenerPosition(engine->averagePosition+core::vector3df(0,0,-5), irrklang::vec3df(0,-1,1))
	AddAllSoundSources();
}

void AudioManagerClass::UpdateListenerPosition(Engine * engine)
{
	audioDevice->setListenerPosition(engine->averagePosition+core::vector3df(0,0,-5), irrklang::vec3df(0,-1,1));
}

//void AudioManagerClass::CreateAudioManager()
//{
//	
//}

void AudioManagerClass::AddAllSoundSources()
{
	BackgroundSong = audioDevice->addSoundSourceFromFile("../media/Doctor Who - This Is Gallifrey, Our Childhood, Our Home.mp3");
//	IncreaseSpeed = audioDevice->addSoundSourceFromFile("../media/");
//	DecreaseSpeed = audioDevice->addSoundSourceFromFile("../media/");
//	Breaking = audioDevice->addSoundSourceFromFile("../media/");
//	Crashing = audioDevice->addSoundSourceFromFile("../media/");

	TestSound = audioDevice->addSoundSourceFromFile("../media/chord.wav");
}

void AudioManagerClass::BackgroundMusic()
{
	
	audioDevice->play3D(BackgroundSong, irrklang::vec3df(0,0,0), true, false, true);
}



/*****************************************************************************
 * How to use:																 *
 * ...->PlaySound(NameOfTheTypeOfSoundYouWantReplacesThis,					 *
 *		irrklang::vec3df(0,-1,1));											 *
 *																			 *
 * This function uses IrrKlangs vec3df, not IrrLicht. I believe the same	 *
 * values can still be used, if they're hard coded, but it could be a		 *
 * problem if they're not. A possible (untested) solution is using			 *
 * irrklang::vec3df position(core::vector3df(0,0,-5)); This means it could	 *
 * look something like this:												 *
 *																			 *
 * irrklang::vec3df position(engine->averagePosition +						 *
 *							 core::vector3df(0,0,-5));						 *
 * ...->PlaySound(NameOfTheTypeOfSoundYouWantReplacesThis, position);		 *
 *																			 *
 * For names of sound types, refer to AudioManager.hpp						 *
 *****************************************************************************/

void AudioManagerClass::PlaySound(E_sounds sounds, irrklang::vec3df position)
{
//	irrklang::ISoundSource * sound;
//
////	switch(sounds)
////	{
////	case E_IncreaseSpeed:	sound = IncreaseSpeed;	break;
////	case E_DecreaseSpeed:	sound = DecreaseSpeed;	break;
////	case E_Breaking:		sound = Breaking;		break;
////	case E_Crashing:		sound = Crashing;		break;
////	case E_TestSound:		sound = TestSound;		break;
////	default:				sound = TestSound;		break;
////	}
//
//	//sound = audioDevice->addSoundSourceFromFiwle("../media/chord.wav");
//
//	if(audioDevice->isCurrentlyPlaying(sound))
//	{
//		// Stop the current playback of the sound
//		audioDevice->play3D(sound, position, false, false, false);
//	}
//	
//	else
//		audioDevice->play3D(sound, position, false, false, false);
//
//	audioDevice->removeSoundSource("../media/chord.wav");
}

AudioManagerClass::~AudioManagerClass()
{
	audioDevice->removeAllSoundSources();
	audioDevice->drop();
}