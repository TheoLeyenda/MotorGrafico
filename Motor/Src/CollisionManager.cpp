#include "CollisionManager.h"

#include "AxisAlignedBoundingBox.h"
#include "Camera.h"
#include <math.h>

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager(){}


CollisionResult2D CollisionManager::ParcialCollisionDetection2D(Entity2D* myEntity, Entity2D* toCheckTrigger2D, glm::vec3 myScale, glm::vec3 toCheckScale)
{
	float toCheckPosX = toCheckTrigger2D->transform.position.x;
	float toCheckPosY = toCheckTrigger2D->transform.position.y;

	float toCheckScaleX = toCheckScale.x;
	float toCheckScaleY = toCheckScale.y;

	float myPosX = myEntity->transform.position.x;
	float myPosY = myEntity->transform.position.y;

	float myScaleX = myScale.x;
	float myScaleY = myScale.y;

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

bool CollisionManager::CheckTrigger2D(Entity2D* myEntity, Entity2D* toCheckEntity2D, glm::vec3 myScale, glm::vec3 toCheckScale)
{
	CollisionResult2D collisionResult = ParcialCollisionDetection2D(myEntity, toCheckEntity2D, myScale, toCheckScale);

	if (collisionResult != CollisionResult2D::NoneCollision)
		return true;

	return false;
}

bool CollisionManager::CheckCollision2D(Entity2D* myEntity, Entity2D* toCheckEntity2D, float speedMyEntity, glm::vec3 myScale, glm::vec3 toCheckScale)
{
	if (speedMyEntity <= 0) 
		 speedMyEntity = 0.05f;

	CollisionResult2D collisionResult = ParcialCollisionDetection2D(myEntity, toCheckEntity2D, myScale, toCheckScale);
	if (collisionResult != CollisionResult2D::NoneCollision) 
	{
		switch (collisionResult)
		{
		case CollisionResult2D::CollisionDown:
			myEntity->SetPosition(myEntity->transform.position.x,
								  myEntity->transform.position.y + speedMyEntity,
								  myEntity->transform.position.z);
			break;
		case CollisionResult2D::CollisionLeft:
			myEntity->SetPosition(myEntity->transform.position.x + speedMyEntity,
								  myEntity->transform.position.y,
								  myEntity->transform.position.z);
			break;
		case CollisionResult2D::CollisionRight:
			myEntity->SetPosition(myEntity->transform.position.x - speedMyEntity,
								  myEntity->transform.position.y,
								  myEntity->transform.position.z);
			break;
		case CollisionResult2D::CollisionUp:
			myEntity->SetPosition(myEntity->transform.position.x,
								  myEntity->transform.position.y - speedMyEntity,
								  myEntity->transform.position.z);
			break;
		}

		return true;
	}
	
	return false;
}

bool CollisionManager::CheckEntitiesOnFrustrum(Camera* actualFrustrumCamera, Entity* entitiesOnGame)
{
	if (actualFrustrumCamera->GetActualFrustrumInUse() != NULL && entitiesOnGame->GetAABB() != NULL)
	{
		float cameraMinX = actualFrustrumCamera->transform.position.x + actualFrustrumCamera->GetActualFrustrumInUse()->GetAABBPositions()[0].x;
		float cameraMaxX = actualFrustrumCamera->transform.position.x + actualFrustrumCamera->GetActualFrustrumInUse()->GetAABBPositions()[2].x;
		float cameraMinY = actualFrustrumCamera->transform.position.y + actualFrustrumCamera->GetActualFrustrumInUse()->GetAABBPositions()[1].y;
		float cameraMaxY = actualFrustrumCamera->transform.position.y + actualFrustrumCamera->GetActualFrustrumInUse()->GetAABBPositions()[3].y;
		float cameraMinZ = actualFrustrumCamera->transform.position.z + actualFrustrumCamera->GetActualFrustrumInUse()->GetAABBPositions()[4].z;
		float cameraMaxZ = actualFrustrumCamera->transform.position.z + actualFrustrumCamera->GetActualFrustrumInUse()->GetAABBPositions()[3].z;

		float entitieMinX = entitiesOnGame->transform.position.x + entitiesOnGame->GetAABB()->GetAABBPositions()[0].x - entitiesOnGame->transform.scale.x;
		float entitieMaxX = entitiesOnGame->transform.position.x + entitiesOnGame->GetAABB()->GetAABBPositions()[2].x + entitiesOnGame->transform.scale.x;
		float entitieMinY = entitiesOnGame->transform.position.y + entitiesOnGame->GetAABB()->GetAABBPositions()[1].y - entitiesOnGame->transform.scale.y;
		float entitieMaxY = entitiesOnGame->transform.position.y + entitiesOnGame->GetAABB()->GetAABBPositions()[3].y + entitiesOnGame->transform.scale.y;
		float entitieMinZ = entitiesOnGame->transform.position.z + entitiesOnGame->GetAABB()->GetAABBPositions()[4].z - entitiesOnGame->transform.scale.z;
		float entitieMaxZ = entitiesOnGame->transform.position.z + entitiesOnGame->GetAABB()->GetAABBPositions()[3].z + entitiesOnGame->transform.scale.z;

		//cout << "CAM | MAX X:" << cameraMaxX << " MIN X:" << cameraMinX << endl;
		//cout << "CAM | MAX Y:" << cameraMaxY << " MIN Y:" << cameraMinY << endl;
		//cout << "CAM | MAX Z:" << cameraMaxZ << " MIN Z:" << cameraMinZ << endl;
		//
		//cout << "ENTITIE | MAX X:" << entitieMaxX << " MIN X:" << entitieMinX << endl;
		//cout << "ENTITIE | MAX Y:" << entitieMaxY << " MIN Y:" << entitieMinY << endl;
		//cout << "ENTITIE | MAX Z:" << entitieMaxZ << " MIN Z:" << entitieMinZ << endl;

		switch (actualFrustrumCamera->typeProjectionCamera)		
		{
		case Perspective:
			if (cameraMinX < entitieMaxX && cameraMaxX > entitieMinX &&
				cameraMinY < entitieMaxY && cameraMaxY > entitieMinY &&
				cameraMinZ < entitieMaxZ && cameraMaxZ > entitieMinZ)
			{
				return true;
			}
			else {
				return false;
			}
			break;
		case Ortho:
			if (cameraMinX < entitieMaxX && cameraMaxX > entitieMinX &&
				cameraMinY < entitieMaxY && cameraMaxY > entitieMinY)
			{
				return true;
			}
			else {
				return false;
			}
			break;
		}
	}
	
	return false;
}