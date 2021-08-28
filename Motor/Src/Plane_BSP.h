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

	void SetPlaneAttach(Entity* plane);
	Entity* GetPlaneAttach();

	void GeneratePlane();

	vector<Entity*> ObjectsInGame;
	vector<Entity*> ObjectsNegativePlane;
	vector<Entity*> ObjectsPositivePlane;

	void SetName(string value) { name = value; }
	string GetName() { return name; }

	void UpdatePlane_BSP(vector<string> registerKeysBSP);
private:
	string name;
	void RemoveItemObjectsInGame(int index);
	Entity* planeAttach = NULL;
	MyPlane* myPlane = NULL; // Con esto saco la matematica del plano
};

#endif

