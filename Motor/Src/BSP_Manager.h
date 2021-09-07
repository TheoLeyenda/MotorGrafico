#ifndef BSP_MANAGER_H
#define BSP_MANAGER_H

#include "PrivateClass/Export.h"
#include "Entity.h"
#include <string>
#include <string.h>
#include <map>
class Plane_BSP;

class ENGINE_API BSP_Manager
{
private:
	string keyBSP;
	string auxKeyBSP;
	void UpdateKeyBSP_Plane(string newKey);
	Entity* currentCamera = NULL;
	vector<string> registerKeysBSP;

public:
	vector<int> objectsDisableBSP;
	map<string,Plane_BSP*> Planes_BSP; // CAMBIAR ESTO POR UN MAPA DE PLANOS
	BSP_Manager(Entity* camera);
	~BSP_Manager();
	string GetKeyBSP();
	void SettingDataLastPlaneBSP(Entity* planeAttach);
	bool AddPlane_BSP(Plane_BSP* newItem);
	void ClearPlanes_BSP();
	void RemovePlane_BSP(string keyRemovePlane);
	void ShowPlanesAttachPlanes_BSP();
	void ShowRegisterKeyBSP();
	void UpdateBSP_Manager(vector<Entity*> ObjectsInBSP);
};

#endif