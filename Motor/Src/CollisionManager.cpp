#include "CollisionManager.h"



CollisionManager::CollisionManager(){}

void CollisionManager::CheckCollision(Entity * myEntity, Entity * toCheckCollision)
{
}

void CollisionManager::CheckTrigger(Entity * myEntity, Entity * toCheckTrigger)
{
}

CollisionResult2D CollisionManager::CheckParcialTrigger2D(Entity2D* myEntity, Entity2D* toCheckTrigger2D)
{
	float toCheckPosX = toCheckTrigger2D->transform.position.x;
	float toCheckPosY = toCheckTrigger2D->transform.position.y;

	float toCheckScaleX = toCheckTrigger2D->transform.scale.x;
	float toCheckScaleY = toCheckTrigger2D->transform.scale.y;

	float myPosX = myEntity->transform.position.x;
	float myPosY = myEntity->transform.position.y;

	float myScaleX = myEntity->transform.scale.x;
	float myScaleY = myEntity->transform.scale.y;

	float minOverlapX = 0.0f;
	float maxOverlapX = glm::min(myPosX + fabs(myScaleX) / 2.0f, toCheckPosX + fabs(toCheckScaleX) / 2.0f) - glm::max(myPosX - fabs(myScaleX) / 2.0f, toCheckPosX - fabs(toCheckScaleX) / 2.0f);
	
	float overlapX = glm::max(minOverlapX, maxOverlapX);

	float minOverlapY = 0.0f;
	float maxOverlapY = glm::min(myPosY + fabs(myScaleY) / 2.0f, toCheckPosY + fabs(toCheckScaleY) / 2.0f) - glm::max(myPosY - fabs(myScaleY) / 2.0f, toCheckPosY - fabs(toCheckScaleY) / 2.0f);

	float overlapY = glm::max(minOverlapY, maxOverlapY);

	if (overlapX != 0.0f && overlapY != 0.0f) 
	{
		if (overlapX > overlapY)
		{
			if (myPosY < 0 && myPosY < toCheckPosY || myPosY > 0 && myPosY < toCheckPosY) {
				std::cout << "CollisionUp" << std::endl;
				return CollisionUp;
			}
			else if (myPosY < 0 && myPosY > toCheckPosY || myPosY > 0 && myPosY > toCheckPosY) {
				std::cout << "CollisionDown" << std::endl;
				return CollisionDown;
			}
		}
		else 
		{
			if (myPosX < 0 && myPosX < toCheckPosX || myPosX > 0 && myPosX < toCheckPosX) {
				std::cout << "CollisionRight" << std::endl;
				return CollisionRight;
			}
			else if (myPosX < 0 && myPosX > toCheckPosX || myPosX > 0 && myPosX > toCheckPosX) {
				std::cout << "CollisionLeft" << std::endl;
				return CollisionLeft;
			}
		}
	}
	return NoneCollision;
}

CollisionResult2D CollisionManager::CheckParcialCollision2D(Entity2D * myEntity, Entity2D * toCheckTrigger2D)
{
	return CollisionResult2D();
}

bool CollisionManager::CheckTrigger2D(Entity2D * myEntity, Entity2D * toCheckTrigger2D)
{
	float toCheckPosX = toCheckTrigger2D->transform.position.x;
	float toCheckPosY = toCheckTrigger2D->transform.position.y;

	float toCheckScaleX = toCheckTrigger2D->transform.scale.x;
	float toCheckScaleY = toCheckTrigger2D->transform.scale.y;

	float myPosX = myEntity->transform.position.x;
	float myPosY = myEntity->transform.position.y;

	float myScaleX = myEntity->transform.scale.x;
	float myScaleY = myEntity->transform.scale.y;

	if ((myPosX + fabs(myScaleX) >= toCheckPosX && myPosX <= toCheckPosX + fabs(toCheckPosX) &&
		 (myPosY + fabs(myScaleY) >= toCheckPosY && myPosY <= toCheckPosY + fabs(toCheckPosY))))
	{
		std::cout << "Colisione" << std::endl;
		return true;
	}

	return false;
}

bool CollisionManager::CheckCollision2D(Entity2D * myEntity, Entity2D & toCheckCollision2D)
{
	return false;
}
