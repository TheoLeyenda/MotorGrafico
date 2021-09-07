#ifndef PLANEBSP_H
#define PLANEBSP_H

#include <iostream>
#include "PrivateClass/Export.h"
#include "Plane.h"

using namespace std;

class Entity;

class ENGINE_API PlaneBSP
{
private:
	string namePlane;
	MyPlane* plane;

public:
	PlaneBSP(string name, glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC);
	~PlaneBSP();

	void flipPlaneBSP();

	bool ObjectPositiveSide(Entity* object);
	glm::vec3 getPlaneNormal() 
	{ 
		if (plane != NULL) 
			return plane->getNormal(); 
	}
	void update_BSP_Plane(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC);
};

#endif // !PLANEBSP_H