#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
#include "PlayerController3D.h"
class Game: public GameBase
{
private:
	int resultInit;

	PlayerController3D* player3D = NULL;

	//Primitive3D* cube = NULL;

	Animation* animations = NULL;

	Material* goldMaterial = NULL;
	Material* silverMaterial = NULL;
	Material* esmeraldMaterial = NULL;
	Material* greenRubberMaterial = NULL;
	Material* mat_shape3 = NULL;
	Material* mat_shape4 = NULL;

	Audio* audio = NULL;
	Model* bobFBX = NULL;
public:
	Game();
	~Game();
	bool isPlaying;

	//Override Functions//

	void InitGame() override;
	void UpdateGame(Windows *_window, Renderer *_render, Input *_input) override;
	void DestroyGame() override;

	void InitMaterials();
	void TempInputs(Windows* windows, Entity* shape);
	void TempInputsPlayer1(Windows* windows, Sprite* sprite);
	void TempInputsPlayer2(Windows* windows, Sprite* sprite);
	void TempColorInput(Windows* windows, Shape* shape);
	void TempInputCamera();
	void TempMoveLightWithID(Windows* windows, int id);
};
#endif