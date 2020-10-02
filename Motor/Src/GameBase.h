#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "PrivateClass/Export.h"
#include "Windows.h"
#include "Renderer.h"
#include "Shape.h"
#include <stdlib.h>
#include <time.h>

class ENGINE_API GameBase {
private:
	Windows* windows;
	Renderer* render;
	
	Shape* quad; //no tiene que ir xd
	Shape* tri;
public:
	GameBase();
	~GameBase();
	int Init();
	void TempInputs(Windows* windows, Shape* tri);
};
#endif