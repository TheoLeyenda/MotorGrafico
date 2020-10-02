//#include <glew.h>
//#include <GLFW/glfw3.h>
#include "GameBase.h"
//#define ASSERT(x) if (!(x)) __debugbreak();
#include "fragmentShader.h"
#include "vertexShader.h"
GameBase::GameBase()
{
	glfwInit();

	windows = new Windows(1080, 680, "MOTORASO");
	render = new Renderer();
	quad = new Shape(render);
	tri = new Shape(render);
}
GameBase::~GameBase() 
{
	if (windows != NULL) 
		delete windows;
	if (quad != NULL)
		delete quad;
	if (tri != NULL)
		delete tri;
	if (render != NULL)
		delete render;
}
int GameBase::Init()
{ 
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

	//VALORES DE TESTEO
	float posX = 0;
	float posY = 0;
	float speed = 0.05f;
	const float posZ = 1;

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
	//---------------------//
	//CONTROLES
	//WASD = Movimiento.
	//ENTER = Cambio de color.
	// KP7 & KP9 = Escala
	// KP7 & KP9  = Rotate on X AXIS
	// KP4 & KP6  = Rotate on Y AXIS
	// KP1 & KP3  = Rotate on Z AXIS
	
	while (!windows->CheckGLFWwindowShouldClose()) 
	{	
		//system("cls");
		//std::cout << "X: " << posX << std::endl;
		//std::cout << "Y: " << posY << std::endl;
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

		tri->Draw(GL_TRIANGLES, 3, render->GetShader(), windows, tri->GetInternalData().model, render->getViewMat(), render->getProjMat());
		//quad->Draw(GL_QUADS, 4, render->GetShader(), windows, quad->GetInternalData().model,render->getViewMat(),render->getProjMat());
		//INPUT DE MOVIMIENTO
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_W) == GLFW_PRESS)
		{
			posY = posY + speed;
			tri->SetPosition(posX, posY, posZ);
			//quad->SetPosition(posX, posY, posZ);
		}
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_S) == GLFW_PRESS)
		{
			posY = posY - speed;
			tri->SetPosition(posX, posY, posZ);
			//quad->SetPosition(posX, posY, posZ);
		}
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_D) == GLFW_PRESS)
		{
			posX = posX + speed;
			tri->SetPosition(posX, posY, posZ);
			//quad->SetPosition(posX, posY, posZ);
		}
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_A) == GLFW_PRESS)
		{
			posX = posX - speed;
			tri->SetPosition(posX, posY, posZ);
			//quad->SetPosition(posX, posY, posZ);
		}
		//-------------------//

		//INPUT DE ROTACION
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_KP_1) == GLFW_PRESS)
		{
			rotZ = rotZ + speedRotation;
			tri->SetRotationZ(rotZ);
			//quad->SetRotationZ(rotZ);
		}
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_KP_3) == GLFW_PRESS)
		{
			rotZ = rotZ - speedRotation;
			tri->SetRotationZ(rotZ);
			//quad->SetRotationZ(rotZ);
		}

		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_KP_4) == GLFW_PRESS)
		{
			rotY = rotY + speedRotation;
			tri->SetRotationY(rotY);
			//quad->SetRotationY(rotY);
		}
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_KP_6) == GLFW_PRESS)
		{
			rotY = rotY - speedRotation;
			tri->SetRotationY(rotY);
			//quad->SetRotationY(rotY);
		}

		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_KP_7) == GLFW_PRESS)
		{
			rotX = rotX + speedRotation;
			tri->SetRotationX(rotX);
			//quad->SetRotationX(rotX);
		}
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_KP_9) == GLFW_PRESS)
		{
			rotX = rotX - speedRotation;
			tri->SetRotationX(rotX);
			//quad->SetRotationX(rotX);
		}
		//------------------//

		//INPUT DE ESCALA
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_KP_8) == GLFW_PRESS)
		{
			scalX = scalX + speedScale;
			scalY = scalY + speedScale;
			scalZ = scalZ + speedScale;
			tri->SetScale(scalX, scalY, scalZ);
			//quad->SetScale(scalX, scalY, scalZ);
		}
		if (glfwGetKey(windows->GetWindowsPtr(), GLFW_KEY_KP_2) == GLFW_PRESS)
		{
			scalX = scalX - speedScale;
			scalY = scalY - speedScale;
			scalZ = scalZ - speedScale;
			tri->SetScale(scalX, scalY, scalZ);
			//quad->SetScale(scalX, scalY, scalZ);
		}
		//---------------------//
		glfwPollEvents();
	}

	glDeleteProgram(render->GetShader());
	glfwTerminate();
	return 0; 
}