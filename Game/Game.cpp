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
	
	AddObjectInDenugGame(GetLight(1));
	AddObjectInDenugGame(GetLight(2));
	AddObjectInDenugGame(GetLight(6));
	AddObjectInDenugGame(GetLight(0));
	AddObjectInDenugGame(GetLight(87));

	ChangeColorLight(1, red);
	ChangeColorLight(2, yellow);
	ChangeColorLight(6, cyan);
	ChangeColorLight(87, brown);
	ChangeColorLight(0, magenta);

	GetMyLightsID();

	model = new Model(render);
	model->LoadModel("res/modelos/source/pose3.fbx", "res/modelos/textures/");
	model->SetScale(1.0f, 1.0f, 1.0f);
	model->SetName("LOCA DEL DRAGON");
	model->SetRotationX(-1.45);
	model->SetRotationY(0);
	model->SetRotationZ(-0.5);
	model->SetPosition(1300, 0, 0);
	model->SetMaterial(goldMaterial);

	model2 = new Model(render);
	model2->LoadModel("res/modelos/pochita.fbx", "res/modelos/");
	model2->SetScale(50, 50, 50);
	model2->SetName("POCHITA");
	model2->SetMaterial(greenRubberMaterial);

	model3 = new Model(render);
	model3->LoadModel("res/modelos/merkava-tank/Merkava_Tank.obj", "res/modelos/merkava-tank/textures/");
	model3->SetScale(0.5, 0.5, 0.5);
	model3->SetPosition(1000, 10, 10);
	model3->SetName("MERKAVA TANQUE PAPARDOOO");
	model3->SetMaterial(goldMaterial);

	AddObjectInDenugGame(model);
	AddObjectInDenugGame(model2);
	AddObjectInDenugGame(model3);

	pyramid = new Primitive3D(render,Pyramid);
	pyramid->SetPosition(500.0f, 250.0f, -50.0f);
	if(useSkybox)
		pyramid->SetScale(5000.0f, 5000.0f, 5000.0f);
	else
		pyramid->SetScale(50.0f, 50.0f, 50.0f);

	pyramid->SetRotationY(6.0f);
	pyramid->SetNewMaterial(silverMaterial);
	pyramid->SetNewMaterial(textureMaterialForLight);
	pyramid->LoadTexture("res/texturas/bokitaElMasGrandePapa.png", false);
	pyramid->SetName("pyramid");

	AddObjectInDenugGame(pyramid);

	cube = new Primitive3D(render, Cube);
	cube->SetPosition(300, 100.0f, -50.0f);
	cube->SetScale(50.0f, 50.0f, 50.0f);
	cube->SetNewMaterial(greenRubberMaterial);
	cube->SetName("cube");
	
	AddObjectInDenugGame(cube);

	cube2 = new Primitive3D(render, Cube);
	cube2->SetPosition(420.0f, 100.0f, -50.0f);
	cube2->SetScale(50.0f, 50.0f, 50.0f);
	cube2->SetNewMaterial(goldMaterial);
	cube2->SetName("cube2");

	AddObjectInDenugGame(cube2);

	cube3 = new Primitive3D(render, Cube);
	cube3->SetPosition(360.0f, 250.0f, -50.0f);
	cube3->SetScale(50.0f, 50.0f, 50.0f);
	cube3->SetNewMaterial(textureMaterialDefault);
	cube3->LoadTexture("res/texturas/Facharda.jpg", false);
	cube3->SetName("cube3");
	
	AddObjectInDenugGame(cube3);

	audio = new Audio(render);
	audio->SetName("audio");
	AddObjectInDenugGame(audio);

	//shape1 = new Shape(render,TypeShape::QUAD, "res/texturas/Algun dia.png");
	//shape1->SetPosition(-190.0f, 200.0f, 10.0);
	//shape1->SetScale(120.0f, 120.0f, 120.0f);
	//shape1->SetName("Shape1");
	//AddObjectInDenugGame(shape1);
	
	//shape2 = new Shape(render, TypeShape::TRIANGLE, "res/texturas/bokitaElMasGrandePapa.png");
	//shape2->SetPosition(-320.0f, 200.0f, 10.0);
	//shape2->SetScale(120.0f, 120.0f, 120.0f);
	//shape2->SetNewMaterial(textureMaterialForLight);
	//shape2->SetName("Shape2");
	//AddObjectInDenugGame(shape2);

	shape3 = new Shape(render, TypeShape::QUAD);
	shape3->SetPosition(-450.0f, 200.0f, 10.0);
	shape3->SetScale(120.0f, 120.0f, 120.0f);
	shape3->SetNewMaterial(mat_shape3);
	shape3->SetName("Shape3");
	AddObjectInDenugGame(shape3);

	shape4 = new Shape(render, TypeShape::TRIANGLE);
	shape4->SetPosition(-580.0f, 200.0f, 10.0);
	shape4->SetScale(120.0f, 120.0f, 120.0f);
	shape4->SetNewMaterial(mat_shape4);
	shape4->SetName("Shape4");
	AddObjectInDenugGame(shape4);

	sprite = new Sprite(render,"res/texturas/nave.png", true);
	sprite->SetPosition(-360.0f, 350.0f, 10.0);
	sprite->SetScale(120.0f, 120.0f, 120.0f);
	sprite->SetRotationZ(91.1f);
	sprite->SetName("Sprite");
	AddObjectInDenugGame(sprite);

	//spriteAnimado = new Sprite(render, "res/texturas/PlayerShit.png", true);
	//spriteAnimado->SetPosition(windows->GetSizeX() / 2, windows->GetSizeY() / 2, 0.0f);
	//spriteAnimado->SetPosition(0, windows->GetSizeY()/2, 0.0f);
	//spriteAnimado->SetScale(120.0f, 120.0f, 120.0f);
	//spriteAnimado->SetRotationZ(91.1f);
	//spriteAnimado->SetName("SpriteAnimado");
	//AddObjectInDenugGame(spriteAnimado);

	//animations = new Animation();
	//
	//float durationAnim = 0.75f;
	//// ANIMACION CAMINATA HACIA ARRIBA
	//animations->AddFrame((480 - 60 * 8), 0.0f, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 7), 0.0f, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 6), 0.0f, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 5), 0.0f, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 4), 0.0f, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 3), 0.0f, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 2), 0.0f, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 1), 0.0f, 60, 60, 480, 240, durationAnim);
	//animations->AddAnimation();
	//
	//// ANIMACION CAMINATA HACIA DERECHA
	//animations->AddFrame((480 - 60 * 8), 60, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 7), 60, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 6), 60, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 5), 60, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 4), 60, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 3), 60, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 2), 60, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 1), 60, 60, 60, 480, 240, durationAnim);
	//animations->AddAnimation();
	//
	//// ANIMACION CAMINATA HACIA IZQUIERDA
	//animations->AddFrame((480 - 60 * 8), 120, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 7), 120, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 6), 120, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 5), 120, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 4), 120, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 3), 120, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 2), 120, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 1), 120, 60, 60, 480, 240, durationAnim);
	//animations->AddAnimation();
	//
	//// ANIMACION CAMINATA HACIA ABAJO
	//animations->AddFrame((480 - 60 * 8), 180, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 7), 180, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 6), 180, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 5), 180, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 4), 180, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 3), 180, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 2), 180, 60, 60, 480, 240, durationAnim);
	//animations->AddFrame((480 - 60 * 1), 180, 60, 60, 480, 240, durationAnim);
	//animations->AddAnimation();
	//
	//spriteAnimado->SetAnimation(animations);
	//spriteAnimado->SetAttribsSprite();

	SetUseDebugWindows(true);
}

void Game::UpdateGame(Windows *_window, Renderer *_render, Input *_input)
{
	//timeClock.FPS();

	if (input->GetKey(KeyBoard::KEY_RIGHT_SHIFT) && audio->GetIsPlayingAudio2D("res/audio/Dale Dale Boca.mp3"))
	{
		audio->StopAll();
	}
	if (input->GetKey(KeyBoard::KEY_LEFT_SHIFT) && !audio->GetIsPlayingAudio2D("res/audio/Dale Dale Boca.mp3"))
	{
		audio->PlayAudio2D("res/audio/Dale Dale Boca.mp3", true);
		RemoveObjectInDebugGame(cube);
		AddObjectInDenugGame(cube2);
	}

	if (rotateBokitaSkybox && useSkybox)
	{
		pyramid->SetRotationY(pyramid->transform.rotation.y - speedAutomaticRotation);
	}

	if (useCamera)
		TempInputCamera();


	//TempInputsPlayer1(windows, spriteAnimado);

	TempMoveLightWithID(windows, 2);

	if (shape1 != NULL) 
		shape1->Draw(motorasoGui->GetIfWireFrameIsActive());

	if (shape2 != NULL)
		shape2->Draw(motorasoGui->GetIfWireFrameIsActive());

	if (shape3 != NULL)
		shape3->Draw(motorasoGui->GetIfWireFrameIsActive());

	if (shape4 != NULL)
		shape4->Draw(motorasoGui->GetIfWireFrameIsActive());

	if(pyramid != NULL)
		pyramid->Draw(motorasoGui->GetIfWireFrameIsActive());
	if (cube != NULL)
		cube->Draw(motorasoGui->GetIfWireFrameIsActive());
	if(cube2 != NULL)
		cube2->Draw(motorasoGui->GetIfWireFrameIsActive());
	if(cube3 != NULL)
		cube3->Draw(motorasoGui->GetIfWireFrameIsActive());

	if (sprite != NULL)
		sprite->Draw(GetTimeClock());

	if (spriteAnimado != NULL)
		spriteAnimado->Draw(GetTimeClock());

	if (model != NULL)
		model->Draw(motorasoGui->GetIfWireFrameIsActive());
	if (model2 != NULL)
		model2->Draw(motorasoGui->GetIfWireFrameIsActive());
	if (model3 != NULL)
		model3->Draw(motorasoGui->GetIfWireFrameIsActive());
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
	if (shape1 != NULL) {
		delete shape1;
		shape1 = NULL;
	}
	if (shape2 != NULL) {
		delete shape2;
		shape2 = NULL;
	}
#pragma endregion

	if (cube != NULL) {
		delete cube;
		cube = NULL;
	}
	if (cube2 != NULL) {
		delete cube2;
		cube2 = NULL;
	}
	if (cube3 != NULL) {
		delete cube3;
		cube3 = NULL;
	}
	if (pyramid != NULL) {
		delete pyramid;
		pyramid = NULL;
	}
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

	if (sprite != NULL)
		delete sprite;

	if (spriteAnimado != NULL)
		delete spriteAnimado;

	if (animations != NULL)
		delete animations;

	if (model != NULL) {
		delete model;
		model = NULL;
	}
	if (model2 != NULL) {
		delete model2;
		model2 = NULL;
	}
	if (model3 != NULL) {
		delete model3;
		model3 = NULL;
	}
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

	//MANEJO DE DATOS
	camera->SetPosition(newPositionCamX, newPositionCamY, newPositionCamZ);

	camera->SetView();
	//render->RotateCamera(newRotationCamZ, camera->GetInternalData().model);
	
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
