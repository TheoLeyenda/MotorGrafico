#include "..\Motor\Src\GameBase.h"
#include "Game.h"

enum TypeDrawShape
{
	Tri,
	Quad,
	Spri,
	MultiplayObjects,
};
enum TypeCollisionCheck
{
	Collision,
	Trigger,
};

//---------------------//
//VALORES DE TESTEO
float speed = 2.5f;
float speedRotation = 0.05f;
float speedScale = 2.5f;

float r = 1.0f;
float g = 0.0f;
float b = 0.0f;
float a = 1.0f;

bool enableVertexTexture = false;

float speedMovementCamera = 250.0f;
float speedRotateCamera = 90.0f;

float newPositionCamX = 0;
float newPositionCamY = 0;
float newPositionCamZ = 0;

bool useCamera = true;
bool useModels = true;
//---------------------//

TypeColorShape typeColorShape = TypeColorShape::SolidColor;

Game::Game() :GameBase() {}

//---------------------//
Game::~Game() {}
//---------------------//

void Game::InitGame()
{
	/*
	shape2 = new Shape(render, TypeShape::TRIANGLE, VertexColor);
	shape2->SetPosition(500.7, 200.0f, -500.0f);
	shape2->SetScale(200.5f, 200.5f, 0.5f);

	shape1 = new Shape(render, TypeShape::QUAD, SolidColor);
	shape1->SetPosition(500.0f, 400.0f, 0.0f);
	shape1->SetScale(200.5f, 200.5f, 0.5f);
	*/

	newPositionCamX = camera->transform.position.x;
	newPositionCamY = camera->transform.position.y;
	newPositionCamZ = camera->transform.position.z + 55;

	pyramid = new Model3D(render,Pyramid);
	pyramid->SetPosition(300.0f, 200.0f, -50.0f);
	//pyramid->SetRotationZ(50);
	//pyramid->SetRotationX(60);
	//pyramid->SetRotationZ(45);
	pyramid->SetScale(50.0f, 50.0f, 50.0f);

	cube = new Model3D(render, Cube);
	cube->SetPosition(300.0f, 100.0f, -50.0f);
	//cube->SetRotationZ(50);
	//cube->SetRotationX(60);
	//cube->SetRotationZ(45);
	cube->SetScale(50.0f, 50.0f, 10.0f);
}

void Game::UpdateGame(Windows *_window, Renderer *_render, Input *_input)
{
	//timeClock.FPS();

	/*
	shape2->Draw(TypeShape::TRIANGLE, 3);
	shape1->Draw(TypeShape::QUAD, 4);

	std::cout << "POS X:" << shape2->transform.position.x << std::endl;
	std::cout << "POS Y:" << shape2->transform.position.y << std::endl;
	std::cout << "POS Z:" << shape2->transform.position.z << std::endl;

	collisionManager->CheckCollision2D(shape1, shape2, speed, shape1->GetBoxColliderSize2D(), shape2->GetBoxColliderSize2D());
	collisionManager->CheckCollision2D(shape1, shape1, speed, shape1->GetBoxColliderSize2D(), shape1->GetBoxColliderSize2D());

	collisionManager->CheckCollision2D(shape2, shape1, speed, shape2->GetBoxColliderSize2D(), shape1->GetBoxColliderSize2D());
	collisionManager->CheckCollision2D(shape2, shape1, speed, shape2->GetBoxColliderSize2D(), shape1->GetBoxColliderSize2D());

	TempInputs(windows, shape2);
	TempColorInput(windows, shape2);
	*/
	pyramid->Draw();

	cube->Draw();
	if (useCamera)
		TempInputCamera();

	if (useModels) 
	{
		TempInputs(windows, pyramid);
		TempInputs(windows, cube);
	}

}

void Game::DestroyGame()
{
	//---------------------//
#pragma region MOTOR 2D
	if (shape1 != NULL)
		delete shape1;
	if (shape2 != NULL)
		delete shape2;
#pragma endregion

	if (cube != NULL)
		delete cube;
	if (pyramid != NULL)
		delete pyramid;
	//---------------------//
}
void Game::TempColorInput(Windows* windows, Shape* shape)
{
	//---------------------//
#pragma region COLOR REGION
	
	if (input->GetKey(KeyBoard::KEY_ENTER))
	{
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		shape->SetSolidColor(r, g, b);
	}
	
	if (input->GetKey(KeyBoard::KEY_KP_0))
	{
		typeColorShape = TypeColorShape::SolidColor;
		if (shape->GetCurrentShape() == TypeShape::TRIANGLE) {
			shape->SetShape(TypeShape::TRIANGLE, typeColorShape);
			shape->SetVertexsAttribShape(TypeMaterial::Color);
		}
		else if (shape->GetCurrentShape() == TypeShape::QUAD)
		{
			shape->SetShape(TypeShape::QUAD, typeColorShape);
			shape->SetVertexsAttribShape(TypeMaterial::Color);
		}
	}
	if (input->GetKey(KeyBoard::KEY_KP_ENTER))
	{
		typeColorShape = TypeColorShape::VertexColor;
		if (shape->GetCurrentShape() == TypeShape::TRIANGLE) {
			shape->SetShape(TypeShape::TRIANGLE, typeColorShape);
			shape->SetVertexsAttribShape(TypeMaterial::Color);
		}
		else if (shape->GetCurrentShape() == TypeShape::QUAD)
		{
			shape->SetShape(TypeShape::QUAD, typeColorShape);
			shape->SetVertexsAttribShape(TypeMaterial::Color);
		}
	}
#pragma endregion

	
}

void Game::TempInputCamera()
{
#pragma region CAMERA MOVE
	float speed = 0;
	//INPUTS
	KeyBoard moveUpCamera = KeyBoard::KEY_W;
	KeyBoard moveDownCamera = KeyBoard::KEY_S;
	KeyBoard moveLeftCamera = KeyBoard::KEY_A;
	KeyBoard moveRightCamera = KeyBoard::KEY_D;
	KeyBoard moveForwardCamera = KeyBoard::KEY_UP;
	KeyBoard moveBackCamera = KeyBoard::KEY_DOWN;

	//ROTACION EN Z NO DISPONIBLE AUN.
	KeyBoard y_rotateLeft = KeyBoard::KEY_KP_4;
	KeyBoard y_rotateRight = KeyBoard::KEY_KP_6;
	KeyBoard x_rotateLeft = KeyBoard::KEY_KP_8;
	KeyBoard x_rotateRight = KeyBoard::KEY_KP_2;


	//TRASLACION
	if (input->GetKey(moveUpCamera))
	{
		newPositionCamY += speedMovementCamera * timeClock.deltaTime();
	}
	if (input->GetKey(moveDownCamera))
	{
		newPositionCamY -= speedMovementCamera * timeClock.deltaTime();
	}
	if (input->GetKey(moveLeftCamera))
	{
		newPositionCamX -= speedMovementCamera * timeClock.deltaTime();
	}
	if (input->GetKey(moveRightCamera))
	{
		newPositionCamX += speedMovementCamera * timeClock.deltaTime();
	}
	if (input->GetKey(moveForwardCamera)) 
	{
		newPositionCamZ += speedMovementCamera * timeClock.deltaTime();
	}
	if (input->GetKey(moveBackCamera)) 
	{
		newPositionCamZ -= speedMovementCamera * timeClock.deltaTime();
	}

	//ROTACION
	if (input->GetKey(y_rotateLeft))
	{
		speed = speedRotateCamera * timeClock.deltaTime();
		camera->RotateCameraY(speed);
	}
	if (input->GetKey(y_rotateRight))
	{
		speed = speedRotateCamera * timeClock.deltaTime();
		camera->RotateCameraY(-speed);
	}
	if (input->GetKey(x_rotateLeft))
	{
		speed = speedRotateCamera * timeClock.deltaTime();
		camera->RotateCameraX(speed);

	}
	if (input->GetKey(x_rotateRight))
	{
		speed = speedRotateCamera * timeClock.deltaTime();
		camera->RotateCameraX(-speed);
	}

	//MANEJO DE DATOS
	camera->SetPosition(newPositionCamX, newPositionCamY, newPositionCamZ);

	render->SetView(camera);
	//render->RotateCamera(newRotationCamZ, camera->GetInternalData().model);
	
#pragma endregion
}

void Game::TempInputs(Windows* windows, Entity* shape)
{

	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_T))
	{
		shape->SetPosition(shape->transform.position.x, shape->transform.position.y + speed, shape->transform.position.z);

	}
	if (input->GetKey(KeyBoard::KEY_G))
	{
		shape->SetPosition(shape->transform.position.x, shape->transform.position.y - speed, shape->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_H))
	{
		shape->SetPosition(shape->transform.position.x + speed, shape->transform.position.y, shape->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_F))
	{
		shape->SetPosition(shape->transform.position.x - speed, shape->transform.position.y, shape->transform.position.z);

	}
	//-------------------//

	//INPUT DE ROTACION
	if (input->GetKey(KeyBoard::KEY_I))
	{
		shape->SetRotationZ(shape->transform.rotation.z + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_O))
	{
		shape->SetRotationZ(shape->transform.rotation.z - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_K))
	{
		shape->SetRotationY(shape->transform.rotation.y + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_L))
	{
		shape->SetRotationY(shape->transform.rotation.y - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_N))
	{
		shape->SetRotationX(shape->transform.rotation.x + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_M))
	{
		shape->SetRotationX(shape->transform.rotation.x - speedRotation);
	}
	//------------------//

	//INPUT DE ESCALA
	if (input->GetKey(KeyBoard::KEY_9))
	{
		shape->SetScale(shape->transform.scale.x + speedScale, shape->transform.scale.y + speedScale, shape->transform.scale.z + speedScale);
	}
	if (input->GetKey(KeyBoard::KEY_0))
	{
		shape->SetScale(shape->transform.scale.x - speedScale, shape->transform.scale.y - speedScale, shape->transform.scale.z - speedScale);
	}
}

void Game::TempInputsPlayer1(Windows* windows, Sprite* sprite)
{
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_W))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y + speed, sprite->transform.position.z);
		sprite->SetCurrentAnimationIndex(0);
	}
	if (input->GetKey(KeyBoard::KEY_S))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y - speed, sprite->transform.position.z);
		sprite->SetCurrentAnimationIndex(3);
	}
	if (input->GetKey(KeyBoard::KEY_D))
	{
		sprite->SetPosition(sprite->transform.position.x + speed, sprite->transform.position.y, sprite->transform.position.z);
		sprite->SetCurrentAnimationIndex(1);
	}
	if (input->GetKey(KeyBoard::KEY_A))
	{
		sprite->SetPosition(sprite->transform.position.x - speed, sprite->transform.position.y, sprite->transform.position.z);
		sprite->SetCurrentAnimationIndex(2);
	}
	//-------------------//

	//INPUT DE ROTACION
	if (input->GetKey(KeyBoard::KEY_KP_4))
	{
		sprite->SetRotationZ(sprite->transform.rotation.z + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_6))
	{
		sprite->SetRotationZ(sprite->transform.rotation.z - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_1))
	{
		sprite->SetRotationY(sprite->transform.rotation.y + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_3))
	{
		sprite->SetRotationY(sprite->transform.rotation.y - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_7))
	{
		sprite->SetRotationX(sprite->transform.rotation.x + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_9))
	{
		sprite->SetRotationX(sprite->transform.rotation.x - speedRotation);
	}
	//------------------//

	//INPUT DE ESCALA
	if (input->GetKey(KeyBoard::KEY_KP_8))
	{
		sprite->SetScale(sprite->transform.scale.x + speedScale, sprite->transform.scale.y + speedScale, sprite->transform.scale.z + speedScale);
	}
	if (input->GetKey(KeyBoard::KEY_KP_2))
	{
		sprite->SetScale(sprite->transform.scale.x - speedScale, sprite->transform.scale.y - speedScale, sprite->transform.scale.z - speedScale);
	}
}

void Game::TempInputsPlayer2(Windows * windows, Sprite * sprite)
{
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_UP))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y + speed, sprite->transform.position.z);
		sprite->SetCurrentAnimationIndex(0);
	}
	if (input->GetKey(KeyBoard::KEY_DOWN))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y - speed, sprite->transform.position.z);
		sprite->SetCurrentAnimationIndex(3);
	}
	if (input->GetKey(KeyBoard::KEY_RIGHT))
	{
		sprite->SetPosition(sprite->transform.position.x + speed, sprite->transform.position.y, sprite->transform.position.z);
		sprite->SetCurrentAnimationIndex(1);
	}
	if (input->GetKey(KeyBoard::KEY_LEFT))
	{
		sprite->SetPosition(sprite->transform.position.x - speed, sprite->transform.position.y, sprite->transform.position.z);
		sprite->SetCurrentAnimationIndex(2);
	}
	//-------------------//
	//INPUT DE ROTACION
	if (input->GetKey(KeyBoard::KEY_KP_4))
	{
		sprite->SetRotationZ(sprite->transform.rotation.z + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_6))
	{
		sprite->SetRotationZ(sprite->transform.rotation.z - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_1))
	{
		sprite->SetRotationY(sprite->transform.rotation.y + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_3))
	{
		sprite->SetRotationY(sprite->transform.rotation.y - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_7))
	{
		sprite->SetRotationX(sprite->transform.rotation.x + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_9))
	{
		sprite->SetRotationX(sprite->transform.rotation.x - speedRotation);
	}
	//------------------//

	//INPUT DE ESCALA
	if (input->GetKey(KeyBoard::KEY_KP_8))
	{
		sprite->SetScale(sprite->transform.scale.x + speedScale, sprite->transform.scale.y + speedScale, sprite->transform.scale.z + speedScale);
	}
	if (input->GetKey(KeyBoard::KEY_KP_2))
	{
		sprite->SetScale(sprite->transform.scale.x - speedScale, sprite->transform.scale.y - speedScale, sprite->transform.scale.z - speedScale);
	}

}
