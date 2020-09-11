#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "PrivateClass/Export.h"
#include "Windows.h"
#include "Renderer.h"
#include "Shape.h"

class ENGINE_API GameBase {
private:
	Windows* windows;
	Renderer* render;
	
	Shape* shape; //no tiene que ir xd
public:
	GameBase();
	~GameBase();
	int Init();
};
#endif