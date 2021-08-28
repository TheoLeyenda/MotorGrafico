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
		if (Planes_BSP[registerKeysBSP[i]] != NULL && Planes_BSP[registerKeysBSP[i]] != nullptr)
		{
			delete Planes_BSP[registerKeysBSP[i]];
			Planes_BSP[registerKeysBSP[i]] = NULL;
		}
	}
}

string BSP_Manager::GetKeyBSP()
{
	return keyBSP;
}

void BSP_Manager::SettingDataLastPlaneBSP(Entity * planeAttach)
{
	auto isFoundElementMap = Planes_BSP.find(planeAttach->GetName());

	if(isFoundElementMap != Planes_BSP.end())
		Planes_BSP[planeAttach->GetName()]->SetPlaneAttach(planeAttach);
}

void BSP_Manager::UpdateKeyBSP_Plane(string newKey)
{
	keyBSP = newKey + to_string(Planes_BSP.size()+1);
	registerKeysBSP.push_back(keyBSP);
}

bool BSP_Manager::AddPlane_BSP(Plane_BSP * newItem)
{
	auto isFoundElementMap = Planes_BSP.find(keyBSP);
	
	if (isFoundElementMap != Planes_BSP.end())
		return false;
	
	Planes_BSP.insert(std::make_pair(keyBSP, newItem));

	keyBSP.clear();
	keyBSP = auxKeyBSP;
	UpdateKeyBSP_Plane(keyBSP);
	
	return true;

}

void BSP_Manager::ClearPlanes_BSP()
{
	Planes_BSP.clear();
}

void BSP_Manager::RemovePlane_BSP(string keyRemovePlane)
{
	auto isFoundElementMap = Planes_BSP.find(keyRemovePlane);

	if (isFoundElementMap == Planes_BSP.end())
		return;
	
	Planes_BSP.erase(isFoundElementMap);
}

void BSP_Manager::ShowPlanesAttachPlanes_BSP()
{
	cout << "---Planes_BSP---" << endl;
	for (int i = 0; i < Planes_BSP.size(); i++) 
	{
		std::cout <<"Element "<<i<<" "<<Planes_BSP[registerKeysBSP[i]]->GetPlaneAttach()->GetName()<<std::endl;
	}
	cout << "Cantidad de elementos: " << Planes_BSP.size()<<endl;
}

void BSP_Manager::ShowRegisterKeyBSP()
{
	cout << "---RegisterKeysBSP---" << endl;
	for (int i = 0; i < registerKeysBSP.size(); i++) 
	{
		std::cout << "Element " << i << " " << registerKeysBSP[i]<< std::endl;
	}
	cout << "Cantidad de elementos: " << registerKeysBSP.size() << endl;
}

void BSP_Manager::UpdateBSP_Manager(vector<Entity*> ObjectsInBSP)
{
	for (int i = 0; i < Planes_BSP.size(); i++) 
	{
		if (Planes_BSP[registerKeysBSP[i]] != NULL && Planes_BSP[registerKeysBSP[i]] != nullptr) {
			Planes_BSP[registerKeysBSP[i]]->ObjectsInGame = ObjectsInBSP;
			Planes_BSP[registerKeysBSP[i]]->UpdatePlane_BSP(registerKeysBSP);
		}
	}
}
