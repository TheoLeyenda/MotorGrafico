#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Entity.h"
#include "Input.h"
#include "Timer.h"
#include "MathLibrary.h"

class Model;

class PlayerController3D : public Entity
{
private:
	Model* model = NULL;

	float RUN_SPEED = 100;
	float TURN_SPEED = 120;
	float UP_SPEED = 50;

	float currentSpeed = 0;
	float currentTurnSpeed = 0;
	void CheckInputs(Input* input);
protected:
	void BindBuffer() override;
	void SetEnableDrawAABB(bool value) override;
public:
	PlayerController3D(Renderer *_renderer);
	void Move(Input* input, Time time);
	void SetMyModel(Model* model);
	void SetRUN_SPEED(float value) { RUN_SPEED = value; }
	void SetTURN_SPEED(float value) { TURN_SPEED = value; }
	void SetUP_SPEED(float value) { UP_SPEED = value; }
	void Draw(bool& wireFrameActive) override;
	float GetRUN_SPEED() { return RUN_SPEED; }
	float GetTURN_SPEED() { return TURN_SPEED; }
	float GetUP_SPEED() { return UP_SPEED; }
	~PlayerController3D();
};

#endif

