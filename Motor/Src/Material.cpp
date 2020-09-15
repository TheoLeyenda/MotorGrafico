#include "Material.h"

Material::Material()
{
	_colorRGBA = {1.0f,0.0f,0.0f,1.0f};
}

Material::Material(float r, float g, float b, float a){
	_colorRGBA = { r,g,b,a};
}


Material::~Material()
{
}

void Material::SetMaterialValue(float r, float g, float b, float a){
	_colorRGBA = { r,g,b,a };
}

glm::vec4 Material::GetColorRGBA(){
	return _colorRGBA;
}
