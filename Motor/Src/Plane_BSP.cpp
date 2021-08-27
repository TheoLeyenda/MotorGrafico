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

void Plane_BSP::SetCurrenCameraCompare(Entity* camera)
{
	currentCameraCompare = camera;
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

		PointA = glm::vec3(planeAttach->transform.position.x + (planeAttach->transform.scale.x)
			, planeAttach->transform.position.y
			, planeAttach->transform.position.z);

		PointB = glm::vec3(planeAttach->transform.position.x
			, planeAttach->transform.position.y + (planeAttach->transform.scale.y)
			, planeAttach->transform.position.z);

		PointC = glm::vec3(planeAttach->transform.position.x
			, planeAttach->transform.position.y
			, planeAttach->transform.position.z);

		if (myPlane == NULL)
			myPlane = new MyPlane(PointA, PointB, PointC);
		else
			myPlane->set3Points(PointA, PointB, PointC);
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

	if (myPlane == NULL || currentCameraCompare == NULL || ObjectsInGame.size() <= 0)
		return;

	//cout << currentCameraCompare->transform.position.x <<" "<< currentCameraCompare->transform.position.y <<" "<< currentCameraCompare->transform.position.z << endl;
	if (myPlane->getSide(currentCameraCompare->transform.position)) 
	{
		currentCameraPosition = CurrentCameraPosition::RightPlane;
	}
	else
	{
		currentCameraPosition = CurrentCameraPosition::LeftPlane;
	}

	//Dibujo los objetos en funcion de que lado esta la camara
	//cout << currentCameraPosition << endl;
	switch (currentCameraPosition)
	{
		
	case CurrentCameraPosition::LeftPlane:
		//Si la camara esta del lado izquierdo dibujo los objetos que se encuentran en el vector ObjectsLeftPlane y 
		//dejo de dibujar los objetos que se encuentran en el vector ObjectsRightPlane.

		for (int i = 0; i < ObjectsLeftPlane.size(); i++) 
		{
			ObjectsLeftPlane[i]->SetIsAlive(true);
		}

		for (int i = 0; i < ObjectsRightPlane.size(); i++) 
		{
			ObjectsRightPlane[i]->SetIsAlive(false);
		}

		break;
	case CurrentCameraPosition::RightPlane:
		//Si la camara esta del lado derecho dibujo los objetos que se encuentran en el vector ObjectsRightPlane y
		//dejo de dibujar los objetos que se encuentran en el vector ObjectsLeftPlane.

		for (int i = 0; i < ObjectsLeftPlane.size(); i++)
		{
			ObjectsLeftPlane[i]->SetIsAlive(false);
		}

		for (int i = 0; i < ObjectsRightPlane.size(); i++)
		{
			ObjectsRightPlane[i]->SetIsAlive(true);
		}

		break;
	}
	
	//Limpio los vectores ObjectsLeftPlane y ObjectsRightPlane
	ObjectsLeftPlane.clear();
	ObjectsRightPlane.clear();

	//Checkeo de que lados estan los objetos y dependiendo de ello los pongo en un vector o en el otro

	for (int i = 0; i < ObjectsInGame.size(); i++) 
	{
		if(myPlane->getSide(ObjectsInGame[i]->transform.position))
		{
			ObjectsRightPlane.push_back(ObjectsInGame[i]);
		}
		else
		{
			ObjectsLeftPlane.push_back(ObjectsInGame[i]);
		}
	}
}
void Plane_BSP::RemoveItemObjectsInGame(int index)
{
	ObjectsInGame.erase(ObjectsInGame.begin() + index);
}



