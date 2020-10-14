#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
class Game: public GameBase
{
private:
	int resultInit;
public:
	Game();
	~Game();
	void Play();
	bool isPlaying;

	//Override Functions//

	//int InitGame() override;
	//void Update() override;
	//void DestroyGame() override;


	int InitGame();
	void Update();
	void DestroyGame();
};
#endif