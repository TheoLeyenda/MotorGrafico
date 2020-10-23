#include "..\Motor\Src\GameBase.h"
#include "..\Motor\Src\GameBase.h"
#include "..\Motor\Src\GameBase.h"
#include "Game.h"

//VALORES DE TESTEO
float posX = 0;
float posY = 0;
float speed = 0.05f;
const float posZ = 0;

float rotX = 0;
float rotY = 0;
float rotZ = 0;
float speedRotation = 0.05f;

float scalX = 1;
float scalY = 1;
float scalZ = 1;
float speedScale = 0.05f;

float r = 1.0f;
float g = 0.0f;
float b = 0.0f;
float a = 1.0f;
bool enableSetSolidColor = false;

Game::Game():GameBase(){}

Game::~Game(){}



void Game::InitGame()
{
	quad = new Shape(GetRenderer());
	tri = new Shape(GetRenderer());

	tri->InitShape(TypeShape::TRIANGLE);

	tri->SetVertexsAttrib(GetRenderer()->GetShader());
	//---------------------//
}

void Game::UpdateGame(Windows *_window, Renderer *_render, Input *_input)
{
	tri->Draw(TypeShape::TRIANGLE, 3, _render->GetShader(), _window, tri->GetInternalData().model);
	TempInputs(_window, tri);
}

void Game::DestroyGame()
{
	if (quad != NULL)
		delete quad;
	if (tri != NULL)
		delete tri;
}


void GameBase::TempInputs(Windows* windows, Shape* tri)
{
	if (enableSetSolidColor)
	{
		tri->SetSolidColor(r, g, b, a);
		//quad->SetSolidColor(r, g, b, a, vertexShader, fragmentShader);
		if (input->GetKey(KeyBoard::KEY_ENTER))
		{
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
	}
	//INPUT DE MOVIMIENTO
	if (input->GetKey(KeyBoard::KEY_W))
	{
		posY = posY + speed;
		tri->SetPosition(posX, posY, posZ);
	}
	if (input->GetKey(KeyBoard::KEY_S))
	{
		posY = posY - speed;
		tri->SetPosition(posX, posY, posZ);
	}
	if (input->GetKey(KeyBoard::KEY_D))
	{
		posX = posX + speed;
		tri->SetPosition(posX, posY, posZ);
	}
	if (input->GetKey(KeyBoard::KEY_A))
	{
		posX = posX - speed;
		tri->SetPosition(posX, posY, posZ);
	}
	//-------------------//

	//INPUT DE ROTACION
	if (input->GetKey(KeyBoard::KEY_KP_4))
	{
		rotZ = rotZ + speedRotation;
		tri->SetRotationZ(rotZ);
	}
	if (input->GetKey(KeyBoard::KEY_KP_6))
	{
		rotZ = rotZ - speedRotation;
		tri->SetRotationZ(rotZ);
	}

	if (input->GetKey(KeyBoard::KEY_KP_1))
	{
		rotY = rotY + speedRotation;
		tri->SetRotationY(rotY);
	}
	if (input->GetKey(KeyBoard::KEY_KP_3))
	{
		rotY = rotY - speedRotation;
		tri->SetRotationY(rotY);
	}

	if (input->GetKey(KeyBoard::KEY_KP_7))
	{
		rotX = rotX + speedRotation;
		tri->SetRotationX(rotX);
	}
	if (input->GetKey(KeyBoard::KEY_KP_9))
	{
		rotX = rotX - speedRotation;
		tri->SetRotationX(rotX);
	}
	//------------------//

	//INPUT DE ESCALA
	if (input->GetKey(KeyBoard::KEY_KP_8))
	{
		scalX = scalX + speedScale;
		scalY = scalY + speedScale;
		scalZ = scalZ + speedScale;
		tri->SetScale(scalX, scalY, scalZ);
	}
	if (input->GetKey(KeyBoard::KEY_KP_2))
	{
		scalX = scalX - speedScale;
		scalY = scalY - speedScale;
		scalZ = scalZ - speedScale;
		tri->SetScale(scalX, scalY, scalZ);
	}
}

Windows * GameBase::GetWindows()
{
	return windows;
}

Renderer * GameBase::GetRenderer()
{
	return render;
}

Input * GameBase::GetInput()
{
	return input;
}

