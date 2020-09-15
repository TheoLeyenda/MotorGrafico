#ifndef MATERIAL_H
#define MATERIAL_H
#include "PrivateClass/Export.h"
#include "../Lib/glm/vec4.hpp"

class ENGINE_API Material
{
private:
	glm::vec4 _colorRGBA;
public:
	Material();
	Material(float r, float g, float b, float a);
	~Material();
	void SetMaterialValue(float r, float g, float b, float a);
	glm::vec4 GetColorRGBA();
};
#endif
