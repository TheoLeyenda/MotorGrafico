#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "PrivateClass/Export.h"
#include "Windows.h"
#include "Renderer.h"
#include "Shape.h"
#include "model.h"
#include <stdlib.h>
#include <time.h>
#include "Input.h"
#include "Sprite.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

#define INIT_ERROR -1

class ENGINE_API GameBase {
private:

	void HandleCamera();				//Funcion interna del engine
	void HandleLight(Camera* camera);	//Funcion interna del engine
protected:
	Windows* windows;
	Renderer* render;
	Input* input;
	CollisionManager* collisionManager;
	Time timeClock;
	Camera* camera;
	Light* light;
public:
	GameBase();
	~GameBase();

	int InitEngine();
	void UpdateEngine();
	void DestroyEngine();

	virtual void InitGame() = 0; //Inicializa todos las variables del juego.
	virtual void UpdateGame(Windows *_window, Renderer *_render, Input *_input) = 0; //Update del juego
	virtual void DestroyGame() = 0; //Funcion que se debe llamar al finalizar el juego (Destruye correctamente todos las funciones internas del juego)

	Time& GetTimeClock();
	CollisionManager* GetCollisionManager() { return collisionManager; }
	Windows* GetWindows();
	Renderer* GetRenderer();
	Input* GetInput();
};
#endif