#include "BSP_Manager.h"
#include "Plane_BSP.h"
#include <sstream>

BSP_Manager::BSP_Manager(Entity* camera, Entity* _rootScene)
{
	auxKeyBSP = "Plane_BSP";
	UpdateKeyBSP_Plane("Plane_BSP");
	currentCamera = camera;
	rootScene = _rootScene;
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

	if (isFoundElementMap != Planes_BSP.end()) {
		Planes_BSP[planeAttach->GetName()]->SetPlaneAttach(planeAttach);
		Planes_BSP[planeAttach->GetName()]->SetCurrentCameraCompare(currentCamera);
	}
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

vector<Entity*> BSP_Manager::FilterPlanesBSP(vector<Entity*> ObjectsInBSP)
{
	vector<Entity*> planes;
	vector<Entity*> auxObjectsInBSP;

	for (int i = 0; i < ObjectsInBSP.size(); i++)
	{
		for (int j = 0; j < registerKeysBSP.size(); j++)
		{
			if (ObjectsInBSP[i]->GetName() == registerKeysBSP[j])
			{
				Entity* parent = ObjectsInBSP[i]->GetParent();
				parent->RemoveChildren(ObjectsInBSP[i], rootScene);
				planes.push_back(ObjectsInBSP[i]);
			}
		}
	}

	for (int i = 0; i < ObjectsInBSP.size(); i++)
	{
		bool push = true;
		for (int j = 0; j < planes.size(); j++) {

			if (ObjectsInBSP[i] == planes[j] || ObjectsInBSP[i] == planes[j]->GetChild(0))
			{
				push = false;
			}
		}
		if (push)
			auxObjectsInBSP.push_back(ObjectsInBSP[i]);
	}

	return auxObjectsInBSP;
}

void BSP_Manager::DisableObjects(vector<Entity*> ObjectsInBSP)
{
	for (int i = 0; i < objectsDisableBSP.size(); i++)
	{
		if(ObjectsInBSP[objectsDisableBSP[i]]->GetIsAlive())
			ObjectsInBSP[objectsDisableBSP[i]]->DisableMeAndChilds();
	}

	objectsDisableBSP.clear();
}

void BSP_Manager::UpdateBSP_Manager(vector<Entity*> ObjectsInBSP)
{
	//Filtro otros si hay otro plano BSP en mi vector de objetos y lo remuevo
	vector<Entity*> auxObjectsInBSP = FilterPlanesBSP(ObjectsInBSP);;

	//----------------------------------------------------------------------//

	for (int i = 0; i < ObjectsInBSP.size(); i++) 
	{
		ObjectsInBSP[i]->SetIsAlive(true);
	}

	for (int i = 0; i < Planes_BSP.size(); i++) 
	{
		if (Planes_BSP[registerKeysBSP[i]] != NULL && Planes_BSP[registerKeysBSP[i]] != nullptr) {
			Planes_BSP[registerKeysBSP[i]]->ObjectsInGame = auxObjectsInBSP;
			Planes_BSP[registerKeysBSP[i]]->UpdatePlane_BSP(registerKeysBSP, objectsDisableBSP);
		}
	}

	DisableObjects(ObjectsInBSP);

}
