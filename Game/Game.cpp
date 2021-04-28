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
float speed = 10.0f;
float speedRotation = 0.05f;
float speedScale = 2.5f;

float r = 1.0f;
float g = 0.0f;
float b = 0.0f;
float a = 1.0f;

bool enableVertexTexture = false;

float speedMovementCamera = 600.0f;
float speedRotateCamera = 90.0f;

float newPositionCamX = 0;
float newPositionCamY = 0;
float newPositionCamZ = 0;

bool ortho = false;
bool useCamera = true;
bool useModels = true;
//---------------------//

//LIGHT
float ambientIntensity;
float diffuseIntensity;

TypeColorShape typeColorShape = TypeColorShape::SolidColor;

Game::Game() :GameBase() {}

//---------------------//
Game::~Game() {}
//---------------------//

void Game::InitGame()
{

	newPositionCamX = camera->transform.position.x;
	newPositionCamY = camera->transform.position.y;
	newPositionCamZ = camera->transform.position.z + 55;

	InitMaterials();

	pyramid = new Primitive3D(render,Pyramid);
	pyramid->SetPosition(300.0f, 250.0f, -50.0f);
	pyramid->SetScale(50.0f, 50.0f, 50.0f);

	cube = new Primitive3D(render, Cube);
	cube->SetPosition(300, 100.0f, -50.0f);
	cube->SetScale(50.0f, 50.0f, 50.0f);
	cube->SetNewMaterial(greenRubberMaterial);

	cube2 = new Primitive3D(render, Cube);
	cube2->SetPosition(420.0f, 100.0f, -50.0f);
	cube2->SetScale(50.0f, 50.0f, 50.0f);
	cube2->SetNewMaterial(goldMaterial);

	cube3 = new Primitive3D(render, Cube);
	cube3->SetPosition(360.0f, 250.0f, -50.0f);
	cube3->SetScale(50.0f, 50.0f, 50.0f);
	cube3->SetNewMaterial(silverMaterial);
}

void Game::UpdateGame(Windows *_window, Renderer *_render, Input *_input)
{
	//timeClock.FPS();

	if (useCamera)
		TempInputCamera();

	if (useModels)
		TempInputs(windows, light);

	//pyramid->Draw();
	cube->Draw();
	cube2->Draw();
	cube3->Draw();
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
	if (cube2 != NULL)
		delete cube2;
	if (cube3 != NULL)
		delete cube3;
	if (pyramid != NULL)
		delete pyramid;
	//---------------------//
	if (goldMaterial != NULL)
		delete goldMaterial;
	if (silverMaterial != NULL)
		delete silverMaterial;
	if (esmeraldMaterial != NULL)
		delete esmeraldMaterial;
	if (greenRubberMaterial != NULL)
		delete greenRubberMaterial;
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

	if (input->GetKey(KeyBoard::KEY_LEFT)) 
	{
		camera->ChangePerspective(TypeProjectionCamera::Ortho);	
	}
	if (input->GetKey(KeyBoard::KEY_RIGHT)) 
	{
		camera->ChangePerspective(TypeProjectionCamera::Perspective);
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

void Game::InitMaterials()
{

	goldMaterial = new Material();
	goldMaterial->SetAmbientMat(glm::vec3(0.24725f, 0.1995f, 0.0745f));
	goldMaterial->SetDiffuseMat(glm::vec3(0.75164f, 0.60648f, 0.22648f));
	goldMaterial->SetSpecularMat(glm::vec3(0.628281f, 0.555802f, 0.366065f));
	goldMaterial->SetNewShininess(0.1f, 128);

	silverMaterial = new Material();
	silverMaterial->SetAmbientMat(glm::vec3(0.19225f, 0.19225f, 0.19225f));
	silverMaterial->SetDiffuseMat(glm::vec3(0.50754f, 0.50754f, 0.50754f));
	silverMaterial->SetSpecularMat(glm::vec3(0.508273f, 0.508273f, 0.508273f));
	silverMaterial->SetNewShininess(0.4f, 128);

	esmeraldMaterial = new Material();
	esmeraldMaterial->SetAmbientMat(glm::vec3(0.0215f, 0.1745f, 0.0215f));
	esmeraldMaterial->SetDiffuseMat(glm::vec3(0.07568f, 0.61424f, 0.07568f));
	esmeraldMaterial->SetSpecularMat(glm::vec3(0.633f, 0.727811f, 0.633f));
	esmeraldMaterial->SetNewShininess(0.6f, 32);

	greenRubberMaterial = new Material();
	greenRubberMaterial->SetAmbientMat(glm::vec3(0.0f, 0.05f, 0.0));
	greenRubberMaterial->SetDiffuseMat(glm::vec3(0.4f, 0.5f, 0.4f));
	greenRubberMaterial->SetSpecularMat(glm::vec3(0.04f, 0.7f, 0.04f));
	greenRubberMaterial->SetNewShininess(0.078125f, 128.0f);

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
	if (input->GetKey(KeyBoard::KEY_R))
	{
		shape->SetPosition(shape->transform.position.x, shape->transform.position.y, shape->transform.position.z + speed);
	}
	if (input->GetKey(KeyBoard::KEY_Y))
	{
		shape->SetPosition(shape->transform.position.x, shape->transform.position.y, shape->transform.position.z - speed);
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
	if (input->GetKey(KeyBoard::KEY_V))
	{
		shape->SetScale(shape->transform.scale.x + speedScale, shape->transform.scale.y + speedScale, shape->transform.scale.z + speedScale);
	}
	if (input->GetKey(KeyBoard::KEY_B))
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
