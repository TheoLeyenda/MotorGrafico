#include "Light.h"

#include "Camera.h"
#include "glew.h"
#include "GLFW/glfw3.h"
#include <sstream>

int Light::nr_of_directional_light = 0;
int Light::nr_of_point_light = 0;
int Light::nr_of_spot_light = 0;

//int Asteroide::_cantAsteroides = 0;

Light::Light(Renderer * _render, TypeLight type) : Entity(_render)
{
	_colour = glm::vec3(0.0f, 0.0f, 0.0f);
	_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	_diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	_specular = glm::vec3(0.0f, 0.0f, 0.0f);
	_typeLight = type;

	//SetBoolsTypeLight();

	switch (_typeLight)
	{
	case TypeLight::Directional:
		nr_of_directional_light++;
		SetDirectionLight(glm::vec3(-0.2f, -1.0f, -2.3f));
		break;
	case TypeLight::Point:
		nr_of_point_light++;
		SetTypeLightPoint();
		break;
	case TypeLight::Spot:
		nr_of_spot_light++;
		SetTypeLightSpot();
		break;
	default:
		break;
	}

	UpdateCountLightInShader(_render->GetShaderColor());

	CreateDataLight();
}

Light::Light(glm::vec3 colour, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Renderer * render, TypeLight type) : Entity(render)
{ 
	_colour = colour;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_typeLight = type;

	SetBoolsTypeLight();

	switch (_typeLight)
	{
	case TypeLight::Directional:
		nr_of_directional_light++;
		SetDirectionLight(glm::vec3(-0.2f, -1.0f, -2.3f));
		break;
	case TypeLight::Point:
		nr_of_point_light++;
		SetTypeLightPoint();
		break;
	case TypeLight::Spot:
		nr_of_spot_light++;
		SetTypeLightSpot();
		break;
	default:
		break;
	}

	UpdateCountLightInShader(render->GetShaderColor());

	CreateDataLight();
}

void Light::SetCountLightInShader(Shader shader)
{
	nr_of_directional_lightLocation = glGetUniformLocation(shader.getId(), "nr_of_directional_light");
	nr_of_point_lightsLocation = glGetUniformLocation(shader.getId(), "nr_of_point_lights");
	nr_of_spot_lightLocation = glGetUniformLocation(shader.getId(), "nr_of_spot_light");
}

void Light::UpdateCountLightInShader(Shader shader)
{
	CheckIsModel();
	renderer->GetShaderColor().use();
	SetCountLightInShader(shader);
	glUniform1i(nr_of_directional_lightLocation, nr_of_directional_light);
	glUniform1i(nr_of_point_lightsLocation, nr_of_point_light);
	glUniform1i(nr_of_spot_lightLocation, nr_of_spot_light);
	glUseProgram(0);
}

void Light::UseLight(Camera * cameraIn)
{
	CheckIsModel();

	renderer->GetShaderColor().use();

	switch (_typeLight)
	{
	case Light::Point:
#pragma region POINT LIGHT
		glUniform3f(_uniformPosLightPointLoc, this->transform.position.x, this->transform.position.y, this->transform.position.z);

		glUniform1f(_uniformConstPointLight, _constValuePoint);

		glUniform1f(_uniformLinearPointLight, _linearValuePoint);

		glUniform1f(_uniformQuadraticPointLight, _quadraticValuePoint);

		glUniform3f(_uniformAmbientPointLoc, _ambient.x, _ambient.y, _ambient.z);

		glUniform3f(_uniformDiffusePointLoc, _diffuse.x, _diffuse.y, _diffuse.z);

		glUniform3f(_uniformSpecularPointLoc, _specular.x, _specular.y, _specular.z);
#pragma endregion
		break;
	case Light::Directional:
#pragma region DIRECTIONAL LIGHT
		glUniform3f(_uniformDirectionLocation, _directionDirectinal.x, _directionDirectinal.y, _directionDirectinal.z);

		glUniform3f(_uniformAmbDirectionalLoc, _ambient.x, _ambient.y, _ambient.z);

		glUniform3f(_uniformDiffDirectionalLoc, _diffuse.x, _diffuse.y, _diffuse.z);

		glUniform3f(_uniformSpecDirectionalLoc, _specular.x, _specular.y, _specular.z);
#pragma endregion
		break;
	case Light::Spot:
#pragma region SPOT LIGHT
		glUniform3f(_uniformPosLightSpotLoc, this->transform.position.x, this->transform.position.y, this->transform.position.z);

		glUniform1f(_uniformCutOffSpotLight, glm::cos(glm::radians(_cutOffValueSpot)));

		glUniform1f(_uniformOuterCutOffSpotLight, glm::cos(glm::radians(_outerCutOffValueSpot)));

		glUniform1f(_uniformConstSpotLight, _constValueSpot);

		glUniform1f(_uniformLinearSpotLight, _linearValueSpot);

		glUniform1f(_uniformQuadraticSpotLight, _quadraticValueSpot);

		glUniform3f(_uniformAmbientSpotLoc, _ambient.x, _ambient.y, _ambient.z);

		glUniform3f(_uniformDiffuseSpotLoc, _diffuse.x, _diffuse.y, _diffuse.z);

		glUniform3f(_uniformSpecularSpotLoc, _specular.x, _specular.y, _specular.z);

		glUniform3f(_uniformSpotLightDirection, transform.backward.x, transform.backward.y, transform.backward.z);
#pragma endregion
		break;
	}

#pragma region BASIC LIGHTING (POS LIGHT)
	glUniform3f(_uniformPosCameraLocation, cameraIn->transform.position.x,
		cameraIn->transform.position.y, cameraIn->transform.position.z);

	glUniform3f(_unifromColourLocation, _colour.x, _colour.y, _colour.z);

#pragma endregion

	glUseProgram(0);
}

void Light::Draw()
{
	renderer->DrawLight(lightIndicesCubeCount, renderer->GetShaderColor(),
		this->internalData.model, _vboLight, _iboLight, _posAttribLight, _colAttribLight);
}

void Light::SetColorLight(float r, float g, float b)
{
	_colour = glm::vec3(r, g, b);
}

glm::vec3 Light::GetColorLight()
{
	return _colour;
}

void Light::SetTypeLightDefault(TypeLight type)
{
	switch (type)
	{
	case Light::Point:
		SetTypeLightPoint();
		break;
	case Light::Directional:
		SetTypeLightDirectional();
		break;
	case Light::Spot:
		SetTypeLightSpot();
		break;
	}
}

void Light::SetPointLightCustom(float linearVal, float quadraticVal, float cutOffValue)
{
	SetTypeLightPoint(linearVal, quadraticVal, cutOffValue);
}

void Light::SetSpotLightCustom(float linearVal, float quadraticVal, float cutOffValue, float outerCutOffValue)
{
	SetTypeLightSpot(linearVal, quadraticVal, cutOffValue, outerCutOffValue);
}

void Light::SetDirectionalLightCustom(glm::vec3 direction)
{
	SetTypeLightDirectional(direction);
}

void Light::SetUniformColourLocation(Shader& shader)
{
	_unifromColourLocation = glGetUniformLocation(shader.getId(), "lightSource.colour");
}
//================================================
//DIRECTIONAL LIGHT
void Light::SetUniformAmbDirectionalLoc(Shader& shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "dirLight[" + iterS.str() + "].ambient";

	_uniformAmbDirectionalLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformDiffDirectionalLoc(Shader& shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "dirLight[" + iterS.str() + "].diffuse";

	_uniformDiffDirectionalLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformSpecDirectionalLoc(Shader& shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "dirLight[" + iterS.str() + "].specular";

	_uniformSpecDirectionalLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformDirectionLightLocation(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "dirLight[" + iterS.str() + "].direction";

	_uniformDirectionLocation = glGetUniformLocation(shader.getId(), result.c_str());
}

//================================================
//POINT LIGHT

void Light::SetUniformConstPointLight(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "pointLight[" + iterS.str() + "].constant";

	_uniformConstPointLight = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformAmbientPointLoc(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "pointLight[" + iterS.str() + "].ambient";
	
	_uniformAmbientPointLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformDiffPointLoc(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "pointLight[" + iterS.str() + "].diffuse";

	_uniformDiffusePointLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformSpecPointLoc(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "pointLight[" + iterS.str() + "].specular";

	_uniformSpecularPointLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformLinearPointLight(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "pointLight[" + iterS.str() + "].linear";

	_uniformLinearPointLight = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformQuadraticPointLight(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "pointLight[" + iterS.str() + "].quadratic";

	_uniformQuadraticPointLight = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformPosLightPoint(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "pointLight[" + iterS.str() + "].posLight";
	
	_uniformPosLightPointLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

//================================================
//SPOT LIGHT
void Light::SetUniformCutOffSopttLight(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].cutOff";

	_uniformCutOffSpotLight = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformOuterCutOffSopttLight(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].outerCutOff";

	_uniformOuterCutOffSpotLight = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformPosLightSpot(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].posLight";

	_uniformPosLightSpotLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformSpotLightDirection(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].direction";

	_uniformSpotLightDirection = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformAmbientSpotLoc(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].ambient";

	_uniformAmbientSpotLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformDiffSpotLoc(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].diffuse";

	_uniformDiffuseSpotLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformSpecSpotLoc(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].specular";

	_uniformSpecularSpotLoc = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformLinearSpotLight(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].linear";

	_uniformLinearSpotLight = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformQuadraticSpotLight(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].quadratic";

	_uniformQuadraticSpotLight = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformConstSpotLight(Shader & shader, int iter)
{
	stringstream iterS;
	iterS << iter;
	string result = "spotLight[" + iterS.str() + "].constant";

	_uniformConstSpotLight = glGetUniformLocation(shader.getId(), result.c_str());
}

void Light::SetUniformPosCameraLocation(Shader & shader)
{
	_uniformPosCameraLocation = glGetUniformLocation(shader.getId(), "cameraPos");
}

void Light::SetTypeLightPoint(float linearVal, float quadraticVal, float cutOffValue)
{
	SetPointLight(linearVal, quadraticVal);
	SetCutOffSpotLight(cutOffValue);

	if(_typeLight != TypeLight::Point)
		nr_of_point_light++;
	
	_typeLight = TypeLight::Point;

	/*
	if (nr_of_directional_light > 0)
		nr_of_directional_light--;

	if (nr_of_spot_light > 0)
		nr_of_spot_light--;
	*/

	UpdateCountLightInShader(renderer->GetShaderColor());
	
}

void Light::SetTypeLightPoint()
{
	SetPointLight(0.0014f, 0.000007f);
	//SetCutOffSpotLight(12.5f);
	
	if(_typeLight != TypeLight::Point)
		nr_of_point_light++;

	_typeLight = TypeLight::Point;

	/*
	if (nr_of_directional_light > 0)
		nr_of_directional_light--;

	if (nr_of_spot_light > 0)
		nr_of_spot_light--;
	*/

	UpdateCountLightInShader(renderer->GetShaderColor());

	SetBoolsTypeLight();
}

void Light::SetTypeLightSpot(float linearVal, float quadraticVal, float cutOffValue, float outerCutOffValue)
{
	SetPointLight(linearVal, quadraticVal);
	SetCutOffSpotLight(cutOffValue);
	SetOuterCutOffSpotLight(outerCutOffValue);

	if (_typeLight != TypeLight::Spot)
		nr_of_spot_light++;
	
	_typeLight = TypeLight::Spot;

	/*
	if (nr_of_directional_light > 0)
		nr_of_directional_light--;

	if (nr_of_point_light > 0)
		nr_of_point_light--;
	*/

	UpdateCountLightInShader(renderer->GetShaderColor());

	SetBoolsTypeLight();
}

void Light::SetTypeLightSpot()
{
	SetSpotLight(0.0014f, 0.000007f);
	SetCutOffSpotLight(12.5f);
	SetOuterCutOffSpotLight(17.5f);
	
	if (_typeLight != TypeLight::Spot)
		nr_of_spot_light++;
	
	_typeLight = TypeLight::Spot;

	/*
	if (nr_of_directional_light > 0)
		nr_of_directional_light--;

	if (nr_of_point_light > 0)
		nr_of_point_light--;
	*/

	UpdateCountLightInShader(renderer->GetShaderColor());

	SetBoolsTypeLight();
}

void Light::SetTypeLightDirectional()
{
	SetDirectionLight(glm::vec3(-0.2f, -1.0f, -2.3f));

	if (_typeLight != TypeLight::Directional)
		nr_of_directional_light++;

	_typeLight = TypeLight::Directional;

	/*
	if (nr_of_spot_light > 0)
		nr_of_spot_light--;

	if (nr_of_point_light > 0)
		nr_of_point_light--;
	*/

	UpdateCountLightInShader(renderer->GetShaderColor());

	SetBoolsTypeLight();
}

void Light::SetTypeLightDirectional(glm::vec3 direction)
{
	SetDirectionLight(direction);

	if(_typeLight != TypeLight::Directional)
		nr_of_directional_light++;
	
	_typeLight = TypeLight::Directional;

	/*
	if (nr_of_spot_light > 0)
		nr_of_spot_light--;

	if (nr_of_point_light > 0)
		nr_of_point_light--;
	*/

	UpdateCountLightInShader(renderer->GetShaderColor());

	SetBoolsTypeLight();
}

void Light::SetPointLight(float linearVal, float quadraticVal)
{
	SetLinearValuePoint(linearVal);
	SetQuadraticValuePoint(quadraticVal);
}

void Light::SetSpotLight(float linearVal, float quadraticVal)
{
	SetLinearValueSpot(linearVal);
	SetQuadraticValueSpot(quadraticVal);
}

Light::~Light() 
{
	switch (_typeLight)
	{
	case Light::Point:
		nr_of_point_light--;
		break;
	case Light::Directional:
		nr_of_directional_light--;
		break;
	case Light::Spot:
		nr_of_spot_light--;
		break;
	}
	UpdateCountLightInShader(renderer->GetShaderColor());
}

void Light::SetVAO()
{
	glGenVertexArrays(1, &_vaoLight);
	glBindVertexArray(_vaoLight);
}

void Light::SetVBO()
{
	glGenBuffers(1, &_vboLight);
	glBindBuffer(GL_ARRAY_BUFFER, _vboLight);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lightSourceCube), lightSourceCube, GL_STATIC_DRAW);

	_posAttribLight = glGetAttribLocation(renderer->GetShaderColor().getId(), "position");
	glVertexAttribPointer(_posAttribLight, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttribLight);

	_colAttribLight = glGetAttribLocation(renderer->GetShaderColor().getId(), "customColor");
	glVertexAttribPointer(_colAttribLight, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colAttribLight);
}

void Light::SetIBO()
{
	glGenBuffers(1, &_iboLight);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboLight);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexCubeLight), indexCubeLight, GL_STATIC_DRAW);
}

void Light::BindVAO()
{
	glBindVertexArray(_vaoLight);
}

void Light::BindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iboLight);
}

void Light::BindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboLight);

	_posAttribLight = glGetAttribLocation(renderer->GetShaderColor().getId(), "position");
	glVertexAttribPointer(_posAttribLight, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttribLight);
	_colAttribLight = glGetAttribLocation(renderer->GetShaderColor().getId(), "customColor");
	glVertexAttribPointer(_colAttribLight, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(_colAttribLight);
}

void Light::UnbindIBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Light::UnbindVAO()
{
	glBindVertexArray(0);
}

void Light::UnbindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Light::CreateDataLight()
{
	//---
	SetVAO();
	//---
	SetIBO();
	//---
	SetVBO();
	//---
	UnbindBuffers();
	//---
}

void Light::SetBoolsTypeLight()
{
	switch (_typeLight)
	{
	case Light::Point:
		_isPoint = 1;
		_isDirectional = 0;
		_isSpot = 0;
		break;
	case Light::Directional:
		_isDirectional = 1;
		_isPoint = 0;
		_isSpot = 0;
		break;
	case Light::Spot:
		_isSpot = 1;
		_isDirectional = 0;
		_isPoint = 0;
		break;
	}
}
