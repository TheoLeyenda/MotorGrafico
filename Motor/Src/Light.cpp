#include "Light.h"

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

void Light::UseLight(float ambientIntensityLocation, float ambientColourLocation,
	float diffuseIntensityLocation, float directionLocation)
{
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);

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

Light::~Light() {}
