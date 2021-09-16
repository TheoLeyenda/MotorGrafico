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
	for (int i = 0; i < planes_BSP.size(); i++) 
	{
		if (planes_BSP[registerKeysBSP[i]] != NULL && planes_BSP[registerKeysBSP[i]] != nullptr)
		{
			delete planes_BSP[registerKeysBSP[i]];
			planes_BSP[registerKeysBSP[i]] = NULL;
		}
	}
}

string BSP_Manager::GetKeyBSP()
{
	return keyBSP;
}

void BSP_Manager::SettingDataLastPlaneBSP(Entity * planeAttach)
{
	auto isFoundElementMap = planes_BSP.find(planeAttach->GetName());

	if (isFoundElementMap != planes_BSP.end()) {
		planes_BSP[planeAttach->GetName()]->SetPlaneAttach(planeAttach);
		planes_BSP[planeAttach->GetName()]->SetCurrentCameraCompare(currentCamera);
	}
}

void BSP_Manager::UpdateKeyBSP_Plane(string newKey)
{
	keyBSP = newKey + to_string(planes_BSP.size()+1);
	registerKeysBSP.push_back(keyBSP);
}

bool BSP_Manager::AddPlane_BSP(Plane_BSP * newItem)
{
	auto isFoundElementMap = planes_BSP.find(keyBSP);
	
	if (isFoundElementMap != planes_BSP.end())
		return false;
	
	planes_BSP.insert(std::make_pair(keyBSP, newItem));

	keyBSP.clear();
	keyBSP = auxKeyBSP;
	UpdateKeyBSP_Plane(keyBSP);
	
	return true;

}

void BSP_Manager::ClearPlanes_BSP()
{
	planes_BSP.clear();
}

void BSP_Manager::RemovePlane_BSP(string keyRemovePlane)
{
	auto isFoundElementMap = planes_BSP.find(keyRemovePlane);

	if (isFoundElementMap == planes_BSP.end())
		return;
	
	planes_BSP.erase(isFoundElementMap);
}

void BSP_Manager::ShowPlanesAttachPlanes_BSP()
{
	cout << "---Planes_BSP---" << endl;
	for (int i = 0; i < planes_BSP.size(); i++) 
	{
		std::cout <<"Element "<<i<<" "<<planes_BSP[registerKeysBSP[i]]->GetPlaneAttach()->GetName()<<std::endl;
	}
	cout << "Cantidad de elementos: " << planes_BSP.size()<<endl;
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
			ObjectsInBSP[objectsDisableBSP[i]]->SetIsAlive(false);
	}

	objectsDisableBSP.clear();
}

void BSP_Manager::UpdateBSP_Manager(vector<Entity*> ObjectsInBSP)
{
	//Filtro otros si hay otro plano BSP en mi vector de objetos y lo remuevo
	vector<Entity*> auxObjectsInBSP = FilterPlanesBSP(ObjectsInBSP);
	vector<Plane_BSP*> vecPlanesBSP;
	//----------------------------------------------------------------------//

	for (int i = 0; i < ObjectsInBSP.size(); i++) 
	{
		ObjectsInBSP[i]->SetIsAlive(true);
	}

	for (int i = 0; i < registerKeysBSP.size(); i++)
	{
		if (planes_BSP[registerKeysBSP[i]] != NULL && planes_BSP[registerKeysBSP[i]] != nullptr) 
		{
			vecPlanesBSP.push_back(planes_BSP[registerKeysBSP[i]]);
		}
	}

	for (int i = 0; i < auxObjectsInBSP.size(); i++)
	{
		if (auxObjectsInBSP[i]->GetIsRootHerarchy()) 
		{
			auxObjectsInBSP[i]->CheckVisibleBSP(auxObjectsInBSP, objectsDisableBSP, vecPlanesBSP);
		}
	}

	DisableObjects(ObjectsInBSP);

	auxObjectsInBSP.clear();
	vecPlanesBSP.clear();

}
