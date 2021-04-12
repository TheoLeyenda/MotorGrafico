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

	//MATERIAL
	glm::vec3 _ambientMat;
	glm::vec3 _diffuseMat;
	glm::vec3 _specularMat;
	//-----------

public:
	Material();
	Material(float r, float g, float b, float a);
	Material(float* arrayRGBA, int tamArrayRGBA, int repeticiones);

	//LIGTH
	Material(float sIntensity,float shine);
	Material(float r, float g, float b, float sIntensity, float shine);
	Material(float r, float g, float b, float sIntensity, float shine, glm::vec3 ambientMat, glm::vec3 diffuseMat, glm::vec3 specularMat);

	//Devuelve el promedio de los tres valores del _ambientMat.
	float GetAverageAmbientMat();
	
	//Devuelve el promedio de los tres valores del _diffuseMat.
	float GetAverageDiffuseMat();

	//Devuelve el promedio de los tres valores del _specularMat.
	float GetAverageSpecularMat();

	//Devuelve el promedio de los tres valores del _ambientMat multiplicado por multyplay.
	float GetAverageAmbientMatMultyplay(float multyplay);

	//Devuelve el promedio de los tres valores del _diffuseMat multiplicado por multyplay.
	float GetAverageDiffuseMatMultyplay(float multyplay);

	//Devuelve el promedio de los tres valores del _specularMat multiplicado por multyplay.
	float GetAverageSpecularMatMultyplay(float multyplay);

	//Devuelve el promedio de los tres valores del _ambientMat potenciado por pow.
	float GetAverageAmbientMatPow(float pow);

	//Devuelve el promedio de los tres valores del _diffuseMat potenciado por pow.
	float GetAverageDiffuseMatPow(float pow);

	//Devuelve el promedio de los tres valores del _specularMat potenciado por pow.
	float GetAverageSpecularMatPow(float pow);

	void SetAmbientMat(glm::vec3 ambientMat);

	void SetDiffuseMat(glm::vec3 diffuseMat);

	void SetSpecularMat(glm::vec3 specularMat);

	glm::vec3 GetAmbientMat();

	glm::vec3 GetDiffuseMat();

	glm::vec3 GetSpecularMat();

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
