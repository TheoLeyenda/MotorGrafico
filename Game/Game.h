#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
#include "PlayerController3D.h"
class Game: public GameBase
{
private:
	int resultInit;

	PlayerController3D* player3D = NULL;

	Shape* shape1 = NULL;
	Shape* shape2 = NULL;
	Shape* shape3 = NULL;
	Shape* shape4 = NULL;

	Sprite* sprite = NULL;
	Sprite* spriteAnimado = NULL;

	Animation* animations = NULL;

	Primitive3D* pyramid = NULL;

	Primitive3D* cube = NULL;
	Primitive3D* cube2 = NULL;
	Primitive3D* cube3 = NULL;

	Material* goldMaterial = NULL;
	Material* silverMaterial = NULL;
	Material* esmeraldMaterial = NULL;
	Material* greenRubberMaterial = NULL;
	Material* mat_shape3 = NULL;
	Material* mat_shape4 = NULL;

	Audio* audio = NULL;

	Entity* robotLoco = NULL;
	Entity* planeBSP1 = NULL;
	Entity* planeBSP2 = NULL;
	Entity* planeBSP3 = NULL;

	Model* modelOBJ = NULL;
	Model* modelOBJ2 = NULL;
	Model* modelFBX = NULL;
	Model* model3DS = NULL;
	Model* modelCOLLADA = NULL;
	Model* modelSTL = NULL;
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