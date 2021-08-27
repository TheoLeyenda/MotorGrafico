#include "BSP_Manager.h"
#include "Plane_BSP.h"
#include <sstream>

BSP_Manager::BSP_Manager(Entity* camera)
{
	auxKeyBSP = "Plane_BSP";
	UpdateKeyBSP_Plane("Plane_BSP");
	currentCamera = camera;
}

BSP_Manager::~BSP_Manager()
{
	for (int i = 0; i < Planes_BSP.size(); i++) 
	{
		if (Planes_BSP[i] != NULL && Planes_BSP[i] != nullptr) 
		{
			delete Planes_BSP[i];
			Planes_BSP[i] = NULL;
		}
	}
}

string BSP_Manager::GetKeyBSP()
{
	return keyBSP;
}

void BSP_Manager::SettingDataLastPlaneBSP(Entity * planeAttach)
{
	Planes_BSP[Planes_BSP.size() - 1]->SetPlaneAttach(planeAttach);
}

void BSP_Manager::UpdateKeyBSP_Plane(string newKey)
{
	keyBSP = newKey + to_string(Planes_BSP.size()+1);
	registerKeysBSP.push_back(keyBSP);
}

void BSP_Manager::AddPlane_BSP(Plane_BSP * newItem, string currentKey)
{
	bool repeatItem = false;
	for (int i = 0; i < registerKeysBSP.size(); i++) 
	{
		if (currentKey.c_str() == registerKeysBSP[i].c_str()) 
		{
			repeatItem = true;
		}
	}

	if (repeatItem)
		return;
	
	keyBSP.clear();
	keyBSP = auxKeyBSP;
	UpdateKeyBSP_Plane(keyBSP);
	Planes_BSP.push_back(newItem);
}

void BSP_Manager::ClearPlanes_BSP()
{
	Planes_BSP.clear();
}

void BSP_Manager::RemovePlane_BSP(Plane_BSP * itemRemove)
{
	int index = -1;
	for (int i = 0; i < Planes_BSP.size(); i++) 
	{
		if (Planes_BSP[i] == itemRemove) 
		{
			index = i;
			i = Planes_BSP.size();
		}
	}

	if (index != -1) 
		Planes_BSP.erase(Planes_BSP.begin() + index);
}

void BSP_Manager::ShowPlanesAttachPlanes_BSP()
{
	for (int i = 0; i < Planes_BSP.size(); i++) 
	{
		std::cout <<"Plane_BSP"<<i<< Planes_BSP[i]->GetPlaneAttach()->GetName()<<std::endl;
	}
}

void BSP_Manager::UpdateBSP_Manager(vector<Entity*> ObjectsInBSP)
{
	//cout << Planes_BSP.size() << endl;
	for (int i = 0; i < Planes_BSP.size(); i++) 
	{
		if (Planes_BSP[i] != NULL && Planes_BSP[i] != nullptr) {
			Planes_BSP[i]->ObjectsInGame = ObjectsInBSP;
			Planes_BSP[i]->UpdatePlane_BSP(registerKeysBSP);
			//cout << "PLane_BSP" << i << endl;
			//cout << Planes_BSP[i]->GetPlaneAttach()->transform.globalPosition.x
			//	<< ", " << Planes_BSP[i]->GetPlaneAttach()->transform.globalPosition.y
			//	<< ", " << Planes_BSP[i]->GetPlaneAttach()->transform.globalPosition.z << endl;
		}
	}
	//cin.get();
	//system("cls");
}
