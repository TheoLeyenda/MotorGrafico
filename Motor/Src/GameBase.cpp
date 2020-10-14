//#include <glew.h>
//#include <GLFW/glfw3.h>
#include "GameBase.h"
//#define ASSERT(x) if (!(x)) __debugbreak();
#include "fragmentShader.h"
#include "vertexShader.h"

GameBase::GameBase(){}
GameBase::~GameBase(){}

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

void GameBase::TempInputs(Windows* windows, Shape* tri) 
{
	//INPUT DE MOVIMIENTO
	if (input->GetKey(windows->GetWindowsPtr(), KeyBoard::KEY_W)) 
	{
		posY = posY + speed;
		tri->SetPosition(posX, posY, posZ);
		//quad->SetPosition(posX, posY, posZ);
	}
	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_S))
	{
		posY = posY - speed;
		tri->SetPosition(posX, posY, posZ);
		//quad->SetPosition(posX, posY, posZ);
	}
	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_D))
	{
		posX = posX + speed;
		tri->SetPosition(posX, posY, posZ);
		//quad->SetPosition(posX, posY, posZ);
	}
	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_A))
	{
		posX = posX - speed;
		tri->SetPosition(posX, posY, posZ);
		//quad->SetPosition(posX, posY, posZ);
	}
	//-------------------//

	//INPUT DE ROTACION
	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_KP_4))
	{
		rotZ = rotZ + speedRotation;
		tri->SetRotationZ(rotZ);
		//quad->SetRotationZ(rotZ);
	}
	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_KP_6))
	{
		rotZ = rotZ - speedRotation;
		tri->SetRotationZ(rotZ);
		//quad->SetRotationZ(rotZ);
	}

	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_KP_1))
	{
		rotY = rotY + speedRotation;
		tri->SetRotationY(rotY);
		//quad->SetRotationY(rotY);
	}
	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_KP_3))
	{
		rotY = rotY - speedRotation;
		tri->SetRotationY(rotY);
		//quad->SetRotationY(rotY);
	}

	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_KP_7))
	{
		rotX = rotX + speedRotation;
		tri->SetRotationX(rotX);
		//quad->SetRotationX(rotX);
	}
	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_KP_9))
	{
		rotX = rotX - speedRotation;
		tri->SetRotationX(rotX);
		//quad->SetRotationX(rotX);
	}
	//------------------//

	//INPUT DE ESCALA
	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_KP_8))
	{
		scalX = scalX + speedScale;
		scalY = scalY + speedScale;
		scalZ = scalZ + speedScale;
		tri->SetScale(scalX, scalY, scalZ);
		//quad->SetScale(scalX, scalY, scalZ);
	}
	if (glfwGetKey(windows->GetWindowsPtr(), KeyBoard::KEY_KP_2))
	{
		scalX = scalX - speedScale;
		scalY = scalY - speedScale;
		scalZ = scalZ - speedScale;
		tri->SetScale(scalX, scalY, scalZ);
		//quad->SetScale(scalX, scalY, scalZ);
	}
}

int GameBase::InitGame()
{ 
	glfwInit();

	windows = new Windows(1080, 680, "MOTORASO");
	render = new Renderer();
	input = new Input();

	quad = new Shape(render);
	tri = new Shape(render);


	if (!glfwInit() || windows == NULL)
		return -1;

	windows->CheckCreateWindows();
	windows->CreateContextWindows();
	render->GLEWInit();
	
	tri->InitShape(GL_TRIANGLES);
	//quad->InitShape(GL_QUADS);

	render->SetShader();

	tri->SetVertexsAttrib(render->GetShader());

	//quad->SetVertexsAttrib(render->GetShader());

	glUseProgram(render->GetShader());

	//Limpiar shader y buffer 
	render->ClearShader();
	render->UnbindBuffer();

	//---------------------//
	//CONTROLES
	//WASD = Movimiento.
	//ENTER = Cambio de color.
	// KP7 & KP9 = Escala
	// KP7 & KP9  = Rotate on X AXIS
	// KP4 & KP6  = Rotate on Y AXIS
	// KP1 & KP3  = Rotate on Z AXIS
	return 0;
}

void GameBase::Update()
{
	while (!windows->CheckGLFWwindowShouldClose())
	{
		//---------------------//
		if (enableSetSolidColor)
		{
			tri->SetSolidColor(r, g, b, a, vertexShader, fragmentShader);
			//quad->SetSolidColor(r, g, b, a, vertexShader, fragmentShader);
			if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			}
		}
		//---------------------//
		TempInputs(windows, tri);
		//---------------------//
		tri->Draw(GL_TRIANGLES, 3, render->GetShader(), windows, tri->GetInternalData().model);
		//---------------------//
		glfwPollEvents();
		//---------------------//
	}
}

void GameBase::DestroyGame()
{
	glDeleteProgram(render->GetShader());
	glfwTerminate();

	if (windows != NULL)
		delete windows;
	if (input != NULL)
		delete input;
	if (render != NULL)
		delete render;

	if (quad != NULL)
		delete quad;
	if (tri != NULL)
		delete tri;
}
