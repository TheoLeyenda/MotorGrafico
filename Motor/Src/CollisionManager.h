#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
#include "PrivateClass/Export.h"

#include "Entity.h"
#include "Entity2D.h"

enum CollisionResult2D
{
	CollisionLeft,
	CollisionRight,
	CollisionUp,
	CollisionDown,
	NoneCollision
};

class ENGINE_API CollisionManager
{

private:
public:
	CollisionManager();

	void CheckCollision(Entity* myEntity,Entity* toCheckCollision);
	void CheckTrigger(Entity* myEntity, Entity* toCheckTrigger);

	
	
	CollisionResult2D CheckParcialTrigger2D(Entity2D* myEntity, Entity2D* toCheckTrigger2D);
	CollisionResult2D CheckParcialCollision2D(Entity2D* myEntity, Entity2D* toCheckTrigger2D);

	bool CheckTrigger2D(Entity2D* myEntity, Entity2D* toCheckTrigger2D);
	bool CheckCollision2D(Entity2D* myEntity, Entity2D& toCheckCollision2D);
};

#endif
