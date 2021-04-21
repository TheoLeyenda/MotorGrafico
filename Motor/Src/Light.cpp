#include "Light.h"

#include "Camera.h"
#include "glew.h"
#include "GLFW/glfw3.h"

Light::Light(Renderer * _render, TypeLight type) : Entity(_render)
{
	_colour = glm::vec3(0.0f, 0.0f, 0.0f);
	_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	_diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	_specular = glm::vec3(0.0f, 0.0f, 0.0f);

	switch (type)
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
	case Light::Pos:
		_isSpot = 0;
		_isDirectional = 0;
		_isPoint = 0;
		break;
	}

	_linearValue = 0.09f;
	_quadraticValue = 0.032f;
	_cutOffValue = 12.5f;
	_outerCutOffValue = 17.5f;

	//Default
	SetDirectionLight(glm::vec3(-0.2f, -1.0f, -2.3f));

	CreateDataLight();
}

Light::Light(glm::vec3 colour, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Renderer * render, TypeLight type) : Entity(render)
{ 
	_colour = colour;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;

	switch (type)
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
	case Light::Pos:
		_isSpot = 0;
		_isDirectional = 0;
		_isPoint = 0;
		break;
	}

	_linearValue = 0.09f;
	_quadraticValue = 0.032f;
	_cutOffValue = 12.5f;
	_outerCutOffValue = 17.5f;

	//Default
	SetDirectionLight(glm::vec3(-0.2f, -1.0f, -2.3f));

	CreateDataLight();
}

void Light::UseLight(Camera * cameraIn)
{
	renderer->GetShaderColor().use();

#pragma region TYPES LIGHT
	glUniform1i(_uniformTypeLightDirectional, _isDirectional);
	
	glUniform1i(_uniformTypeLightPoint, _isPoint);
	
	glUniform1i(_uniformTypeLightSpot, _isSpot);
#pragma endregion

#pragma region DIRECTIONAL LIGHT && SPOT LIGHT
	if(_isDirectional == 1 && _isSpot == 0)
		glUniform3f(_uniformDirectionLocation, _direction.x, _direction.y, _direction.z);
	if(_isDirectional == 0 && _isSpot == 1)
		glUniform3f(_uniformDirectionLocation, transform.backward.x, transform.backward.y, transform.backward.z);
#pragma endregion
	
#pragma region SPOT LIGHT
	glUniform1f(_uniformCutOffSpotLight, glm::cos(glm::radians(_cutOffValue)));

	glUniform1f(_uniformOuterCutOffSpotLight, glm::cos(glm::radians(_outerCutOffValue)));
#pragma endregion

#pragma region POINT LIGHT
	glUniform1f(_uniformConstPointLight, _constValue);

	glUniform1f(_uniformLinearPointLight, _linearValue);

	glUniform1f(_uniformQuadraticPointLight, _quadraticValue);
#pragma endregion

#pragma region BASIC LIGHTING (POS LIGHT)
	glUniform3f(_uniformPosCameraLocation, cameraIn->transform.position.x,
		cameraIn->transform.position.y, cameraIn->transform.position.z);

	glUniform3f(_unifromColourLocation, _colour.x, _colour.y, _colour.z);

	glUniform3f(_uniformAmbientLocation, _ambient.x, _ambient.y, _ambient.z);

	glUniform3f(_uniformDiffuseLocation, _diffuse.x, _diffuse.y, _diffuse.z);

	glUniform3f(_uniformSpecularLocation, _specular.x, _specular.y, _specular.z);

	glUniform3f(_uniformPosLightLocation, transform.position.x, transform.position.y, transform.position.z);
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

void Light::SetTypeLight(TypeLight type)
{
	_typeLight = type;
}

void Light::SetUniformColourLocation(Shader& shader)
{
	_unifromColourLocation = glGetUniformLocation(shader.getId(), "lightSource.colour");
}

void Light::SetUniformAmbientLocation(Shader& shader)
{
	_uniformAmbientLocation = glGetUniformLocation(shader.getId(), "lightSource.ambient");
}

void Light::SetUniformDiffuseLocation(Shader& shader)
{
	_uniformDiffuseLocation = glGetUniformLocation(shader.getId(), "lightSource.diffuse");
}

void Light::SetUniformSpecularLocation(Shader& shader)
{
	_uniformSpecularLocation = glGetUniformLocation(shader.getId(), "lightSource.specular");
}

void Light::SetUniformPosLightLocation(Shader& shader)
{
	_uniformPosLightLocation = glGetUniformLocation(shader.getId(), "lightSource.posLight");
}

void Light::SetUniformDirectionLightLocation(Shader & shader)
{
	_uniformDirectionLocation = glGetUniformLocation(shader.getId(), "lightSource.direction");
}
void Light::SetUniformConstPointLight(Shader & shader)
{
	_uniformConstPointLight = glGetUniformLocation(shader.getId(), "lightSource.constant");
}

void Light::SetUniformLinearPointLight(Shader & shader)
{
	_uniformLinearPointLight = glGetUniformLocation(shader.getId(), "lightSource.linear");
}

void Light::SetUniformQuadraticPointLight(Shader & shader)
{
	_uniformQuadraticPointLight = glGetUniformLocation(shader.getId(), "lightSource.quadratic");
}

void Light::SetUniformCutOffSopttLight(Shader & shader)
{
	_uniformCutOffSpotLight = glGetUniformLocation(shader.getId(), "lightSource.cutOff");
}

void Light::SetUniformOuterCutOffSopttLight(Shader & shader)
{
	_uniformOuterCutOffSpotLight = glGetUniformLocation(shader.getId(), "lightSource.outerCutOff");
}

void Light::SetUniformPosCameraLocation(Shader & shader)
{
	_uniformPosCameraLocation = glGetUniformLocation(shader.getId(), "cameraPos");
}

void Light::SetUniformTypeLightDirectional(Shader & shader)
{
	_uniformTypeLightDirectional = glGetUniformLocation(shader.getId(), "typelight.directional");
}

void Light::SetUniformTypeLightSpot(Shader & shader)
{
	_uniformTypeLightSpot = glGetUniformLocation(shader.getId(), "typelight.spotLight");
}

void Light::SetUniformTypeLightPoint(Shader & shader)
{
	_uniformTypeLightPoint = glGetUniformLocation(shader.getId(), "typelight.pointLight");
}


void Light::SetPointLight(float linearVal, float quadraticVal)
{
	SetLinearValue(linearVal);
	SetQuadraticValue(quadraticVal);
}

Light::~Light() {}

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
