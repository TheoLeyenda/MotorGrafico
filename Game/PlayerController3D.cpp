#include "PlayerController3D.h"
#include "Input.h"
#include "model.h"
#include "AxisAlignedBoundingBox.h"

PlayerController3D::PlayerController3D(Renderer * _renderer) : Entity(_renderer){}

PlayerController3D::~PlayerController3D() {}

void PlayerController3D::Move(Input* input, Time time)
{
	CheckInputs(input);
	SetRotationY(currentTurnSpeed * time.deltaTime() + transform.rotation.y);
	float dis = currentSpeed * time.deltaTime();
	float dx = (float)(dis * mathLibrary.sin(mathLibrary.ToRadians(transform.rotation.y)));
	float dz = (float)(dis * mathLibrary.cos(mathLibrary.ToRadians(transform.rotation.y)));
	if(model == NULL)
		SetPosition(dx, 0, dz);

	if (model != NULL) 
	{
		SetPosition(dx + transform.position.x, model->transform.position.y, dz + transform.position.z);
		
		model->SetPosition(transform.position.x , transform.position.y, transform.position.z);
		model->SetRotationX(transform.rotation.x);
		model->SetRotationY(transform.rotation.y);
		model->SetRotationZ(transform.rotation.z);
		model->SetScale(transform.scale.x, transform.scale.y, transform.scale.z);
	}
}

void PlayerController3D::SetMyModel(Model* value)
{
	model = value;
	if (model != NULL) {
		SetPosition(model->transform.position.x, model->transform.position.y, model->transform.position.z);
		SetRotationX(model->transform.rotation.x);
		SetRotationY(model->transform.rotation.y);
		SetRotationZ(model->transform.rotation.z);
		SetScale(model->transform.scale.x, model->transform.scale.y, model->transform.scale.z);
	}
}

void PlayerController3D::Draw(bool & wireFrameActive){}

void PlayerController3D::CheckInputs(Input* input)
{
	if (input->GetKey(KeyBoard::KEY_W))
		currentSpeed = RUN_SPEED;
	else if (input->GetKey(KeyBoard::KEY_S))
		currentSpeed = -RUN_SPEED;
	else
		currentSpeed = 0;
	
	if (input->GetKey(KeyBoard::KEY_UP) && model != NULL)
		model->SetPosition(model->transform.position.x, model->transform.position.y + UP_SPEED, model->transform.position.z);
	else if (input->GetKey(KeyBoard::KEY_DOWN) && model != NULL)
		model->SetPosition(model->transform.position.x, model->transform.position.y - UP_SPEED, model->transform.position.z);

	if (input->GetKey(KeyBoard::KEY_D))
		currentTurnSpeed = -TURN_SPEED;
	else if (input->GetKey(KeyBoard::KEY_A))
		currentTurnSpeed = TURN_SPEED;
	else
		currentTurnSpeed = 0;
}

void PlayerController3D::BindBuffer(){}

void PlayerController3D::SetEnableDrawAABB(bool value)
{
	if (axisAlignedBoundingBox != NULL)
		axisAlignedBoundingBox->SetEnableDraw(value);
}
