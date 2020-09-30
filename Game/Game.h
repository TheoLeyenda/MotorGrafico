#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
class Game: GameBase
{
public:
	Game();
	~Game();
	void Play();
	bool isPlaying;
};
#endif