
#include "GameBase.h"
#include "glew.h"
#include "GLFW/glfw3.h"

GameBase::GameBase()
{
	windows = new Windows(640, 480, "MOTORASO", NULL, NULL);
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
		windows->SwapBuffersWindows();
		glfwPollEvents();
	}
	glfwTerminate();
	return 0; 
}