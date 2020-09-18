#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "vertexShader.h"
#include "fragmentShader.h"
#include "GameBase.h"

//#define ASSERT(x) if (!(x)) __debugbreak();

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
	
	bool triOn = true;
	bool quadOn = false;

	unsigned int shaderProgram1;
	unsigned int shaderProgram2;

	if (triOn){
		tri->InitShape(GL_TRIANGLES);
		shaderProgram1 = render->CreateShaderProgram(vertexShader, fragmentShader);
		glUseProgram(shaderProgram1);
	}
	if (quadOn){
		quad->InitShape(GL_QUADS);
		shaderProgram2 = render->CreateShaderProgram(vertexShader, fragmentShader);
		glUseProgram(shaderProgram2);
	}

	while (!windows->CheckGLFWwindowShouldClose()) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//render->GLClearError();
		if (triOn && shaderProgram1){ tri->Draw(GL_TRIANGLES, 3,  shaderProgram1); }
		else if (quadOn && shaderProgram2){ quad->Draw(GL_QUADS, 4, shaderProgram2); }
		//ASSERT(render->GLLogCall());

		windows->SwapBuffersWindows();
		glfwPollEvents();
	}
	if(triOn)
		glDeleteProgram(shaderProgram1);
	if(quadOn)
		glDeleteProgram(shaderProgram2);
	glfwTerminate();
	return 0; 
}