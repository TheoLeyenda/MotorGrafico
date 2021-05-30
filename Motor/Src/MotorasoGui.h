#ifndef MOTORASOGUI_H
#define MOTORASOGUI_H

#include "PrivateClass/Export.h"
#include "Windows.h"
#include "Gui/imgui.h"
#include "Gui/imgui_impl_glfw_gl3.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Entity;

class ENGINE_API MotorasoGui 
{
private:
	Windows* _window;
	float xPosition = 0;
	
	bool _wireFrameActive;
public:
	MotorasoGui(Windows* window);
	bool& GetIfWireFrameIsActive() { return _wireFrameActive; }
	void UpdateMotorasoGui();
	void UpdateMotorasoGui(vector<Entity*> entitysData);
	void CreateFrame();
	void RenderGui();
	~MotorasoGui();
};

#endif
