#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "PrivateClass/Export.h"
#include "Windows.h"
#include "Renderer.h"
#include "Shape.h"
#include <stdlib.h>
#include <time.h>
#include "Input.h"

#define INIT_ERROR -1

class ENGINE_API GameBase {
private:
	Windows* windows;
	Renderer* render;
	Input* input;
public:
	GameBase();
	~GameBase();

	int InitEngine();
	void UpdateEngine();
	void DestroyEngine();

	virtual void InitGame() = 0; //Inicializa todos las variables del juego.
	virtual void UpdateGame(Windows *_window, Renderer *_render, Input *_input) = 0; //Update del juego
	virtual void DestroyGame() = 0; //Funcion que se debe llamar al finalizar el juego (Destruye correctamente todos las funciones internas del juego)

	void TempInputs(Windows* windows, Shape* tri);

	Windows* GetWindows();
	Renderer* GetRenderer();
	Input* GetInput();
};
#endif