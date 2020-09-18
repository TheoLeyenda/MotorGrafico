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
	if (glewInit() != GLEW_OK)
		std::cout << "Error on GLEW!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	bool triOn = true;
	bool quadOn = false;

	if (triOn){
		tri->InitShape(GL_TRIANGLES);
	}
	if (quadOn){
		quad->InitShape(GL_QUADS);
	}
	render->SetShader(vertexShader, fragmentShader);
	glUseProgram(render->GetShader());
	unsigned int shaderAux = render->GetShader();
	while (!windows->CheckGLFWwindowShouldClose()) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		shaderAux = render->GetShader();
		
		//render->GLClearError();
		if (triOn)
		{ 
			tri->SetSolidColor(1.0f, 1.0f, 0.0f, 1.0f, vertexShader, fragmentShader);
			tri->Draw(GL_TRIANGLES, 3, shaderAux);
			
		}
		else if (quadOn)
		{ 
			quad->SetSolidColor(1.0f, 0.0f, 1.0f, 1.0f, vertexShader, fragmentShader);
			quad->Draw(GL_QUADS, 4, shaderAux);
			
		}
		//ASSERT(render->GLLogCall());

		windows->SwapBuffersWindows();
		glfwPollEvents();
	}

	glDeleteProgram(render->GetShader());
	glfwTerminate();
	return 0; 
}