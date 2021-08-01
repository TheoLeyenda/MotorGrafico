#ifndef MOTORASOGUI_H
#define MOTORASOGUI_H

#include "PrivateClass/Export.h"
#include "Windows.h"


#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Entity;
class Light;

class ENGINE_API MotorasoGui
{
private:
	Windows* _window;
	float xPosition = 0;
	static float speedPosition;
	static float speedRotation;
	static float speedScalated;
	static bool _wireFrameActive;
	
	static Entity* lastEntitySelected;
	static Entity* currentEntitySelected;
	static void _TreeEntitys(Entity* entity);
public:
	MotorasoGui(Windows* window);
	static void CreateContext(Windows* window);
	static void Destroy();
	static void NewFrame();
	static void Render();
	static void TreeEntitys(Entity* entityNode);
	static void ShowTransform(Entity* entityNode);
	static void ShowEntityNodeInfo(Entity* entityNode);
	static void ShowEntityInfo(Entity* entityNode);
	static void ShowLightInfo(Light* light);
	static void Text(const string& text);
	static void Begin(const string& windowName, bool opened, size_t flags);
	static void End();

	bool& GetIfWireFrameIsActive() { return _wireFrameActive; }
	static void UpdateWireFrameGui();
	static void UpdateAABB(Entity* entityNode);
	float GetSpeedRotation() { return speedRotation; };
	void SetSpeedPositionChange(float value) { speedPosition = value; }
	void SetSpeedRotationChange(float value) { speedRotation = value; }
	void SetSpeedScalatedChange(float value) { speedScalated = value; }
	~MotorasoGui();
};

#endif
