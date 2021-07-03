#ifndef AUDIO_H
#define AUDIO_H
#include "Entity.h"
#include "irrKlang-1.6.0/include/irrKlang.h"
#include <iostream>

class ENGINE_API Audio : public Entity
{
private:
	irrklang::ISoundEngine *SoundEngine = NULL;
	irrklang::ISoundSource *SoundSource = NULL;
	irrklang::IAudioRecorder* SoundRecorder = NULL;
	bool isPlaying = false;

protected:
	void BindBuffer() override;
public:
	Audio(Renderer* render);

	string GetClassName() override;

	void Draw(bool& wireFrameActive) override;

	void PlayAudio2D(const char* pathMusicFile, bool loop);

	void StopAll();

	bool GetIsPlayingAudio2D(const char* pathMusicFile) { return SoundEngine->isCurrentlyPlaying(pathMusicFile); }

	~Audio();
};

#endif
