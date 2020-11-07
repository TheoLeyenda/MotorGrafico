#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
class Game: public GameBase
{
private:
	int resultInit;
	Shape* shape1; //no tiene que ir xd
	Shape* shape2;
	Sprite* player;
	Sprite* ferchu;
	Sprite* bokita;

	Animation* _animations;
	
public:
	Game();
	~Game();
	bool isPlaying;

	//Override Functions//

	void InitGame() override;
	void UpdateGame(Windows *_window, Renderer *_render, Input *_input) override;
	void DestroyGame() override;

	void TempInputs(Windows* windows, Shape* shape);
	void TempInputs(Windows* windows, Sprite* sprite);
	void TempColorInput(Windows* windows, Shape* shape);
};
#endif