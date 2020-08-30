#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "PrivateClass/Export.h"
#include "Windows.h"
#include "Renderer.h"

class ENGINE_API GameBase {
private:
	Windows* windows;
	Renderer* render;
public:
	GameBase();
	~GameBase();
	int Init();
};
#endif