#include "PlaneBSP.h"
#include "Entity.h"

PlaneBSP::PlaneBSP(string name, glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC)
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

void PlaneBSP::flipPlaneBSP()
{
	if (plane == NULL)
		return;

	plane->flipPlane();
}

bool PlaneBSP::ObjectPositiveSide(Entity* object)
{
	if (plane == NULL || object == NULL)
		return false;

	if (plane->getSide(object->transform.globalPosition))
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