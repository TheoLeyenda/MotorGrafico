#include "Plane_BSP.h"
#include "Plane.h"
#include "BSP_Manager.h"
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

	//cout << "vertex_max_x: " << vertexPlaneBSP.vertex_max_x << endl;
	//cout << "vertex_max_y: " << vertexPlaneBSP.vertex_max_y << endl;
	//cout << "vertex_max_z: " << vertexPlaneBSP.vertex_max_z << endl;
	//cout << "vertex_min_x: " << vertexPlaneBSP.vertex_min_x << endl;
	//cout << "vertex_min_y: " << vertexPlaneBSP.vertex_min_y << endl;
	//cout << "vertex_min_z: " << vertexPlaneBSP.vertex_min_z << endl;
	//cout << "----------------------------------------------" << endl;

	if (planeAttach != NULL) 
	{
		glm::vec3 PointA = glm::vec3(0.0f); 
		glm::vec3 PointB = glm::vec3(0.0f);
		glm::vec3 PointC = glm::vec3(0.0f);
		if ((int)vertexPlaneBSP.vertex_min_x == 0 && (int)vertexPlaneBSP.vertex_max_x == 0)
		{
			//cout << "ENTRE AL PLANO EJE X" << endl;
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
			//cout << "ENTRE AL PLANO EJE Z" << endl;
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
			//cout << "ENTRE AL PLANO EJE Y" << endl;
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

		myPlane = new MyPlane(PointA, PointB, PointC);

		myPlane->flipPlane();
	}
}
void Plane_BSP::CheckObjectInPlaneBSP(Entity* ObjectCompare, int indexPlanePush, vector<int>& indexsDisableObjects)
{
	if (planeAttach != NULL)
	{
		if (!planeAttach->GetIsAlive())
			return;
	}

	if (myPlane == NULL)
		GeneratePlane(); // SE EJECUTA SOLO SI EL PLANO ES NULO.

	if (myPlane == NULL)
		return;


	if (myPlane == NULL || currentCameraCompare == NULL)
		return;

	if (myPlane->getSide(currentCameraCompare->transform.position))
	{
		currentCameraPosition = CurrentCameraPosition::PostivePlane;
	}
	else
	{
		currentCameraPosition = CurrentCameraPosition::NegativePlane;
	}

	//1)Asumir que por defecto todos los objetos estan prendidos
	//2)hacer el recorrido este en todos los planos.
	//3)Guardar en una lista auxiliar de ints que representan a los objetos en la lista que debo apagar original 
	//y despues aplico el prendido y apagado cuando termino el recorrido.

	switch (currentCameraPosition)
	{
	case CurrentCameraPosition::PostivePlane:
		if (!myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[0]) &&
			!myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[1]) &&
			!myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[2]) &&
			!myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[3]) &&
			!myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[4]) &&
			!myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[5]) &&
			!myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[6]) &&
			!myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[7]))
		{
			indexsDisableObjects.push_back(indexPlanePush);
		}

		break;
	case CurrentCameraPosition::NegativePlane:
		if (myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[0]) &&
			myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[1]) &&
			myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[2]) &&
			myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[3]) &&
			myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[4]) &&
			myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[5]) &&
			myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[6]) &&
			myPlane->getSide(ObjectCompare->GetAABBGlobalPositions()[7]))
		{
			indexsDisableObjects.push_back(indexPlanePush);
		}

		break;

	}
}

