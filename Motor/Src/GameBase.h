#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "PrivateClass/Export.h"
#include "Windows.h"
#include "Renderer.h"
#include "Shape.h"
#include "Primitive3D.h"
#include <stdlib.h>
#include <time.h>
#include "Input.h"
#include "Sprite.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Model.h"
#include "Audio.h"
#include "MotorasoGui.h"
#include "ModelNode.h"
#include "BSP_Manager.h"
#include "Plane_BSP.h"
#include "Plane.h"
#include <map>

#define INIT_ERROR -1

class EmptyObject;

class ENGINE_API GameBase {
private:

	vector<Light*> _lights;
	void HandleCamera();				//Funcion interna del engine
	void HandleLight();	//Funcion interna del engine

	bool useDebugWindows = true;

	EmptyObject* rootScene;

	void ActivateAABB_DebugGame();
	void DisableAABB_DebugGame();

	bool useBSP_Manager = true;

protected:
	static vector<Entity*> entitysDebugInGame;

	Windows* windows = NULL;
	Renderer* render = NULL;
	Input* input = NULL;
	CollisionManager* collisionManager = NULL;
	Time timeClock;
	Camera* camera = NULL;
	Material* textureMaterialForLight = NULL;
	Material* textureMaterialDefault = NULL;
	MotorasoGui* motorasoGui = NULL;

	BSP_Manager* bsp_manager = NULL;
	vector<Entity*> entitysBSP;
	void AddEntityInEntitysBSP(Entity* newItem);
	void UpdateBSP_Manager();

	void SetUseBSP_Manager(bool value) { useBSP_Manager = value; }
public:
	GameBase();
	~GameBase();

	int InitEngine();
	void UpdateEngine();
	void DestroyEngine();

	void SetEnableAABB_DebugGame(bool value);

	void AddObjectInDenugGame(Entity* entity);

	void RemoveObjectInDebugGame(Entity* entity);

	static void DisableObjectInGame(Entity* entity);

	static void EnableObjectInGame(Entity* entity);

	void SetUseDebugWindows(bool value) { useDebugWindows = value; }

	Light* GetLight(int id);
	void AddLight(Light::TypeLight typeLight, int id);
	void RemoveLight(int id);
	void SetLightPosition(int id, glm::vec3 position);
	void SetTypeLightDefault(int id, Light::TypeLight setType);
	void SetSettingsLightCustom(int id, glm::vec3 direction);
	void SetSettingsLightCustom(int id, float linearVal, float quadraticVal, float cutOffValue);
	void SetSettingsLightCustom(int id, float linearVal, float quadraticVal, float cutOffValue, float outerCutOffValue);
	void ChangeColorLight(int id, glm::vec3 color );
	void GetMyLightsID();

	virtual void InitGame() = 0; //Inicializa todos las variables del juego.
	virtual void UpdateGame(Windows *_window, Renderer *_render, Input *_input) = 0; //Update del juego
	virtual void DestroyGame() = 0; //Funcion que se debe llamar al finalizar el juego (Destruye correctamente todos las funciones internas del juego)

	void ShowEntitys_BSP();

	Time& GetTimeClock();
	CollisionManager* GetCollisionManager() { return collisionManager; }
	Windows* GetWindows();
	Renderer* GetRenderer();
	Input* GetInput();
	Entity* GetRootScene() { return (Entity*)rootScene; }
};
#endif