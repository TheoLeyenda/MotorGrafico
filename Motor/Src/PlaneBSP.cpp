#include "PlaneBSP.h"

PlaneBSP::PlaneBSP(Renderer* render, string name, glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC)
	: Entity(render)
{
	namePlane = name;
	plane = new MyPlane(pointA, pointB, pointC);
}

PlaneBSP::~PlaneBSP()
{
	if (plane != NULL)
	{
		delete plane;
		plane = NULL;
	}
}

void PlaneBSP::BindBuffer()
{
	//Trhow not implemented exception xd
}

void PlaneBSP::Draw(bool & wireFrameActive)
{
	//Trhow not implemented exception xd
}

void PlaneBSP::SetEnableDrawAABB(bool value)
{
	//Trhow not implemented exception xd
}

bool PlaneBSP::ObjectPositiveSide(Entity* object)
{
	if (plane == NULL)
		return;

	if (plane->getSide(object->transform.position))
		return true;
	else
		return false;
}

void PlaneBSP::update_BSP_Plane(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC)
{
	if (plane != NULL)
	{
		plane->set3Points(pointA, pointB, pointC);
	}
}