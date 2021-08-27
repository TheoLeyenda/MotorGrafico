#include "Plane_BSP.h"
#include "Plane.h"

Plane_BSP::Plane_BSP(){}


Plane_BSP::~Plane_BSP()
{
	if (myPlane != NULL) {
		delete myPlane;
		myPlane = NULL;
	}

}

void Plane_BSP::SetPlaneAttach(Entity * plane)
{
	planeAttach = plane;
}
Entity * Plane_BSP::GetPlaneAttach()
{
	return planeAttach;
}

void Plane_BSP::GeneratePlane()
{
	if (planeAttach != NULL) 
	{
		glm::vec3 PointA, PointB, PointC;

		PointA = glm::vec3(planeAttach->transform.globalPosition.x + (planeAttach->transform.scale.x)
			, planeAttach->transform.globalPosition.y
			, planeAttach->transform.globalPosition.z);

		PointB = glm::vec3(planeAttach->transform.globalPosition.x
			, planeAttach->transform.globalPosition.y + (planeAttach->transform.scale.y)
			, planeAttach->transform.globalPosition.z);

		PointC = glm::vec3(planeAttach->transform.globalPosition.x
			, planeAttach->transform.globalPosition.y
			, planeAttach->transform.globalPosition.z);

		if (myPlane == NULL)
			myPlane = new MyPlane(PointA, PointB, PointC);
		else
			myPlane->set3Points(PointA, PointB, PointC);

		//cout << "PointA" << endl;
		//cout << PointA.x << "," << PointA.y << "," << PointC.z << endl;
		//cout << "PointB" << endl;
		//cout << PointB.x << "," << PointB.y << "," << PointB.z << endl;
		//cout << "PointC" << endl;
		//cout << PointC.x << "," << PointC.y << "," << PointC.z << endl;

		//cout << endl;
	}
}
void Plane_BSP::UpdatePlane_BSP(vector<string> registerKeysBSP)
{
	GeneratePlane();

	//Filtro otros si hay otro plano BSP en mi vector de objetos y lo remuevo
	for (int i = 0; i < ObjectsInGame.size(); i++) 
	{
		for (int j = 0; j < registerKeysBSP.size(); j++) 
		{
			if (ObjectsInGame[i]->GetName().c_str() == registerKeysBSP[j].c_str())
			{
				RemoveItemObjectsInGame(i);
			}
		}
	}

	if (myPlane == NULL|| ObjectsInGame.size() <= 0)
		return;

	//Checkeo de que lados estan los objetos y dependiendo de ello los pongo en un vector o en el otro

	for (int i = 0; i < ObjectsInGame.size(); i++)
	{
		//cout << planeAttach->GetName() <<" "<< myPlane->getSide(ObjectsInGame[i]->transform.globalPosition) << endl;
		if (myPlane->getSide(ObjectsInGame[i]->transform.globalPosition))
		{
			ObjectsPositivePlane.push_back(ObjectsInGame[i]);
		}
		else
		{
			ObjectsNegativePlane.push_back(ObjectsInGame[i]);
		}
	}
	

	for (int i = 0; i < ObjectsNegativePlane.size(); i++)
	{
		ObjectsNegativePlane[i]->SetIsAlive(false);
	}

	for (int i = 0; i < ObjectsPositivePlane.size(); i++)
	{
		ObjectsPositivePlane[i]->SetIsAlive(true);
	}
	
	
	//Limpio los vectores ObjectsLeftPlane y ObjectsRightPlane
	ObjectsNegativePlane.clear();
	ObjectsPositivePlane.clear();


}
void Plane_BSP::RemoveItemObjectsInGame(int index)
{
	ObjectsInGame.erase(ObjectsInGame.begin() + index);
}



