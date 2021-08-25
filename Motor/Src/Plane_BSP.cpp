#include "Plane_BSP.h"

void Plane_BSP::BindBuffer(){}

void Plane_BSP::SetEnableDrawAABB(bool value){}

Plane_BSP::Plane_BSP(Renderer * renderer) : Entity(renderer)
{
	myPrimitive = new Primitive3D(renderer);
	myPrimitive->SetScale(5, 5, valueScaleZ);
}

Plane_BSP::~Plane_BSP()
{
	if (myPrimitive != NULL) {
		delete myPrimitive;
		myPrimitive = NULL;
	}
}

void Plane_BSP::SetMaterialPlane(Material * mat)
{
	myPrimitive->SetNewMaterial(mat);
}

void Plane_BSP::SetScalePlane(float scaleX, float scaleY)
{
	myPrimitive->SetScale(scaleX, scaleY, valueScaleZ);
}

void Plane_BSP::SetPosition(float x, float y, float z)
{
	myPrimitive->SetPosition(x, y, z);
}

void Plane_BSP::SetPosition(glm::vec3 position)
{
	myPrimitive->SetPosition(position);
}

void Plane_BSP::SetRotationX(float x)
{
	myPrimitive->SetRotationX(x);
}

void Plane_BSP::SetRotationY(float y)
{
	myPrimitive->SetRotationY(y);
}

void Plane_BSP::SetRotationZ(float z)
{
	myPrimitive->SetRotationZ(z);
}

void Plane_BSP::Draw(bool & wireFrameActive)
{
	myPrimitive->Draw(wireFrameActive);
}
