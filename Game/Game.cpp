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
float speedCamer = 200.5f;
float newCamX = 0;
float newCamY = 0;
float newCamZ = 0;
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

	newCamX = camera->transform.position.x;
	newCamY = camera->transform.position.y;
	newCamZ = camera->transform.position.z;

	pyramid = new Model3D(render,Pyramid);
	pyramid->SetPosition(500.0f, 200.0f, -98.0f);
	pyramid->SetScale(100.0f, 100.0f, 100.0f);
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

	TempColorInput(windows, shape1);

}

void Game::DestroyGame()
{
	//---------------------//
	if (shape1 != NULL)
		delete shape1;
	if (shape2 != NULL)
		delete shape2;
	if (pyramid != NULL)
		delete pyramid;
	//---------------------//
}
void Game::TempColorInput(Windows* windows, Shape* shape)
{
	//---------------------//
	#pragma region COLOR REGION
	/*
	
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
	*/
	#pragma endregion

	#pragma region CAMERA MOVE
		if (input->GetKey(KeyBoard::KEY_UP))
		{
			newCamZ += speedCamer * timeClock.deltaTime();
		}
		if (input->GetKey(KeyBoard::KEY_DOWN))
		{
			newCamZ -= speedCamer * timeClock.deltaTime();
		}
		if (input->GetKey(KeyBoard::KEY_LEFT))
		{
			//newCamX -= speedCamer * timeClock.deltaTime();
			//camera->SetPosition(newCamX, newCamY, newCamZ);
			newCamX -= speedCamer * timeClock.deltaTime();
		}
		if (input->GetKey(KeyBoard::KEY_RIGHT))
		{
			//newCamX += speedCamer * timeClock.deltaTime();
			//camera->SetPosition(newCamX, newCamY, newCamZ);
			newCamX += speedCamer * timeClock.deltaTime();
		}
		camera->SetPosition(newCamX, newCamY, newCamZ);
		render->RotateCamera(newCamX, camera->GetInternalData().model);
#pragma endregion
}

void Game::TempInputs(Windows* windows, Shape* shape)
{

	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_W))
	{
		shape->SetPosition(shape->transform.position.x, shape->transform.position.y + speed, shape->transform.position.z);

	}
	if (input->GetKey(KeyBoard::KEY_S))
	{
		shape->SetPosition(shape->transform.position.x, shape->transform.position.y - speed, shape->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_D))
	{
		shape->SetPosition(shape->transform.position.x + speed, shape->transform.position.y, shape->transform.position.z);
	}
	if (input->GetKey(KeyBoard::KEY_A))
	{
		shape->SetPosition(shape->transform.position.x - speed, shape->transform.position.y, shape->transform.position.z);

	}
	//-------------------//

	//INPUT DE ROTACION
	if (input->GetKey(KeyBoard::KEY_KP_4))
	{
		shape->SetRotationZ(shape->transform.rotation.z + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_6))
	{
		shape->SetRotationZ(shape->transform.rotation.z - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_1))
	{
		shape->SetRotationY(shape->transform.rotation.y + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_3))
	{
		shape->SetRotationY(shape->transform.rotation.y - speedRotation);
	}

	if (input->GetKey(KeyBoard::KEY_KP_7))
	{
		shape->SetRotationX(shape->transform.rotation.x + speedRotation);
	}
	if (input->GetKey(KeyBoard::KEY_KP_9))
	{
		shape->SetRotationX(shape->transform.rotation.x - speedRotation);
	}
	//------------------//

	//INPUT DE ESCALA
	if (input->GetKey(KeyBoard::KEY_KP_8))
	{
		shape->SetScale(shape->transform.scale.x + speedScale, shape->transform.scale.y + speedScale, shape->transform.scale.z + speedScale);
	}
	if (input->GetKey(KeyBoard::KEY_KP_2))
	{
		shape->SetScale(shape->transform.scale.x - speedScale, shape->transform.scale.y - speedScale, shape->transform.scale.z - speedScale);
	}
}

void Game::TempInputsPlayer1(Windows* windows, Sprite* sprite)
{
	/*
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_W))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y + speed, sprite->transform.position.z);
		player->SetCurrentAnimationIndex(0);
	}
	if (input->GetKey(KeyBoard::KEY_S))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y - speed, sprite->transform.position.z);
		player->SetCurrentAnimationIndex(3);
	}
	if (input->GetKey(KeyBoard::KEY_D))
	{
		sprite->SetPosition(sprite->transform.position.x + speed, sprite->transform.position.y, sprite->transform.position.z);
		player->SetCurrentAnimationIndex(1);
	}
	if (input->GetKey(KeyBoard::KEY_A))
	{
		sprite->SetPosition(sprite->transform.position.x - speed, sprite->transform.position.y, sprite->transform.position.z);
		player->SetCurrentAnimationIndex(2);
	}
	//-------------------//
	*/

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
	/*
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_UP))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y + speed, sprite->transform.position.z);
		player2->SetCurrentAnimationIndex(0);
	}
	if (input->GetKey(KeyBoard::KEY_DOWN))
	{
		sprite->SetPosition(sprite->transform.position.x, sprite->transform.position.y - speed, sprite->transform.position.z);
		player2->SetCurrentAnimationIndex(3);
	}
	if (input->GetKey(KeyBoard::KEY_RIGHT))
	{
		sprite->SetPosition(sprite->transform.position.x + speed, sprite->transform.position.y, sprite->transform.position.z);
		player2->SetCurrentAnimationIndex(1);
	}
	if (input->GetKey(KeyBoard::KEY_LEFT))
	{
		sprite->SetPosition(sprite->transform.position.x - speed, sprite->transform.position.y, sprite->transform.position.z);
		player2->SetCurrentAnimationIndex(2);
	}
	//-------------------//
	*/
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
