#include "Material.h"
#include <iostream>

Material::Material()
{
	_colorRGB = {1.0f,0.0f,0.0f};
	_vertexColorRGB = NULL;
}

Material::Material(float r, float g, float b){
	SetMaterialValue(r,g,b);
	_vertexColorRGB = NULL;
}

Material::Material(float* arrayRGBA, int tamArrayRGBA, int repeticiones)
{
	SetMaterialValue(arrayRGBA, tamArrayRGBA, repeticiones);
	_vertexColorRGB = NULL;
}

Material::~Material()
{
	if (_vertexColorRGB != NULL) 
	{
		delete _vertexColorRGB;
	}
}

void Material::SetMaterialValue(float r, float g, float b){
	_colorRGB = { r,g,b};
	//std::cout << "r: " << _colorRGBA[0] << " g: " << _colorRGBA[1] << " b: " << _colorRGBA[2] << " a: " << _colorRGBA[3] << std::endl;
}

void Material::SetMaterialValue(float * arrayRGBA, int tamArrayRGBA, int repeticiones)
{
	if (_vertexColorRGB != NULL) 
	{
		delete _vertexColorRGB;
	}

	_vertexColorRGB = new glm::vec3[repeticiones];
	int j = 0;
	for (int k = 0; k < repeticiones; k++) 
	{
		for (int i = 0; i < tamArrayRGBA; i++)
		{
			_vertexColorRGB[k][i] = arrayRGBA[j];
			std::cout << _vertexColorRGB[k][i];
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

glm::vec3 Material::GetColorRGB(){
	return _colorRGB;
}

glm::vec3 * Material::GetVertexColorRGB()
{
	return _vertexColorRGB;
}