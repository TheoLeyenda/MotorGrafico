#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
class Game: public GameBase
{
private:
	int resultInit;
	Shape* shape1;
	Shape* shape2;
	Model3D* pyramid;

	Model3D* cube;
	Model3D* cube2;
	Model3D* cube3;

	Material* goldMaterial;
	Material* silverMaterial;
	Material* esmeraldMaterial;
	Material* greenPlasticMaterial;
public:
	Game();
	~Game();
	bool isPlaying;

	//Override Functions//

	void InitGame() override;
	void UpdateGame(Windows *_window, Renderer *_render, Input *_input) override;
	void DestroyGame() override;

	void TempInputs(Windows* windows, Entity* shape);
	void TempInputsPlayer1(Windows* windows, Sprite* sprite);
	void TempInputsPlayer2(Windows* windows, Sprite* sprite);
	void TempColorInput(Windows* windows, Shape* shape);
	void TempInputCamera();
};
#endif