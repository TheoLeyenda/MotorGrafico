#include "Material.h"
#include <iostream>

Material::Material()
{
	_colorRGBA = {1.0f,0.0f,0.0f,1.0f};
	_vertexColorRGBA = NULL;
}

Material::Material(float r, float g, float b, float a){
	SetMaterialValue(r,g,b,a);
	_vertexColorRGBA = NULL;
}

Material::Material(float* arrayRGBA, int tamArrayRGBA, int repeticiones)
{
	SetMaterialValue(arrayRGBA, tamArrayRGBA, repeticiones);
	_vertexColorRGBA = NULL;
}


Material::~Material()
{
	if (_vertexColorRGBA != NULL) 
	{
		delete _vertexColorRGBA;
	}
}

void Material::SetMaterialValue(float r, float g, float b, float a){
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

glm::vec4 Material::GetColorRGBA(){
	return _colorRGBA;
}

glm::vec4 * Material::GetVertexColorRGBA()
{
	return _vertexColorRGBA;
}
