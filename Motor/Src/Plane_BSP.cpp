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
void Plane_BSP::SetCurrentCameraCompare(Entity * camera)
{
	currentCameraCompare = camera;
}
Entity * Plane_BSP::GetPlaneAttach()
{
	return planeAttach;
}

void Plane_BSP::GeneratePlane()
{

	cout << "vertex_max_x: " << vertexPlaneBSP.vertex_max_x << endl;
	cout << "vertex_max_y: " << vertexPlaneBSP.vertex_max_y << endl;
	cout << "vertex_max_z: " << vertexPlaneBSP.vertex_max_z << endl;
	cout << "vertex_min_x: " << vertexPlaneBSP.vertex_min_x << endl;
	cout << "vertex_min_y: " << vertexPlaneBSP.vertex_min_y << endl;
	cout << "vertex_min_z: " << vertexPlaneBSP.vertex_min_z << endl;
	cout << "----------------------------------------------" << endl;
	//EL QUE VALGA 0 ES LA NORMAL.

	if (planeAttach != NULL) 
	{
		glm::vec3 PointA = glm::vec3(0.0f); 
		glm::vec3 PointB = glm::vec3(0.0f);
		glm::vec3 PointC = glm::vec3(0.0f);
		if ((int)vertexPlaneBSP.vertex_min_x == 0 && (int)vertexPlaneBSP.vertex_max_x == 0)
		{
			cout << "ENTRE AL PLANO EJE X" << endl;
			PointA = glm::vec3(planeAttach->transform.globalPosition.x
				, planeAttach->transform.globalPosition.y + (planeAttach->transform.scale.y)
				, planeAttach->transform.globalPosition.z);

			PointB = glm::vec3(planeAttach->transform.globalPosition.x
				, planeAttach->transform.globalPosition.y
				, planeAttach->transform.globalPosition.z + (planeAttach->transform.scale.z));

			PointC = glm::vec3(planeAttach->transform.globalPosition.x
				, planeAttach->transform.globalPosition.y
				, planeAttach->transform.globalPosition.z);
		}
		else if((int)vertexPlaneBSP.vertex_min_y == 0 && (int)vertexPlaneBSP.vertex_max_y == 0)
		{
			cout << "ENTRE AL PLANO EJE Z" << endl;
			PointA = glm::vec3(planeAttach->transform.globalPosition.x + (planeAttach->transform.scale.x)
				, planeAttach->transform.globalPosition.y
				, planeAttach->transform.globalPosition.z);

			PointB = glm::vec3(planeAttach->transform.globalPosition.x
				, planeAttach->transform.globalPosition.y + (planeAttach->transform.scale.y)
				, planeAttach->transform.globalPosition.z);

			PointC = glm::vec3(planeAttach->transform.globalPosition.x
				, planeAttach->transform.globalPosition.y
				, planeAttach->transform.globalPosition.z);
		}
		else if ((int)vertexPlaneBSP.vertex_min_z == 0 && (int)vertexPlaneBSP.vertex_max_z == 0)
		{
			cout << "ENTRE AL PLANO EJE Y" << endl;
			PointA = glm::vec3(planeAttach->transform.globalPosition.x + (planeAttach->transform.scale.x)
				, planeAttach->transform.globalPosition.y
				, planeAttach->transform.globalPosition.z);

			PointB = glm::vec3(planeAttach->transform.globalPosition.x
				, planeAttach->transform.globalPosition.y
				, planeAttach->transform.globalPosition.z + (planeAttach->transform.scale.z));

			PointC = glm::vec3(planeAttach->transform.globalPosition.x
				, planeAttach->transform.globalPosition.y
				, planeAttach->transform.globalPosition.z);
		}
		


		if (myPlane == NULL)
			myPlane = new MyPlane(PointA, PointB, PointC);
		else
			myPlane->set3Points(PointA, PointB, PointC);

		myPlane->flipPlane();
	}
}
void Plane_BSP::UpdatePlane_BSP(vector<string> registerKeysBSP)
{
	if (planeAttach != NULL) 
	{
		if (!planeAttach->GetIsAlive())
			return;
	}

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
		if (myPlane->getSide(ObjectsInGame[i]->transform.position))
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



