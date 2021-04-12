#include "Material.h"
#include <iostream>

#include <glew.h>
#include <GLFW/glfw3.h>

Material::Material()
{
	_colorRGBA = { 1.0f,0.0f,0.0f,1.0f };
	_vertexColorRGBA = NULL;
	_specularIntensity = 0.0f;
	_shininess = 0.0f;

	_ambientMat[0] = 0;
	_ambientMat[1] = 0;
	_ambientMat[2] = 0;

	_diffuseMat[0] = 0;
	_diffuseMat[1] = 0;
	_diffuseMat[2] = 0;

	_specularMat[0] = 0;
	_specularMat[1] = 0;
	_specularMat[2] = 0;
}

Material::Material(float r, float g, float b, float a) {
	SetMaterialValue(r, g, b, a);
	_vertexColorRGBA = NULL;

	_specularIntensity = 0;
	_shininess = 0;

	_ambientMat[0] = 0;
	_ambientMat[1] = 0;
	_ambientMat[2] = 0;

	_diffuseMat[0] = 0;
	_diffuseMat[1] = 0;
	_diffuseMat[2] = 0;

	_specularMat[0] = 0;
	_specularMat[1] = 0;
	_specularMat[2] = 0;
}

Material::Material(float* arrayRGBA, int tamArrayRGBA, int repeticiones)
{
	SetMaterialValue(arrayRGBA, tamArrayRGBA, repeticiones);
	_vertexColorRGBA = NULL;

	_specularIntensity = 0;
	_shininess = 0;

	_ambientMat[0] = 0;
	_ambientMat[1] = 0;
	_ambientMat[2] = 0;

	_diffuseMat[0] = 0;
	_diffuseMat[1] = 0;
	_diffuseMat[2] = 0;

	_specularMat[0] = 0;
	_specularMat[1] = 0;
	_specularMat[2] = 0;
}

Material::Material(float sIntensity, float shine)
{
	_specularIntensity = sIntensity;
	_shininess = shine;

	_ambientMat[0] = 0;
	_ambientMat[1] = 0;
	_ambientMat[2] = 0;

	_diffuseMat[0] = 0;
	_diffuseMat[1] = 0;
	_diffuseMat[2] = 0;

	_specularMat[0] = 0;
	_specularMat[1] = 0;
	_specularMat[2] = 0;
}

Material::Material(float r, float g, float b, float sIntensity, float shine)
{
	SetMaterialValue(r, g, b, 1.0f);
	_shininess = shine;
	_specularIntensity = sIntensity;

	_ambientMat[0] = 0;
	_ambientMat[1] = 0;
	_ambientMat[2] = 0;

	_diffuseMat[0] = 0;
	_diffuseMat[1] = 0;
	_diffuseMat[2] = 0;

	_specularMat[0] = 0;
	_specularMat[1] = 0;
	_specularMat[2] = 0;
}

Material::Material(float r, float g, float b, float sIntensity, float shine, glm::vec3 ambientMat, glm::vec3 diffuseMat, glm::vec3 specularMat)
{
	SetMaterialValue(r, g, b, 1.0f);
	_shininess = shine;
	_specularIntensity = sIntensity;
	
	_ambientMat[0] = ambientMat[0];
	_ambientMat[1] = ambientMat[1];
	_ambientMat[2] = ambientMat[2];

	_diffuseMat[0] = diffuseMat[0];
	_diffuseMat[1] = diffuseMat[1];
	_diffuseMat[2] = diffuseMat[2];

	_specularMat[0] = specularMat[0];
	_specularMat[1] = specularMat[1];
	_specularMat[2] = specularMat[2];
}

float Material::GetAverageAmbientMat()
{
	float result = 0;

	result = _ambientMat[0] + _ambientMat[1] + _ambientMat[2];

	result = result / 3;

	return result;
}

float Material::GetAverageDiffuseMat()
{
	float result = 0;

	result = _diffuseMat[0] + _diffuseMat[1] + _diffuseMat[2];

	result = result / 3;

	return result;
}

float Material::GetAverageSpecularMat()
{
	float result = 0;

	result = _specularMat[0] + _specularMat[1] + _specularMat[2];

	result = result / 3;

	return result;
}

float Material::GetAverageAmbientMatMultyplay(float multyplay)
{
	return GetAverageAmbientMat() * multyplay;
}

float Material::GetAverageDiffuseMatMultyplay(float multyplay)
{
	return GetAverageDiffuseMat() * multyplay;
}

float Material::GetAverageSpecularMatMultyplay(float multyplay)
{
	return GetAverageSpecularMat() * multyplay;
}

float Material::GetAverageAmbientMatPow(float pow)
{
	return powf(GetAverageAmbientMat(), pow);
}

float Material::GetAverageDiffuseMatPow(float pow)
{
	return powf(GetAverageDiffuseMat(), pow);
}

float Material::GetAverageSpecularMatPow(float pow)
{
	return powf(GetAverageSpecularMat(), pow);
}

void Material::SetAmbientMat(glm::vec3 ambientMat)
{
	_ambientMat[0] = ambientMat[0];
	_ambientMat[1] = ambientMat[1];
	_ambientMat[2] = ambientMat[2];
}

void Material::SetDiffuseMat(glm::vec3 diffuseMat)
{
	_diffuseMat[0] = diffuseMat[0];
	_diffuseMat[1] = diffuseMat[1];
	_diffuseMat[2] = diffuseMat[2];
}

void Material::SetSpecularMat(glm::vec3 specularMat)
{
	_specularMat[0] = specularMat[0];
	_specularMat[1] = specularMat[1];
	_specularMat[2] = specularMat[2];
}

glm::vec3 Material::GetAmbientMat()
{
	return _ambientMat;
}

glm::vec3 Material::GetDiffuseMat()
{
	return _diffuseMat;
}

glm::vec3 Material::GetSpecularMat()
{
	return _specularMat;
}

void Material::SetNewShininess(float value)
{
	_shininess = value;
}

void Material::SetNewSpecularIntensity(float value)
{
	_specularIntensity = value;
}

Material::~Material()
{
	if (_vertexColorRGBA != NULL)
	{
		delete _vertexColorRGBA;
	}
}

void Material::SetMaterialValue(float r, float g, float b, float a) {
	_colorRGBA = { r,g,b,a };
	//std::cout << "r: " << _colorRGBA[0] << " g: " << _colorRGBA[1] << " b: " << _colorRGBA[2] << " a: " << _colorRGBA[3] << std::endl;
}

void Material::SetMaterialValue(float * arrayRGBA, int tamArrayRGBA, int repeticiones)
{
	if (_vertexColorRGBA != NULL)
	{
		delete _vertexColorRGBA;
	}

	_vertexColorRGBA = new glm::vec4[repeticiones];
	int j = 0;
	for (int k = 0; k < repeticiones; k++)
	{
		for (int i = 0; i < tamArrayRGBA; i++)
		{
			_vertexColorRGBA[k][i] = arrayRGBA[j];
			std::cout << _vertexColorRGBA[k][i];
			j++;
		}
		std::cout << std::endl;
	}
	/*
	float ColorQuad[]
	{
		1.0f,0.0f,0.0f,1.0f,
		0.0f,1.0f,0.0f,1.0f,
		0.0f,0.0f,1.0f,1.0f,
		1.0f,0.0f,1.0f,1.0f,
	};
	*/
}

glm::vec4 Material::GetColorRGBA() {
	return _colorRGBA;
}

glm::vec4 * Material::GetVertexColorRGBA()
{
	return _vertexColorRGBA;
}