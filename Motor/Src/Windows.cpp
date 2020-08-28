#include "Windows.h"

Windows::Windows()
{
	RefWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
}

Windows::Windows(int x, int y, const char* name, GLFWmonitor * monitor, GLFWwindow * share)
{
	RefWindow = glfwCreateWindow(x, y, name, monitor, share);
}

Windows::~Windows()
{
	glfwTerminate();
}

/*void Windows::ClearWindows()
{
	glClear(GL_COLOR_BUFFER_BIT);
}*/

void Windows::SwapBuffersWindows()
{
	glfwSwapBuffers(RefWindow);
}

/*void Windows::EventsWindows()
{
	glfwPollEvents();
}*/

void Windows::SetSize(int _sizeX, int _sizeY)
{
	sizeX = _sizeX;
	sizeY = _sizeY;
	//EJECUTAR FUNCION QUE SETEA LOS VALORES DE LA PANTALLA.
}

int Windows::GetSizeX()
{
	return sizeX;
}

int Windows::GetSizeY()
{
	return sizeY;
}

void Windows::SetNameWindows(char name[])
{
	//SETEARIA EL NOMBRE DE LA VENTANA.
}

void Windows::SetFullscreen(bool _fullscreen)
{
	//HARIA QUE LA PANTALLA SEA FULL.
}

/*int Windows::CheckGLFWInit()
{
	if (!glfwInit())
		return -1;
}*/

int Windows::CheckCreateWindows()
{
	if (!RefWindow)
	{
		glfwTerminate();
		return -1;
	}
}

void Windows::CreateContextWindows()
{
	glfwMakeContextCurrent(RefWindow);
}

bool Windows::CheckGLFWwindowShouldClose()
{
	return glfwWindowShouldClose(RefWindow);
}


