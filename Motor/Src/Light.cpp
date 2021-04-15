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

	CreateDataLight();
}

Light::Light(glm::vec3 colour, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Renderer * render, TypeLight type) : Entity(render)
{ 
	_colour = colour;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;

	CreateDataLight();
}

void Light::UseLight(Camera * cameraIn)
{
	glUniform3f(_uniformPosCameraLocation, cameraIn->transform.position.x,
		cameraIn->transform.position.y, cameraIn->transform.position.z);

	glUniform3f(_unifromColourLocation, _colour.x, _colour.y, _colour.z);

	glUniform3f(_uniformAmbientLocation, _ambient.x, _ambient.y, _ambient.z);

	glUniform3f(_uniformDiffuseLocation, _diffuse.x, _diffuse.y, _diffuse.z);

	glUniform3f(_uniformSpecularLocation, _specular.x, _specular.y, _specular.z);

	glUniform3f(_uniformPosLightLocation, transform.position.x, transform.position.y, transform.position.z);
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
	_unifromColourLocation = glGetUniformLocation(shader.getId(), "directionalLight.colour");
}

void Light::SetUniformAmbientLocation(Shader& shader)
{
	_uniformAmbientLocation = glGetUniformLocation(shader.getId(), "directionalLight.ambient");
}

void Light::SetUniformDiffuseLocation(Shader& shader)
{
	_uniformDiffuseLocation = glGetUniformLocation(shader.getId(), "directionalLight.diffuse");
}

void Light::SetUniformSpecularLocation(Shader& shader)
{
	_uniformSpecularLocation = glGetUniformLocation(shader.getId(), "directionalLight.specular");
}

void Light::SetUniformPosLightLocation(Shader& shader)
{
	_uniformPosLightLocation = glGetUniformLocation(shader.getId(), "directionalLight.posLight");
}

void Light::SetUniformPosCameraLocation(Shader & shader)
{
	_uniformPosCameraLocation = glGetUniformLocation(shader.getId(), "cameraPos");
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
