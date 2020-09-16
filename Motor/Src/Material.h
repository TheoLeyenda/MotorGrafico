#ifndef MATERIAL_H
#define MATERIAL_H
#include "PrivateClass/Export.h"
#include "../Lib/glm/vec4.hpp"

class ENGINE_API Material
{
private:
	glm::vec4 _colorRGBA;
	glm::vec4* _vertexColorRGBA;
public:
	Material();
	Material(float r, float g, float b, float a);
	Material(float* arrayRGBA, int tamArrayRGBA, int repeticiones);
	~Material();
	void SetMaterialValue(float r, float g, float b, float a);
	void SetMaterialValue(float* arrayRGBA, int tamArrayRGBA, int repeticiones);
	glm::vec4 GetColorRGBA();
	glm::vec4* GetVertexColorRGBA();
};
#endif
