
#include "glew.h"
#include "GLFW/glfw3.h"
#include "GameBase.h"

GameBase::GameBase()
{
	glfwInit();

	windows = new Windows(1080, 680, "MOTORASO");
}
GameBase::~GameBase() 
{
	if (windows != NULL) 
	{
		delete windows;
	}
}
int GameBase::Init()
{ 
	if (!glfwInit() || windows == NULL)
		return -1;

	windows->CheckCreateWindows();

	windows->CreateContextWindows();

	while (!windows->CheckGLFWwindowShouldClose()) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		windows->SwapBuffersWindows();
		glfwPollEvents();
	}
	glfwTerminate();
	return 0; 
}