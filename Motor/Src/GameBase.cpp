#include "GameBase.h"

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
	camera = new Entity(render);
	collisionManager = new CollisionManager();
	if (!initGLFW || windows == NULL)
		return INIT_ERROR;

	windows->CheckCreateWindows();
	windows->CreateContextWindows();
	render->GLEWInit();
	render->SetShader();

	render->SetProjection();
	camera->SetPosition(0.0f, 0.0f, 1.0f);
	render->SetView(camera->transform.position);

	
	render->drawCamera(render->GetShaderColor(),camera->GetInternalData().model);

	return 0;
}

void GameBase::UpdateEngine()
{
	while (!windows->CheckGLFWwindowShouldClose())
	{
		render->BeignDraw();
		timeClock.tick();
		//std::cout << "Time in SECONDS = " << timeClock.GetGlobalTime() << std::endl;
		//---------------------//
		render->SetView(camera->transform.position);
		render->drawCamera(render->GetShaderColor(), camera->GetInternalData().model);
		render->drawCamera(render->GetShaderTexture(), camera->GetInternalData().model);
		UpdateGame(windows, render, input);
		//---------------------//
		
		glfwPollEvents();
		//---------------------//
		render->EndDraw(windows);
	}
}

void GameBase::DestroyEngine()
{
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