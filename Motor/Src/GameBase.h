#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "PrivateClass/Export.h"
#include "Windows.h"
#include "Renderer.h"
#include "Shape.h"
#include <stdlib.h>
#include <time.h>
#include "Input.h"

class ENGINE_API GameBase {
private:
	Windows* windows;
	Renderer* render;
	Input* input;
	Shape* quad; //no tiene que ir xd
	Shape* tri;
public:
	GameBase();
	~GameBase();

	
	int InitGame();
	void Update(); 
	void DestroyGame();

	//virtual int InitGame(); //Inicializa todos las variables del juego.
	//virtual void Update(); //Update del juego
	//virtual void DestroyGame(); //Funcion que se debe llamar al finalizar el juego (Destruye correctamente todos las funciones internas del juego)
	
	void TempInputs(Windows* windows, Shape* tri);
};
#endif