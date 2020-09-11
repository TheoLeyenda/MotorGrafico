#include <glew.h>
#include <GLFW/glfw3.h>
#include "GameBase.h"

GameBase::GameBase()
{
	glfwInit();

	windows = new Windows(1080, 680, "MOTORASO");
	render = new Renderer();
	shape = new Shape(render);
}
GameBase::~GameBase() 
{
	if (windows != NULL) 
		delete windows;
	if (shape != NULL)
		delete shape;
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
	//ESTO DESPUES VA EN SHAPE Y SHAPE RECIBE DE ENTITY EL RENDERER (uwu).
	float _vertexBuffer[] = {
		-0.5f , -0.5f , 1.0f , 0.0f ,0.0f,
		 0.5f , -0.5f , 0.0f , 1.0f ,0.0f,
		 0.0f ,  0.5f , 0.0f , 0.0f, 1.0f
	};
	render->CreateVbo(_vertexBuffer);
	render->CreateShaderProgram();

	while (!windows->CheckGLFWwindowShouldClose()) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		windows->SwapBuffersWindows();
		glfwPollEvents();
	}
	glfwTerminate();
	return 0; 
}