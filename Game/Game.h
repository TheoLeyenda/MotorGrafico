#ifndef GAME_H
#define GAME_H
#include "GameBase.h"
class Game: public GameBase
{
private:
	int resultInit;
	Shape* shape1;
	Shape* shape2;
	Primitive3D* pyramid;

	Primitive3D* cube;
	Primitive3D* cube2;
	Primitive3D* cube3;

	Material* goldMaterial;
	Material* silverMaterial;
	Material* esmeraldMaterial;
	Material* greenRubberMaterial;
	

	Light* light1;
	Light* light2;
	Light* light3;

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