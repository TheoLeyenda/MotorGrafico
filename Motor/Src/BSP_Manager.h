#ifndef BSP_MANAGER_H
#define BSP_MANAGER_H

#include "PrivateClass/Export.h"
#include "Entity.h"
#include <string>
#include <string.h>

class Plane_BSP;

class ENGINE_API BSP_Manager
{
private:
	vector<Plane_BSP*> Planes_BSP;
	string keyBSP;
	void UpdateKeyBSP_Plane(string newKey);
	Entity* currentCamera = NULL;
	vector<string> registerKeysBSP;
public:
	BSP_Manager(Entity* camera);
	~BSP_Manager();
	string GetKeyBSP();
	void SetNewCurrentCameraPlanes_BSP(Entity* camera);
	void SettingDataLastPlaneBSP(Entity* planeAttach);
	void AddPlane_BSP(Plane_BSP* newItem);
	void ClearPlanes_BSP();
	void RemovePlane_BSP(Plane_BSP* itemRemove);
	void ShowPlanesAttachPlanes_BSP();

	void UpdateBSP_Manager(vector<Entity*> ObjectsInBSP);
};

#endif