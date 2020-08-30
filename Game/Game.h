#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
#include <glew.h>
#include <GLFW/glfw3.h>

class Game: GameBase
{
public:
	Game();
	~Game();
	void Play();
	bool isPlaying;
};
#endif