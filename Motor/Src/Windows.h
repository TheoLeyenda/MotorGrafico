#ifndef WINDOWS_H
#define WINDOWS_H
#define TAM 100

#include "PrivateClass/Export.h"

//#include "GLFW/glfw3.h"
struct GLFWwindow;

class ENGINE_API Windows{
private:
	int sizeX;
	int sizeY;
	char nameWindows[TAM];
	bool fullscreen;
public:
	Windows();
	Windows(int x, int y, const char* name);
	~Windows();
	void SetSize(int _sizeX, int _sizeY);
	int GetSizeX();
	int GetSizeY();
	void SetNameWindows(char name[]);
	void SetFullscreen(bool _fullscreen);
	GLFWwindow* GetWindowsPtr();
	int CheckCreateWindows();
	void CreateContextWindows();
	bool CheckGLFWwindowShouldClose();
	//void ClearWindows();
	void SwapBuffersWindows();
	//void EventsWindows();
};
#endif