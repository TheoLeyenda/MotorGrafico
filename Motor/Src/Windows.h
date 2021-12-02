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

	int windowScale = 75;

	int height = windowScale * 9;
	int with = windowScale * 16;
public:
	Windows();
	Windows(int x, int y, const char* name);
	Windows(const char* name);
	~Windows();
	int GetWindowsScale() { return windowScale; }
	int GetWith() { return with; }
	int GetHeight() { return height; }
	void SetSize(int _sizeX, int _sizeY);
	int GetSizeX();
	int GetSizeY();
	void SetNameWindows(char name[]);
	void SetFullscreen(bool _fullscreen);
	GLFWwindow* GetWindowsPtr();
	int CheckCreateWindows();
	void CreateContextWindows();
	bool CheckGLFWwindowShouldClose();
	void SwapBuffersWindows();
};
#endif