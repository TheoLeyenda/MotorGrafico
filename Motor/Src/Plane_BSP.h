#ifndef PLANE_BSP_H
#define PLANE_BSP_H

#include "PrivateClass/Export.h"

#include "Entity.h"
#include "Primitive3D.h"

class ENGINE_API Plane_BSP : Entity 
{

private:
	Primitive3D* myPrimitive = NULL;
	float valueScaleZ = 0.5f;
protected:
	void BindBuffer() override;
	void SetEnableDrawAABB(bool value) override;
public:

	Plane_BSP(Renderer* renderer);
	~Plane_BSP();
	void SetMaterialPlane(Material* mat);
	void SetScalePlane(float scaleX, float scaleY);
	virtual void SetPosition(float x, float y, float z);
	virtual void SetPosition(glm::vec3 position);
	virtual void SetRotationX(float x);
	virtual void SetRotationY(float y);
	virtual void SetRotationZ(float z);

	virtual string GetClassName()
	{
		return "Plane_BSP";
	}

	void Draw(bool& wireFrameActive) override;
};

#endif
