//#include <glew.h>
//#include <GLFW/glfw3.h>
#include "GameBase.h"
//#define ASSERT(x) if (!(x)) __debugbreak();
//#include "fragmentShader.h"
//#include "vertexShader.h"
#include "glew.h"
#include "GLFW/glfw3.h"

GameBase::GameBase() {}
GameBase::~GameBase() {}

int GameBase::InitEngine()
{
	bool initGLFW = glfwInit();

	windows = new Windows(1080, 680, "MOTORASO");
	render = new Renderer();
	input = new Input(windows->GetWindowsPtr());
	collisionManager = new CollisionManager();
	if (!initGLFW || windows == NULL)
		return INIT_ERROR;

	windows->CheckCreateWindows();
	windows->CreateContextWindows();
	render->GLEWInit();
	render->SetShader();

	render->SetProjection();
	render->SetView(glm::vec3(0.0f, 0.0f, 1.0f));

	render->drawCamera(render->GetShaderColor());

	return 0;
	//CONTROLES
	//WASD = Movimiento.
	//ENTER = Cambio de color.
	// KP7 & KP9 = Escala
	// KP7 & KP9  = Rotate on X AXIS
	// KP4 & KP6  = Rotate on Y AXIS
	// KP1 & KP3  = Rotate on Z AXIS
}

void GameBase::UpdateEngine()
{
	while (!windows->CheckGLFWwindowShouldClose())
	{
		render->BeignDraw();
		timeClock.tick();
		//std::cout << "Time in SECONDS = " << timeClock.GetGlobalTime() << std::endl;
		//---------------------//
		render->drawCamera(render->GetShaderColor());
		render->drawCamera(render->GetShaderTexture());
		UpdateGame(windows, render, input);
		//cin.get();
		//---------------------//
		glfwPollEvents();
		//---------------------//

		render->EndDraw(windows);
		//cin.get();
	}
}

void GameBase::DestroyEngine()
{
	glDeleteProgram(render->GetShaderColor());
	glfwTerminate();

	if (input != NULL)
		delete input;
	if (windows != NULL)
		delete windows;
	if (render != NULL)
		delete render;
	if (collisionManager != NULL)
		delete collisionManager;
}

Time& GameBase::GetTimeClock()
{
	return timeClock;
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