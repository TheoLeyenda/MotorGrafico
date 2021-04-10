#include "Light.h"

#include "Camera.h"
#include "glew.h"
#include "GLFW/glfw3.h"

Light::Light(Renderer * _render) : Entity(_render)
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;

	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuseIntensity = 0.0f;
}

Light::Light(Renderer * _render, float _red, float _green, float _blue, float _ambientIntensity,
	float _xDir, float _yDir, float _zDir, float _diffuseIntensity) : Entity(_render)
{
	colour = glm::vec3(_red, _green, _blue);
	ambientIntensity = _ambientIntensity;

	direction = glm::vec3(_xDir, _yDir, _zDir);
	diffuseIntensity = _diffuseIntensity;
}

Light::Light(Renderer * _render, float _red, float _green, float _blue, float _ambientIntensity,
	float _xDir, float _yDir, float _zDir, float _diffuseIntensity, Material * newMaterial) : Entity(_render)
{
	colour = glm::vec3(_red, _green, _blue);
	ambientIntensity = _ambientIntensity;

	direction = glm::vec3(_xDir, _yDir, _zDir);
	diffuseIntensity = _diffuseIntensity;

	materialSpecularInesity = newMaterial->GetSpecularIntensity();
	materialShininessInfluency = newMaterial->GetShininess();
}

void Light::UseLight(float ambientIntensityLocation, float ambientColourLocation,
	float diffuseIntensityLocation, float directionLocation, Camera* cameraIn)
{
	glUniform3f(uniformCameraPositionShaderColor, cameraIn->transform.position.x,
		cameraIn->transform.position.y, cameraIn->transform.position.z);

	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

	glUniform1f(uniformSpecularIntensityShaderColor, materialSpecularInesity);
	glUniform1f(uniformShininessShaderColor, materialShininessInfluency);
}

void Light::SetAmbientIntensityShaderColor(Shader& shader)
{
	uniformAmbientIntensityShaderColor = glGetUniformLocation(shader.getId(), "directionalLight.ambientIntensity");
}

void Light::SetAmbientColourShaderColor(Shader & shader)
{
	uniformAmbientColourShaderColor = glGetUniformLocation(shader.getId(), "directionalLight.colour");
}

void Light::SetAmbientIntensityShaderTexture(Shader & shader)
{
	uniformAmbientIntensityShaderTexture = glGetUniformLocation(shader.getId(), "directionalLight.ambientIntensity");
}

void Light::SetAmbientColourShaderTexture(Shader & shader)
{
	uniformAmbientColourShaderTexture = glGetUniformLocation(shader.getId(), "directionalLight.colour");
}

void Light::SetDiffuseIntensityShaderColor(Shader & shader)
{
	uniformDiffuseIntensityShaderColor = glGetUniformLocation(shader.getId(), "directionalLight.diffuseIntensity");
}

void Light::SetDiffuseIntensityShaderTexture(Shader& shader)
{
	uniformDiffuseIntensityShaderTexture = glGetUniformLocation(shader.getId(), "directionalLight.diffuseIntensity");
}

void Light::SetDirectionShaderColor(Shader & shader)
{
	uniformDirectionShaderColor = glGetUniformLocation(shader.getId(), "directionalLight.direction");
}

void Light::SetDirectionShaderTexture(Shader & shader)
{
	uniformDirectionShaderTexture = glGetUniformLocation(shader.getId(), "directionalLight.direction");
}

void Light::SetSpecularIntensityShaderColor(Shader & shader)
{
	uniformSpecularIntensityShaderColor = glGetUniformLocation(shader.getId(), "material.specularIntensity");
}

void Light::SetShininessShaderColor(Shader & shader)
{
	uniformShininessShaderColor = glGetUniformLocation(shader.getId(), "material.shininess");
}

void Light::SetCameraPositionShaderColor(Shader & shader)
{
	uniformCameraPositionShaderColor = glGetUniformLocation(shader.getId(), "cameraPos");
}

void Light::SetColorLight(float r, float g, float b)
{
	colour = glm::vec3(r, g, b);
}

void Light::SetAmbientIntensity(float _ambientIntensity)
{
	ambientIntensity = _ambientIntensity;
}

void Light::SetDirectionLight(float xDir, float yDir, float zDir)
{
	direction = glm::vec3(xDir, yDir, zDir);
}

void Light::SetDiffuseIntensity(float _diffuseIntensity)
{
	diffuseIntensity = _diffuseIntensity;
}

Light::~Light() {}
