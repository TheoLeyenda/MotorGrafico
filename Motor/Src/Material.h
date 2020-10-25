#ifndef MATERIAL_H
#define MATERIAL_H
#include "PrivateClass/Export.h"
#include "../Lib/glm/vec4.hpp"
#include "../Lib/glm/vec3.hpp"

class ENGINE_API Material
{
private:
	glm::vec3 _colorRGB;
	glm::vec3* _vertexColorRGB;
public:
	Material();
	Material(float r, float g, float b);
	Material(float* arrayRGBA, int tamArrayRGBA, int repeticiones);
	~Material();
	void SetMaterialValue(float r, float g, float b);
	void SetMaterialValue(float* arrayRGBA, int tamArrayRGBA, int repeticiones);
	glm::vec3 GetColorRGB();
	glm::vec3* GetVertexColorRGB();
};
#endif
