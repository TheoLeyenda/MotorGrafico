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
float speedAutomaticRotation = 0.0005f;
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
bool rotateBokitaSkybox = true;
bool useSkybox = false;
bool thirdPerson = false;
glm::vec3 posThirdPersonCam;
glm::vec3 offsetThirdPerson;
//---------------------//

//LIGHT
float ambientIntensity;
float diffuseIntensity;


Game::Game() :GameBase() {}

//---------------------//
Game::~Game() {}
//---------------------//

void Game::InitGame()
{
	InitMaterials();

	//COLORES PARA TESTEAR
	glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 purple = glm::vec3(0.6784f, 0.0157f, 0.9412f);
	glm::vec3 yellow = glm::vec3(1.0f, 0.9843f, 0.0f);
	glm::vec3 brown = glm::vec3(0.4392f, 0.3059f, 0.1333f);
	glm::vec3 orange = glm::vec3(1.0f, 0.5686f, 0.0f);
	glm::vec3 cyan = glm::vec3(0.0157f, 0.9412f, 0.9412f);
	glm::vec3 magenta = glm::vec3(0.9412f, 0.0157f, 0.7412f);

	newPositionCamX = camera->transform.position.x;
	newPositionCamY = camera->transform.position.y;
	newPositionCamZ = camera->transform.position.z + 55;

	AddLight(Light::TypeLight::Spot, 1);
	AddLight(Light::TypeLight::Point, 2);
	AddLight(Light::TypeLight::Point, 6);

	AddLight(Light::TypeLight::Directional, 0);
	SetSettingsLightCustom(0, glm::vec3(0, 2, -6));
	SetLightPosition(6, glm::vec3(100, -50, 0));
	
	AddLight(Light::TypeLight::Spot, 87);
	SetLightPosition(87, glm::vec3(-50, -50, 0));
	
	//AddObjectInDenugGame(GetLight(1));
	//AddObjectInDenugGame(GetLight(2));
	//AddObjectInDenugGame(GetLight(6));
	//AddObjectInDenugGame(GetLight(0));
	//AddObjectInDenugGame(GetLight(87));

	//ChangeColorLight(1, red);
	//ChangeColorLight(2, yellow);
	//ChangeColorLight(6, cyan);
	//ChangeColorLight(87, brown);
	//ChangeColorLight(0, magenta);

	GetMyLightsID();

	modelOBJ = new Model(render);
	modelOBJ->LoadModel("res/modelos/source/alex.obj", "res/modelos/textures/", bsp_manager);
	modelOBJ->SetScale(50.0f, 50.0f, 50.0f);
	modelOBJ->SetName("ALEX-MODEL_OBJ");
	modelOBJ->SetPosition(660, 12, -16);
	modelOBJ->SetRotationY(-0.5);
	modelOBJ->SetMaterial(goldMaterial);
	AddObjectInDenugGame(modelOBJ);

	bobFBX = new Model(render);
	bobFBX->LoadModel("res/modelos/Bob.fbx", " ", bsp_manager);
	//bobFBX->SetPosition(0, 0, 0);
	bobFBX->SetScale(50.0f, 50.0f, 50.0f);
	bobFBX->SetName("Bob_Modelo");
	bobFBX->SetRotationX(-90);
	bobFBX->SetMaterial(goldMaterial);
	AddObjectInDenugGame(bobFBX);

	Entity* entity = bobFBX->GetEntityNode("Cabeza");
	entity->SetPosition(0.0f, 0.0f, 10.8299f);

	entity = bobFBX->GetEntityNode("Cuello");
	entity->SetPosition(0.0f, 0.0f, 9.05693f);

	entity = bobFBX->GetEntityNode("Torso");
	entity->SetPosition(0.0f, 0.0f, 5.99098f);

	entity = bobFBX->GetEntityNode("Brazo_Der");
	entity->SetPosition(4.140750f, 0.0f, 0.0f);

	entity = bobFBX->GetEntityNode("Brazo_Izq");
	entity->SetPosition(-4.140750f, 0.0f, 0.0f);

	entity = bobFBX->GetEntityNode("Mano_Der");
	entity->SetPosition(2.646000f, 0.0f, -1.800000f);

	entity = bobFBX->GetEntityNode("Mano_Izq");
	entity->SetPosition(-2.646000f, 0.0f, -1.800000f);

	entity = bobFBX->GetEntityNode("Pierna_Der");
	entity->SetPosition(1.78f, 0.0f, -4.000000f);

	entity = bobFBX->GetEntityNode("Pierna_Izq");
	entity->SetPosition(-1.78f, 0.0f, -4.000000f);

	entity = bobFBX->GetEntityNode("Pata_Der");
	entity->SetPosition(0.0f, -0.8f, -2.8f);

	entity = bobFBX->GetEntityNode("Pata_Izq");
	entity->SetPosition(0.0f, -0.8f, -2.8f);

	entity = bobFBX->GetEntityNode("Plane_BSP1");
	entity->SetPosition(18.2329f, -8.60411f, 6.35373f);

	/*entity = bobFBX->GetEntityNode("Plane_BSP2");
	entity->SetPosition(-14.2233f, 13.2296f, 6.35373f);

	entity = bobFBX->GetEntityNode("Plane_BSP3");
	entity->SetPosition(1.0468f, 1.05765f, 13.8085f);*/

	if (thirdPerson)
	{
		player3D = new PlayerController3D(render);
		player3D->SetMyModel(modelOBJ);
		player3D->SetRUN_SPEED(350);
		player3D->SetTURN_SPEED(400);
		camera->SetTargetThirdPerson(player3D);
		camera->SetTypeCamera(TypeCamera::ThirdPerson);
		camera->SetViewThirdPerson();
		camera->SetInitOffsetCameraThirdPersonX(0.0f);
		camera->SetInitOffsetCameraThirdPersonY(0.0f);
		camera->SetInitOffsetCameraThirdPersonZ(250.0f);
	}
	else 
	{
		camera->SetTypeCamera(TypeCamera::FirstPerson);
	}
	SetUseDebugWindows(true);

	SetEnableAABB_DebugGame(true);
}

void Game::UpdateGame(Windows *_window, Renderer *_render, Input *_input)
{
	//timeClock.FPS();
	if (player3D != NULL)
		player3D->Move(input, timeClock);


	/*
	Entity* entity = bobFBX->GetEntityNode("Mano_Der");
	cout << "Mano_Der: " << "(" << entity->transform.globalPosition.x
		<< "," << entity->transform.globalPosition.y
		<< "," << entity->transform.globalPosition.z
		<< ")" << endl;
	
	entity = bobFBX->GetEntityNode("Mano_Izq");

	cout << "Mano_Izq: " << "(" << entity->transform.globalPosition.x
		<< "," << entity->transform.globalPosition.y
		<< "," << entity->transform.globalPosition.z
		<< ")" << endl;

	entity = bobFBX->GetEntityNode("Plane_BSP3");

	cout << "Plane_BSP3: " << "(" << entity->transform.globalPosition.x
		<< "," << entity->transform.globalPosition.y
		<< "," << entity->transform.globalPosition.z
		<< ")" << endl;

	system("cls");

	entity = bobFBX->GetEntityNode("Plane_BSP2");

	cout << "Plane_BSP2: " << "(" << entity->transform.globalPosition.x
		<< "," << entity->transform.globalPosition.y
		<< "," << entity->transform.globalPosition.z
		<< ")" << endl;

	entity = bobFBX->GetEntityNode("Plane_BSP1");

	cout << "Plane_BSP1: " << "(" << entity->transform.globalPosition.x
		<< "," << entity->transform.globalPosition.y
		<< "," << entity->transform.globalPosition.z
		<< ")" << endl;
	*/



	if (input->GetKey(KeyBoard::KEY_RIGHT_SHIFT) && audio->GetIsPlayingAudio2D("res/audio/Dale Dale Boca.mp3"))
	{
		audio->StopAll();
	}
	if (input->GetKey(KeyBoard::KEY_LEFT_SHIFT) && !audio->GetIsPlayingAudio2D("res/audio/Dale Dale Boca.mp3"))
	{
		audio->PlayAudio2D("res/audio/Dale Dale Boca.mp3", true);
	}

	if (useCamera)
		TempInputCamera();

	//TempInputsPlayer1(windows, spriteAnimado);

	TempMoveLightWithID(windows, 2);

	

	//MODELS DRAW

	if (modelOBJ != NULL)
		modelOBJ->Draw(motorasoGui->GetIfWireFrameIsActive());

	if (bobFBX != NULL)
		bobFBX->Draw(motorasoGui->GetIfWireFrameIsActive());

	/*if (collisionManager != NULL)
	{
		if (collisionManager->CheckEntitiesOnFrustrum(camera, bobFBX))
			cout << "ESTA ADENTRO DEL FRUSTRUM" << endl;
	}*/
}

void Game::DestroyGame()
{
	entitysDebugInGame.clear();

	if (audio != NULL) {
		delete audio;
		audio = NULL;
	}
	//---------------------//
#pragma region MOTOR 2D
#pragma endregion

	//---------------------//
	if (goldMaterial != NULL) {
		delete goldMaterial;
		goldMaterial = NULL;
	}
	if (silverMaterial != NULL) {
		delete silverMaterial;
		silverMaterial = NULL;
	}
	if (esmeraldMaterial != NULL) {
		delete esmeraldMaterial;
		esmeraldMaterial = NULL;
	}
	if (greenRubberMaterial != NULL) {
		delete greenRubberMaterial;
		greenRubberMaterial = NULL;
	}

	if (mat_shape3 != NULL) {
		delete mat_shape3;
		mat_shape3 = NULL;
	}

	if (mat_shape4 != NULL) {
		delete mat_shape4;
		mat_shape4 = NULL;
	}

	if (animations != NULL)
		delete animations;

	if (modelOBJ != NULL) {
		delete modelOBJ;
		modelOBJ = NULL;
	}

	if (bobFBX != NULL) {
		delete bobFBX;
		bobFBX = NULL;
	}

	if (player3D != NULL)
		delete player3D;
}

void Game::TempColorInput(Windows* windows, Shape* shape)
{
	//---------------------//
#pragma region COLOR REGION
	
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

	
	if(!thirdPerson)
		camera->SetPosition(newPositionCamX, newPositionCamY, newPositionCamZ);
	
#pragma endregion
}

void Game::TempMoveLightWithID(Windows * windows, int id)
{
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_T))
	{
		SetLightPosition(id, glm::vec3(0, speed, 0));
	}
	if (input->GetKey(KeyBoard::KEY_G))
	{
		SetLightPosition(id, glm::vec3(0, -speed, 0));
	}
	if (input->GetKey(KeyBoard::KEY_H))
	{
		SetLightPosition(id, glm::vec3(speed, 0, 0));
	}
	if (input->GetKey(KeyBoard::KEY_F))
	{
		SetLightPosition(id, glm::vec3(-speed, 0, 0));
	}
	if (input->GetKey(KeyBoard::KEY_R))
	{
		SetLightPosition(id, glm::vec3(0, 0, speed));
	}
	if (input->GetKey(KeyBoard::KEY_Y))
	{
		SetLightPosition(id, glm::vec3(0, 0, -speed));
	}
}

void Game::InitMaterials()
{
	mat_shape3 = new Material();
	mat_shape3->SetAmbientMat(glm::vec3(0.5f * 2, 0.1f * 2, 0.1f * 2));
	mat_shape3->SetDiffuseMat(glm::vec3(0.5f * 2, 0.5f * 2, 0.4f * 2));
	mat_shape3->SetSpecularMat(glm::vec3(0.7f * 2, 0.7f * 2, 0.04f * 2));
	mat_shape3->SetNewShininess(1.0, 128);

	mat_shape4 = new Material();
	mat_shape4->SetAmbientMat(glm::vec3(0.1f * 2, 0.18725f * 2, 0.1745f * 2));
	mat_shape4->SetDiffuseMat(glm::vec3(0.396f * 2, 0.74151f * 2, 0.69102f * 2));
	mat_shape4->SetSpecularMat(glm::vec3(0.297254f * 2, 0.30829f * 2, 0.306678f * 2));
	mat_shape4->SetNewShininess(0.1f, 128);

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
