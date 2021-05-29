#ifndef MOTORASOGUI_H
#define MOTORASOGUI_H

#include "PrivateClass/Export.h"
#include "Windows.h"
#include "Gui/imgui.h"
#include "Gui/imgui_impl_glfw_gl3.h"

class ENGINE_API MotorasoGui 
{
private:
	Windows* _window;
	float f = 0;

	bool _wireFrameActive;
public:
	MotorasoGui(Windows* window);
	bool& GetIfWireFrameIsActive() { return _wireFrameActive; }
	void UpdateMotorasoGui();
	void CreateFrame();
	void RenderGui();
	~MotorasoGui();
};

#endif
