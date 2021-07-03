#include "Audio.h"


Audio::Audio(Renderer* render) : Entity(render)
{
	SoundEngine = irrklang::createIrrKlangDevice();
	SoundRecorder = irrklang::createIrrKlangAudioRecorder(SoundEngine);
	InmortalObject = true;
}

string Audio::GetClassName()
{
	return "Audio";
}

void Audio::BindBuffer(){}

void Audio::Draw(bool & wireFrameActive) {  }

void Audio::PlayAudio2D(const char * pathMusicFile, bool loop)
{
	if (SoundEngine != NULL)
	{
		SoundEngine->play2D(pathMusicFile, loop);
	}
	else 
	{
		std::cout << "ERROR: SoundEngine is null" << std::endl;
	}
}

void Audio::StopAll()
{
	if (SoundEngine != NULL)
	{
		SoundEngine->stopAllSounds();
	}
	else
	{
		std::cout << "ERROR: SoundEngine is null" << std::endl;
	}
}

Audio::~Audio()
{
	if(SoundSource != NULL)
		SoundSource->drop();
	
	if(SoundRecorder != NULL)
		SoundRecorder->drop();
	
	if(SoundEngine != NULL)
		SoundEngine->drop();
}
