#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "PrivateClass/Export.h"
#include "Windows.h"

class ENGINE_API GameBase {
private:
	Windows* windows;
public:
	GameBase();
	~GameBase();
	int Init();
};
#endif
