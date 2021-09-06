#ifndef PLANEBSP_H
#define PLANEBSP_H

#include <istream>
#include "Entity.h"
#include "PrivateClass/Export.h"
#include "Plane.h"

using namespace std;

class ENGINE_API PlaneBSP : public  Entity
{
private:
	string namePlane;
	MyPlane* plane;

public:
	PlaneBSP(Renderer* render,string name, glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC);
	~PlaneBSP();

	void BindBuffer();
	void Draw(bool& wireFrameActive);
	void SetEnableDrawAABB(bool value);

	bool ObjectPositiveSide(Entity* object);
	glm::vec3 getPlaneNormal() { if (!plane) return plane->getNormal(); }
	void update_BSP_Plane(glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC);
};

#endif // !PLANEBSP_H