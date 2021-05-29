#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
class Game: public GameBase
{
private:
	int resultInit;
	Shape* shape1 = NULL;
	Shape* shape2 = NULL;
	Primitive3D* pyramid = NULL;

	Primitive3D* cube = NULL;
	Primitive3D* cube2 = NULL;
	Primitive3D* cube3 = NULL;

	Material* goldMaterial = NULL;
	Material* silverMaterial = NULL;
	Material* esmeraldMaterial = NULL;
	Material* greenRubberMaterial = NULL;
	
	Audio* audio = NULL;

	Light* light1 = NULL;
	Light* light2 = NULL;
	Light* light3 = NULL;

	Model* model = NULL;

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