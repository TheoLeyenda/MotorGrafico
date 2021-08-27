#ifndef PLANE_BSP_H
#define PLANE_BSP_H

#include "Entity.h"
#include <string>
#include <string.h>
#include "PrivateClass/Export.h"
class MyPlane;

class ENGINE_API Plane_BSP
{
public:
	Plane_BSP();
	~Plane_BSP();

	enum  CurrentCameraPosition
	{
		Null,
		LeftPlane,
		RightPlane,
	};

	CurrentCameraPosition currentCameraPosition = Null; 

	void SetPlaneAttach(Entity* plane);
	void SetCurrenCameraCompare(Entity* camera);
	Entity* GetPlaneAttach();

	void GeneratePlane();

	vector<Entity*> ObjectsInGame;
	vector<Entity*> ObjectsLeftPlane;
	vector<Entity*> ObjectsRightPlane;

	void UpdatePlane_BSP(vector<string> registerKeysBSP);
private:
	void RemoveItemObjectsInGame(int index);
	Entity* currentCameraCompare = NULL;
	Entity* planeAttach = NULL;
	MyPlane* myPlane = NULL; // Con esto saco la matematica del plano
};

#endif

