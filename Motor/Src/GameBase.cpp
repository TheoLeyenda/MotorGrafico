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

	render->SetShader(vertexShader, fragmentShader);

	tri->SetVertexsAttrib(render->GetShader());

	glUseProgram(render->GetShader());

	//Limpiar shader y buffer 
	render->ClearShader();
	render->UnbindBuffer();

	while (!windows->CheckGLFWwindowShouldClose()) 
	{	
		tri->SetSolidColor(1.0f, 0.0f, 0.0f, 1.0f, vertexShader, fragmentShader);

		tri->Draw(GL_TRIANGLES, 3, render->GetShader(), windows);

		glfwPollEvents();
	}

	glDeleteProgram(render->GetShader());
	glfwTerminate();
	return 0; 
}