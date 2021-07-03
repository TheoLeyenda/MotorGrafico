#include "EmptyObject.h"
#include <glew.h>
#include <GLFW/glfw3.h>


EmptyObject::EmptyObject(Renderer* render) :Entity(render) 
{
	InmortalObject = true;
}

void EmptyObject::BindBuffer() {}
void EmptyObject::Draw(bool & wireFrameActive)
{
	renderer->Draw(0, renderer->GetCurrentShaderUse(), internalData.localModel, wireFrameActive);
}

string EmptyObject::GetClassName()
{
	return "EmptyObject";
}

EmptyObject::~EmptyObject(){}
