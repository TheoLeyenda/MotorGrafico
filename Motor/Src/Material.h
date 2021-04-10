#ifndef MATERIAL_H
#define MATERIAL_H
#include "PrivateClass/Export.h"
#include "../Lib/glm/vec4.hpp"
#include "../Lib/glm/vec3.hpp"

class ENGINE_API Material
{
private:
	glm::vec4 _colorRGBA;
	glm::vec4* _vertexColorRGBA;

	//LIGTH
	float _specularIntensity;
	float _shininess;
	//-----------
public:
	Material();
	Material(float r, float g, float b, float a);
	Material(float* arrayRGBA, int tamArrayRGBA, int repeticiones);

	//LIGTH
	Material(float sIntensity,float shine);
	//void UseMaterial(unsigned int specularIntensityLoc, unsigned int shininessLoc);

	float GetSpecularIntensity() { return _specularIntensity; }
	float GetShininess() { return _shininess; }
	void SetNewShininess(float value);
	void SetNewSpecularIntensity(float value);
	//-----------
	~Material();
	void SetMaterialValue(float r, float g, float b, float a);
	void SetMaterialValue(float* arrayRGBA, int tamArrayRGBA, int repeticiones);
	glm::vec4 GetColorRGBA();
	glm::vec4* GetVertexColorRGBA();
};
#endif
