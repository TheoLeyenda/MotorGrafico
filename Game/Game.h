#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
class Game: public GameBase
{
private:
	int resultInit;
	Shape* quad; //no tiene que ir xd
	Shape* tri;
	Sprite* player;

	Animation* _runLeft;
public:
	Game();
	~Game();
	bool isPlaying;

	//Override Functions//

	void InitGame() override;
	void UpdateGame(Windows *_window, Renderer *_render, Input *_input) override;
	void DestroyGame() override;

	void TempInputs(Windows* windows, Shape* tri);
	void TempInputs(Windows* windows, Sprite* tri);
};
#endif