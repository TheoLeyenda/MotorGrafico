#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "vertexShader.h"
#include "fragmentShader.h"
#include "GameBase.h"

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
	if (glewInit() != GLEW_OK)
		std::cout << "Error on GLEW!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	//quad->InitShape(GL_QUADS);
	quad->InitShape(GL_QUADS);
	unsigned int shaderProgram = render->CreateShaderProgram(vertexShader,fragmentShader);
	glUseProgram(shaderProgram);

	while (!windows->CheckGLFWwindowShouldClose()) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		render->Draw(); //ACA SE VA A BINDEAR EL VBUFFER Y EL SHADER TODO EL TIEMPO
		//quad->DrawShape(GL_QUADS);
		quad->DrawShape(GL_QUADS);

		windows->SwapBuffersWindows();
		glfwPollEvents();
	}
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0; 
}